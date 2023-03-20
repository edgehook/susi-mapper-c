#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <device.h>
#include <util/log.h>
#include <util/util.h>
#include <util/json_util.h>
#include <mapper_core.h>
#include "dev.h"
#include "Susi4.h"

int decode_susi_prop_access_config(char* payload, int * funcid, int * id){
	char* tmp = NULL;
	cJSON* object = json_parse(payload);

	if(!object)	return -1;
	*funcid = json_get_int_from_object(object, "funcid", 0);
	*id = json_get_int_from_object(object, "susiparam", 0);
        infof("payload is %s,funcid = 0x%x,id=0x%x \n",payload,*funcid,*id);	
	/*
	tmp = json_get_string_from_object(object, "path");
	if(!tmp) {
		json_delete(object);
		return -1;
	}
	strncpy(path, tmp, 127);

	tmp = json_get_string_from_object(object, "parameter");
	if(tmp){
		strncpy(parms, tmp, 127);
	}
	*/
	json_delete(object);
	return 0;
}

static int create_susi_service(susi_device* dev, susi_service* svc, device_service_spec* svc_spec){
	int i, ret;

	memcpy(svc->name, svc_spec->name, 64);

	//property.
	if(svc_spec->properties_size > 0){
		svc->properties_size = svc_spec->properties_size;
		dev->prop_count += svc->properties_size;
		svc->properties = (susi_property*)malloc(svc->properties_size*sizeof(susi_property));
		if(svc->properties){
			memset(svc->properties, 0, svc->properties_size*sizeof(susi_property));
			for(i = 0; i < svc->properties_size; i++){
				susi_property* prop = &svc->properties[i];
				device_property_spec* prop_spec = &svc_spec->properties[i];

				memcpy(prop->twin.service, svc->name, 64);
				memcpy(prop->twin.property_name, prop_spec->name, 64);
				prop->twin.writeable = prop_spec->writeable;
				prop->twin.max = prop_spec->max;
				prop->twin.min = prop_spec->min;
				memcpy(prop->twin.unit, prop_spec->unit, 16);
				memcpy(prop->twin.data_type, prop_spec->data_type, 16);
				ret = decode_susi_prop_access_config(prop_spec->access_config,
					&prop->funcid, &prop->parms);
				if(ret){
					errorf("decode_susi_prop_access_config failed %d \r\n", ret);
				}
			}
		}
	}

	//event.
	if(svc_spec->events_size > 0){
		svc->events_size = svc_spec->events_size;
		svc->events = (susi_event*)malloc(svc->events_size*sizeof(susi_event));
		if(svc->events){
			memset(svc->events, 0, svc->events_size*sizeof(susi_event));
			for(i = 0; i < svc->events_size; i++){
				susi_event * evt = &svc->events[i];
				device_event_spec* evt_spec = &svc_spec->events[i];

				memcpy(evt->name, evt_spec->name, 64);
				memcpy(evt->data_type, evt_spec->data_type, 16);
				memcpy(evt->event_type, evt_spec->event_type, 64);
			}
		}
	}

	return 0;
}

static int decode_susi_dev_protoc_config(char* payload, int* it, int* timeout){
	char* tmp;
	char  a[48] = {0},b[48] = {0};
	cJSON* object = json_parse(payload);

	if(!object) return -1;

	tmp = json_get_string_from_object(object, "it_u");
	if(tmp){
		if(!strcmp(tmp,"h")){
			*it = json_get_int_from_object(object, "it", 0)*3600000;
		}else if(!strcmp(tmp,"m")){
			*it = json_get_int_from_object(object, "it", 0)*60000;
		}else if(!strcmp(tmp,"s")){
			*it = json_get_int_from_object(object, "it", 0)*1000;
		}else{
			if(it)
				*it = json_get_int_from_object(object, "it", 0);
		}
	}else{
		if(it)
			*it = json_get_int_from_object(object, "it", 0);
	}

	tmp = json_get_string_from_object(object, "timeout");
	if(tmp && timeout){
		(void)sscanf(tmp, "%[0-9]%[a-Z]", b, a);
		(void)sscanf(b, "%d", timeout);
		if(!strcmp(a,"h")){
			*timeout = *timeout*3600000;
		}else if(!strcmp(tmp,"m")){
			*timeout = *timeout*60000;
		}else if(!strcmp(tmp,"s")){
			*timeout = *timeout*1000;
		}
	}

	json_delete(object);
	return 0;
}

