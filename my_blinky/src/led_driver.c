#include "led_driver.h"

#ifdef CONFIG_BOARD_NATIVE_SIM
/* Mock implementation for native simulator */
static bool led_initialized = false;
static bool led_state = false;

int led_init(void)
{
    led_initialized = true;
    led_state = false;
    return 0;
}

int led_on(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    led_state = true;
    return 0;
}

int led_off(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    led_state = false;
    return 0;
}

int led_toggle(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    led_state = !led_state;
    return 0;
}

int led_get_state(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    return led_state ? 1 : 0;
}

#else
/* Real hardware implementation */
#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET_OR(LED0_NODE, gpios, {0});
static bool led_initialized = false;
static bool led_state = false;

int led_init(void)
{
    if (!device_is_ready(led.port)) {
        return -ENODEV;
    }
    
    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return ret;
    }
    
    led_initialized = true;
    led_state = false;
    return 0;
}

int led_on(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    
    int ret = gpio_pin_set_dt(&led, 1);
    if (ret == 0) {
        led_state = true;
    }
    return ret;
}

int led_off(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    
    int ret = gpio_pin_set_dt(&led, 0);
    if (ret == 0) {
        led_state = false;
    }
    return ret;
}

int led_toggle(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    
    int ret = gpio_pin_toggle_dt(&led);
    if (ret == 0) {
        led_state = !led_state;
    }
    return ret;
}

int led_get_state(void)
{
    if (!led_initialized) {
        return -ENOTCONN;
    }
    
    return led_state ? 1 : 0;
}
#endif
