
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

namespace android{
static jint fd;

#include <android/log.h>  //liblog
//__android_log_print(ANDROID_LOG_DEBUG,"JNIDemo","native add ...")

jint ledOpen(JNIEnv *env, jobject cls)
{
	fd = open("/dev/leds", O_RDWR);
	ALOGI("native ledOpen fd = %d", fd);
	if(fd <= 0)
		return -1;
	else 
		return 0;
	

	return 0;
}

void ledClose(JNIEnv *env, jobject cls)
{	
		ALOGI("native ledClose");
		close(fd);
}


jint ledCtrl(JNIEnv *env, jobject cls, jint which ,jint status)
{

	int ret = ioctl(fd, status, which);
	ALOGI("native ledCtrl : %d %d %d",which , status, ret);
	return 0;
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