susi_device* create_susi_device(device_spec_meta* dev_spec){
	int i, size;
	susi_device* dev = NULL;

	if(!dev_spec) return NULL;

	if(dev_spec->size <= 0 || !dev_spec->services) return NULL;

	size = sizeof(susi_device);
	size += dev_spec->size * sizeof(susi_service);

	dev = (susi_device*)malloc(size);
	if(!dev) return NULL;

	memset(dev, 0, size);
	memcpy(dev->device_id, dev_spec->device_id, 48);
	memcpy(dev->device_os, dev_spec->device_os, 32);
	memcpy(dev->device_catagory, dev_spec->device_catagory, 32);
	memcpy(dev->device_id_code, dev_spec->device_id_code, 64);
	memcpy(dev->device_state, dev_spec->device_state, 32);
	memcpy(dev->tags, dev_spec->tags, 32);

	decode_susi_dev_protoc_config(dev_spec->protocol, &dev->interval, &dev->timeout);
	dev->interval = dev->interval <= 0 ? 5000: dev->interval;
	//reserve 200ms  for mqtt transfor times.
	dev->interval = dev->interval > 200 ? dev->interval-200 : 200;

	Thread_create_mutex(&dev->mutex);
	if(!dev->mutex){
		free(dev);
		return dev;
	}

	//create services.
	dev->size = dev_spec->size;
	dev->online = 1;
	dev->services = (susi_service*)((char*)dev + sizeof(susi_device));

	//setup every service.
	for(i = 0; i < dev->size; i++){
		device_service_spec* svc_spec = &dev_spec->services[i];
		susi_service*	svc	= &dev->services[i];

		create_susi_service(dev, svc, svc_spec);
	}

	return dev;
}

/*
* we do a very simple fetch function.
*/
int do_dummy_fetch(char* path, char* parms){
	//infof("path = %s, parms=%s \r\n", path, parms);

	return (int)(get_timestamp()/1000);
}

