#ifndef __DEV_H__
#define __DEV_H__

#include <device.h>

typedef struct{
	twin_property twin;
	int funcid;
	char path[128];
	int  parms;
}susi_property;

typedef struct{
	char name[64];
	char  data_type[16];
	char  event_type[16];
	void* value;
}susi_event;

typedef struct{
	char name[64];
	//list all device_property_spec
	int properties_size;
	susi_property* properties;
	//list all device_event_spec
	int events_size;
	susi_event* events;
}susi_service;

typedef struct {
	char device_id[48];
	char device_os[32];
	char device_catagory[32];
	char device_id_code[64];
	char device_state[32];
	char tags[128];
	int online;
	int size;	/* service count */
	int prop_count;
	int running;
	int stopped;
	int interval;
	int timeout;
	mutex_type  mutex;
	susi_service* services;
}susi_device;

susi_device* create_susi_device(device_spec_meta* dev_spec);
int start_susi_device(susi_device* dev);
int stop_susi_device(susi_device* dev);
void destory_susi_device(susi_device* dev);
#endif
