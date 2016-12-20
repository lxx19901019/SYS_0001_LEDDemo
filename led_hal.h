
#ifndef __LED_HAL_H__
#define __LED_HAL_H__

#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <hardware/hardware.h>



struct led_device_t {
	struct hw_device_t common;
	int (*led_open)(struct led_device_t *dev);
	int (*led_ctrl)(struct led_device_t *dev, int which, int stauts);
};

#endif


