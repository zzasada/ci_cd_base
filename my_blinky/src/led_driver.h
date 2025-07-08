#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/**
 * @brief Initialize the LED
 * @return 0 on success, negative error code on failure
 */
int led_init(void);

/**
 * @brief Turn LED on
 * @return 0 on success, negative error code on failure
 */
int led_on(void);

/**
 * @brief Turn LED off
 * @return 0 on success, negative error code on failure
 */
int led_off(void);

/**
 * @brief Toggle LED state
 * @return 0 on success, negative error code on failure
 */
int led_toggle(void);

/**
 * @brief Get LED state
 * @return 1 if LED is on, 0 if off, negative error code on failure
 */
int led_get_state(void);

#endif /* LED_DRIVER_H */