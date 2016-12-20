1.ILedService.aidl文件放在D:\android_projects\android_system_code\frameworks\base\core\java\android\os
2.修改frameworks/base/Android.mk 添加一行
					core/java/android/os/IVibratorService.aidl
					core/java/android/os/ILedService.aidl
3. mmm frameworks/base/
4.生成 .out/target/common/obj/JAVA_LIBRARIES/framework_intermediates/src/core/java/android/os/ILedService.java

（2） Server : LedService.java
								SystemServer.java
							
								
			把新文件上传到服务器
				frameworks/base/services/java/com/android/server/SystemServer.java
				frameworks/base/services/core/java/com/android/server/LedService.java
				
				
	不需要修改frameworks/base/services/core/Android.mk
		LOCAL_SRC_FILES += \ 
			${call all-java-files-under, java}
			
(3) JNI :
			com_android_server_LedService.cpp
			onload.cpp
		
		frameworks/base/services/core/jni/onload.cpp
		frameworks/base/services/core/jni/com_android_server_LedService
		
	修改frameworks/base/services/core/jni/Android.mk
	 $(LOCAL_REL_DIR)/com_android_server_VibratorService.cpp \
   + $(LOCAL_REL_DIR)/com_android_server_LedService.cpp \
   
 编译
 $ mmm frameworks/base/services/
 $ make snod
 $ ./gen-img.sh
 
 out/target/product/tiny4412/system.img
 
 
 编写app
 ILedService iLedService = ILedService.Stub.asInterface(ServiceManager.getService("led"));
	a.包含什么
		包含out/target/common/obj/JAVA_LIBRARIES/framework_intermediates/classess.jar
	b.怎么包含 （google 搜索android studio jar）
	
	修改project/app/src/build.gradle
    dexOptions {
        javaMaxHeapSize "4g"
    }
    
     defaultConfig {
     //添加Enabling  multidex support.
     multiDexEnabled true 
     }
     
     dependencies {
     	compile 'com.android.support:multidex:1.0.0'
     }
   修改 mainfest
    <application
    //添加
    android:name="android.support.multidex.MultiDexApplication"
    
    
  V3	
  (3)	JNI:重新上传
  frameworks/base/services/core/jni/com_android_server_LedService.cpp
  (4)HAL:hal_led.c hal_led.h
  hardware/libhardware/include/hardware/led_hal.h
  hardware/libhardware/modules/led/led_hal.c
  hardware/libhardware/modules/led/Android.n k
  
  Android.mk:
  LOCAL_PATH := $(call my-dir)
  include $(CLEAR_VARS)
  LOCAL_MODULE :=led.default
  LOCAL_MODULE_RELATIVE_PATH := hw
  LOCAL_C_INCLUDES := hardware/libhardware
  LOCAL_SRC_FILES := led_hal.c
  LOCAL_SHARED_LIBRARYS := liblog
  LOCAL_MODULE_TAGS := eng
  
  include $(BUILD_SHARED_LIBRARY)
   