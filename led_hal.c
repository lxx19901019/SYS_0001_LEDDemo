
#define LOG_TAG "LedHal"


#include <hardware/vibrator.h>
#include <hardware/hardware.h>
#include <utils/misc.h>
#include <utils/Log.h>
#include <cutils/log.h>

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include "led_hal.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <android/log.h> 


static int fd;
static int led_close(struct hw_device_t *dev)
{
	close(fd);
	return 0;
}
static int led_open(struct led_device_t *dev)
{
	fd = open("/dev/leds", O_RDWR);
	ALOGI("native ledOpen fd = %d", fd);
	if(fd <= 0)
		return -1;
	else 
		return 0;
	
}
static int led_ctrl(struct led_device_t *dev, int which, int stauts)]
{
	int ret = ioctl(fd, status, which);
	ALOGI("native ledCtrl : %d %d %d",which , status, ret);
	return 0;
}

static  struct led_device_t led_dev = {
	.common={
		.close	=led_close,
	},
	.led_open		=led_open,
	.led_ctrl 		=led_ctrl,
};


static int led_device_open(const hw_module_t* module, const char* id __unused,
                      hw_device_t** device __unused)
{
	*device = &led_dev;
	return 0
}

static struct hw_module_methods_t led_methods = {
    .open = led_device_open,
};


struct hw_module_t HAL_MODULE_INFO_SYM = {
    .id = "led",
    .methods = &led_methods,
};





