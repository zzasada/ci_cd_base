#include "led_driver.h"

static bool led_initialized = false;
static bool led_state = false;

/* Reset function for testing */
void led_reset(void)
{
    led_initialized = false;
    led_state = false;
}

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