void do_fetch_props_and_report(susi_device* dev){
	int i = 0, k = 0;
	int size;
	unsigned int ret =0;
	device_report_msg* report_msg;
	devices_props_report_msg* devices_msg;
	report_device_props_msg*  dev_msg;

	if(dev->prop_count < 0) return;
	if(dev->size <= 0) return;

	report_msg = malloc(sizeof(device_report_msg));
	if(!report_msg) return;

	report_msg->events_report_msg = NULL;
	// create devices report message. 
	devices_msg = malloc(sizeof(devices_props_report_msg));
	if(!devices_msg) {
		free(report_msg);
		return;
	}
	// create device report message.
	size = sizeof(report_device_props_msg);
	size += dev->prop_count*sizeof(twin_property);
	dev_msg = malloc(size);
	if(!dev_msg){
		free(devices_msg);
		free(report_msg);
		return;
	}

	memset(dev_msg, 0, size);
	memcpy(dev_msg->device_id, dev->device_id, 48);
	dev_msg->size = dev->prop_count;
	dev_msg->twin_properties =(twin_property*)((char*)dev_msg + sizeof(report_device_props_msg));

	devices_msg->size = 1;
	devices_msg->devices = dev_msg;
	report_msg->props_report_msg = devices_msg;

	for(i = 0; i < dev->size; i++){
		int j;// d;
		
		susi_service* svc = &dev->services[i];

		for(j = 0; j < svc->properties_size; j++){
			char * value = malloc(sizeof(64));
			susi_property* prop = &svc->properties[j];
			twin_property* tprop = &dev_msg->twin_properties[k++];
			
			if(!dev->running) return;

			prop->twin.timestamp = get_timestamp();
			memcpy(tprop, &prop->twin, sizeof(twin_property));
			//d = do_dummy_fetch(prop->path, prop->parms);
			//susi_get_property_value(prop->funcid, prop->parms, value);
			
			if(string_contain(prop->twin.data_type, "int")){
				tprop->value = malloc(sizeof(int));
				//if(tprop->value) *((int*)tprop->value) = atoi(value);
			}else if(string_contain(prop->twin.data_type, "float")){
				tprop->value = malloc(sizeof(double));
				//if(tprop->value) *((float*)tprop->value) = atof(value);
			}else if(string_contain(prop->twin.data_type, "boolean")){
				tprop->value = malloc(sizeof(int));
				//if(tprop->value) *((int*)tprop->value) = atoi(value)%2;
			}else if(string_contain(prop->twin.data_type, "string")){
				tprop->value = malloc(sizeof(64));
				//if(tprop->value) 
				//tprop->value = value;
			}else {
				tprop->value = malloc(sizeof(char)*64);
				//if(tprop->value) sprintf((char*)tprop->value, "%d", atoi(value)%100);
			}

			if(!tprop->value){
				strncpy(tprop->err_msg, "malloc failed!", 127);
			}else{

			        ret = susi_get_property_value(prop->funcid, prop->parms, tprop->value);
				if (ret == SUSI_STATUS_UNSUPPORTED)
				{
					strncpy(tprop->err_msg, "funtion not support!", 127);
					//tprop->err_msg[0] = -1;
				}
				//infof("############tprop->value=%lf\n",*(double*)tprop->value);
				//tprop->err_msg[0] = 0;
			}

		}
	}

	//send report message.
	(void)send_device_report_msg(report_msg);
}
void start_colloct_and_report_data(void* content){
	susi_device* dev = (susi_device*)content;

	if(!dev) return;

	while(1){
		do_fetch_props_and_report(dev);
		if(dev->interval <= 1000){
			if(!dev->running) {
				infof("device(%s) fetch and report exit \r\n", dev->device_id);
				dev->stopped = 1;
				return;
			}
			util_sleep_v2(dev->interval);
		}else{
			int i;

			for(i =0; i < dev->interval/1000; i++){
				if(!dev->running) {
					infof("device(%s) fetch and report exit \r\n", dev->device_id);
					dev->stopped = 1;
					return;
				}
				util_sleep_v2(1000);
			}
		}
	}
}

int start_susi_device(susi_device* dev){
	if(dev->size < 0){
		/* no service, no need to start */
		return -1;
	}
	if(dev->running){
		/* has already running.*/
		return 1;
	}
	Thread_lock_mutex(dev->mutex);
	dev->running = 1;
	dev->stopped = 0;
	submit_task(start_colloct_and_report_data, dev);
	Thread_unlock_mutex(dev->mutex);

	return 0;
}

int stop_susi_device(susi_device* dev){
	if(!dev->running) return 0;

	Thread_lock_mutex(dev->mutex);
	dev->running = 0;
retry_wait_stopped:
	if(!dev->stopped){
		util_sleep_v2(100);
		goto retry_wait_stopped;
	}
	Thread_unlock_mutex(dev->mutex);

	return 0;
}

void destory_susi_device(susi_device* dev){
	if(dev->running){
		stop_susi_device(dev);
	}

	Thread_destroy_mutex(dev->mutex);
	//free device.
	if(dev->services){
		int i;

		for(i = 0; i < dev->size; i++){
			susi_service* svc = &dev->services[i];

			if(svc->properties){
				int j = 0;

				for(j=0; j < svc->properties_size; j++){
					susi_property* prop = &svc->properties[j];

					if(prop->twin.value)
						free(prop->twin.value);
				}

				free(svc->properties);
			}
			if(svc->events)
				free(svc->events);
		}
	}
	free(dev);
}
