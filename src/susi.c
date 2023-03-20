#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <device.h>
#include <util/log.h>
#include <util/util.h>
#include <util/json_util.h>
#include "Susi4.h"


static const char *infoValStr[] = {
	"Spec version",
	"Boot up times",
	"Running time (hours)",
	"Microsoft Plug-and-Play ID",
	"Platform revision",
	"Last Shutdown Status",
	"Last Shutdown Event"
};


static const char *infoStrStr[] = {
	"Board manufacturer",
	"Board name",
	"Board revision",
	"Board serial number",
	"BIOS revision",
	"Hardware revision",
	"Platform type",
	"Firmware name",
	"BIOS name"
};


enum funcid{
	func_boardinfor=0,	
	func_hwm,
	func_gpio,
	NumFunc,
};


int susi_get_hwm_value(SusiId_t id, void * pvalue)
{
	SusiStatus_t status;
	float convVal;
	uint32_t getVal = 0;
	
	//infof("SUSI get hwm value id = 0x%x\n",id);
	status = SusiBoardGetValue(id, &getVal);
	if (status == SUSI_STATUS_SUCCESS)
	{
		//infof("susi_get_hwm_value: id = 0x%x,value=0x%x\n",getVal);
	}
	else
	{
		if (status != SUSI_STATUS_UNSUPPORTED)
		errorf("SusiBoardGetValue(0x%08X) failed. (0x%08X)\n", id, status);
		return status;
	}
	if ((id >= SUSI_ID_HWM_VOLTAGE_BASE) && (id < SUSI_ID_HWM_VOLTAGE_BASE + SUSI_ID_HWM_VOLTAGE_MAX) )//电压
	{
		convVal = getVal / (float)1000;
	//	infof("%.3f V\n", convVal);
	}
	else if ( (id >= SUSI_ID_HWM_TEMP_BASE) && (id < SUSI_ID_HWM_TEMP_BASE + SUSI_ID_HWM_TEMP_MAX) )//温度
	{
		convVal = SUSI_DECODE_CELCIUS((float)(getVal));//转换为摄氏度
	//	infof("%.1f Celsius\n", convVal);
	}
	*(double *)pvalue = convVal;
	//infof("pvalue = %lf\n", *(double*)pvalue);
	return status;
}


int susi_get_gpio_value(uint8_t iPin, uint32_t *pvalue)
{
	uint32_t status, id, mask;
	//Only support single GPIO Mode

	id = SUSI_ID_GPIO(iPin);
	mask = 1; //没有作用


	status = SusiGPIOGetLevel(id, mask, pvalue);
	if (status != SUSI_STATUS_SUCCESS)
	{
		errorf("SusiGPIOGetLevel() failed. (0x%08X)\n", status);
		return 1;
	}

	return 0;
}

static void print_uncompress_ASCII_PNP_ID(uint32_t pnp_id,char * value)
{
	uint16_t ascii_part = (uint16_t)((pnp_id >> 12) & 0x0000FFFF);
	uint8_t low_byte = (uint8_t)(ascii_part & 0x00FF);
	uint8_t high_byte = (uint8_t)(ascii_part >> 8);

	uint8_t first_char_pos = (uint8_t)(low_byte >> 2);
	uint8_t second_char_pos_high_part = (uint8_t)(low_byte & 0x03);
	uint8_t second_char_pos_low_part = (uint8_t)(high_byte >> 5);
	uint8_t second_char_pos = (uint8_t)((second_char_pos_high_part << 3) | second_char_pos_low_part);
	uint8_t third_char_pos = (uint8_t)(high_byte & 0x1F);

	char c1 = 64 + first_char_pos;
	char c2 = 64 + second_char_pos;
	char c3 = 64 + third_char_pos;
	uint16_t vendor_specific_id = (uint16_t)(pnp_id & 0x00000FFF);

	sprintf(value,"%c%c%c, 0x%X\n", c1, c2, c3, vendor_specific_id);
}

int susi_get_board_information(SusiId_t id,void * pvalue)
{
	SusiStatus_t status;
	uint32_t getVal = 0;
	uint32_t getStrLen;
	char getStr[128];
	//infof("get board information,id =0x%x\n",id);
	//标准SUSI定义 SusiBoardGetStringA 和SusiBoardGetValue都是去获得一些设备的信息，ID也一样，所以没法区分，在AppHub中，
	//将SusiBoardGetStringA函数的ID传入值默认加上了0x10，所转移在真正调佣SusiBoardGetStringA，需要将id再减去0x10
	if ( id >= 0x10) 
	{
		status = SusiBoardGetStringA((id - 0x10), getStr, &getStrLen);
		if (status == SUSI_STATUS_SUCCESS)
		{
			sprintf((char *)pvalue,"%s\n", getStr);
			infof("board string = %s\n",pvalue );
		}
	}
	else{	
		status = SusiBoardGetValue(id, &getVal);
		switch (id)
		{
			case SUSI_ID_BOARD_DRIVER_VERSION_VAL:
			case SUSI_ID_BOARD_LIB_VERSION_VAL:
			case SUSI_ID_BOARD_FIRMWARE_VERSION_VAL:
				sprintf((char*)pvalue,"%u.%u.%u\n", (getVal >> 24), ((getVal >> 16) & 0xFF), (getVal & 0xFFFF));
				break;
			case SUSI_ID_BOARD_DOCUMENT_VERSION_VAL:
				sprintf((char*)pvalue,"%u.%u.%u\n", (getVal & 0xFF), ((getVal >> 8) & 0xFF), ((getVal >> 16) & 0xFF));
				break;
			case SUSI_ID_BOARD_PNPID_VAL:
				print_uncompress_ASCII_PNP_ID(getVal,(char*)pvalue);
				break;

			case SUSI_ID_GET_SPEC_VERSION:
			case SUSI_ID_BOARD_PLATFORM_REV_VAL:
				sprintf((char *)pvalue,"%u,%u\n", (getVal >> 24) & 0xFF, (getVal >> 16) & 0xFF);
				break;
			return 0;
		}
	}
	return 0;
}

int susi_library_init()
{
	SusiStatus_t status;
	uint32_t op; 
	int ret = 0;

	status = SusiLibInitialize();

	if (status == SUSI_STATUS_ERROR)
	{
		// This error only occurs on Linux distributions
		infof("Your Linux capabilities is not enough, recommond to become ROOT!\n");
		infof("Aborting  now.\n");
		return -1;
	}

	if (status != SUSI_STATUS_SUCCESS && status != SUSI_STATUS_INITIALIZED)
	{
		errorf("SusiLibInitialize() failed. (0x%08X)\n", status);
		infof("Exit the program...\n");
		return -1;
	}
	infof("SUSI library initialize successful\n");
}

int susi_get_property_value(int funcid, int id, void* pvalue)
{
	uint32_t tmpvalue;;
	switch (funcid){
	case  func_boardinfor:
	susi_get_board_information(id,pvalue);
	break;
	
	case func_hwm:
	susi_get_hwm_value(id,pvalue);
	break;
	
	case func_gpio:
	susi_get_gpio_value(id, pvalue);
	break;
	
	default:
	break;
	}
}

