#include "led.h"

struct led led_data[2];

bool led_init()
{
	led_data[0].gpio_dev = device_get_binding(LED0);
	if (led_data[0].gpio_dev == NULL) {
		printk("Could not get led0 device\n");
		return false;
	}
	
	led_data[1].gpio_dev = device_get_binding(LED1);
	if (led_data[1].gpio_dev == NULL) {
		printk("Could not get led1 device\n");
		return false;
	}

	if(gpio_pin_configure(led_data[0].gpio_dev, PIN0, GPIO_OUTPUT_ACTIVE | FLAGS0) < 0)
		return false;
	if(gpio_pin_configure(led_data[1].gpio_dev, PIN1, GPIO_OUTPUT_ACTIVE | FLAGS1) < 0)
		return false;
	
	led_data[0].gpio_pin = PIN0;
	led_data[1].gpio_pin = PIN1;

	return true;
}

void blink(const struct led *led, uint32_t sleep_ms)
{
	while (1) {
		gpio_pin_toggle(led->gpio_dev, led->gpio_pin);
		k_msleep(sleep_ms);
	}
}

void blink0(void)
{
	blink(&led_data[0], 500);
}

void blink1(void)
{
	blink(&led_data[1], 1000);
}

void toggle0(void)
{
    gpio_pin_toggle(led_data[0].gpio_dev, led_data[0].gpio_pin);
}
void toggle1(void)
{
    gpio_pin_toggle(led_data[1].gpio_dev, led_data[1].gpio_pin);
}