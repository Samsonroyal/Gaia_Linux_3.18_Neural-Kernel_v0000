/*
 * w1-gpio interface to platform code
 */
#ifndef _LINUX_W1_GPIO_H
#define _LINUX_W1_GPIO_H

/**
 * struct w1_gpio_platform_data - Platform-dependent data for w1-gpio
 * @pin: GPIO pin to use
 * @is_open_drain: GPIO pin is configured as open drain
 */
struct w1_gpio_platform_data {
	unsigned int pin;
	unsigned int is_open_drain:1;
	void (*enable_external_pullup)(int enable);
	unsigned int ext_pullup_enable_pin;
	unsigned int pullup_duration;
};

#endif /* _LINUX_W1_GPIO_H */
