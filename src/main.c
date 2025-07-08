#include <zephyr/kernel.h>
#include "led_driver.h"

int main(void)
{
    int ret = led_init();
    if (ret < 0) {
        return ret;
    }
    
    while (1) {
        led_toggle();
        k_msleep(1000);
    }
    
    return 0;
}