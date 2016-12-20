
#define LOG_TAG "LedService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>


#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <hardware/led_hal.h>
#include <hardware/hardware.h>
namespace android{
 
struct led_device_t *led_device;

#include <android/log.h>  //liblog
//__android_log_print(ANDROID_LOG_DEBUG,"JNIDemo","native add ...")

jint ledOpen(JNIEnv *env, jobject cls)
{
	int err;
	const struct  hw_module_t *module;
	struct hw_device_t *device;
	
	/* 1. hw_get_module*/
	ALOGI("native ledOpen");
	err = hw_get_module("led", &module);
	if(err== 0 ){
			err = module->methods->open(module, NULL, &device);
			if(err == 0) {
				/*3 call led_open*/
				led_device = (struct led_device_t *)device;
				return led_device->led_open(led_device);
			}else
				return -1;
	}
	/* 2.get device*/
	
	return -1;
}

void ledClose(JNIEnv *env, jobject cls)
{	
		ALOGI("native ledClose");
}


jint ledCtrl(JNIEnv *env, jobject cls, jint which ,jint status)
{
	ALOGI("native ledCtrl which:%d status:%d", which, status);	
	return led_device->led_ctrl(led_device,which, status);
	
}



static const JNINativeMethod methods[] ={
		{"native_ledOpen", "()I",(void *)ledOpen},
		{"native_ledClose", "()V",(void *)ledClose},
		{"native_ledCtrl", "(II)I",(void *)ledCtrl},
};

int register_android_server_LedService(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "com/android/server/LedService",
            methods, NELEM(methods));
}
};


