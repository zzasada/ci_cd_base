#include <zephyr/ztest.h>
#include <zephyr/kernel.h>
#include "led_driver.h"
#include "led_driver_test.h"

/* Test setup function - resets state before each test */
static void test_before(void *data)
{
    led_reset();
}

/* Test LED initialization */
ZTEST(led_tests, test_led_init)
{
    int ret = led_init();
    zassert_equal(ret, 0, "LED initialization should succeed");
}

/* Test LED operations without initialization */
ZTEST(led_tests, test_led_operations_without_init)
{
    /* led_reset() was called in test_before, so LED should be uninitialized */
    int ret = led_on();
    zassert_equal(ret, -ENOTCONN, "LED on should fail without init");
    
    ret = led_off();
    zassert_equal(ret, -ENOTCONN, "LED off should fail without init");
    
    ret = led_toggle();
    zassert_equal(ret, -ENOTCONN, "LED toggle should fail without init");
    
    ret = led_get_state();
    zassert_equal(ret, -ENOTCONN, "LED get_state should fail without init");
}

/* Test LED state management */
ZTEST(led_tests, test_led_state_management)
{
    int ret;
    
    /* Initialize LED */
    ret = led_init();
    zassert_equal(ret, 0, "LED initialization should succeed");
    
    /* Initial state should be off */
    ret = led_get_state();
    zassert_equal(ret, 0, "LED should initially be off");
    
    /* Turn LED on */
    ret = led_on();
    zassert_equal(ret, 0, "LED on should succeed");
    
    ret = led_get_state();
    zassert_equal(ret, 1, "LED should be on");
    
    /* Turn LED off */
    ret = led_off();
    zassert_equal(ret, 0, "LED off should succeed");
    
    ret = led_get_state();
    zassert_equal(ret, 0, "LED should be off");
}

/* Test LED toggle functionality */
ZTEST(led_tests, test_led_toggle)
{
    int ret;
    
    /* Initialize LED */
    ret = led_init();
    zassert_equal(ret, 0, "LED initialization should succeed");
    
    /* Start with LED off */
    ret = led_off();
    zassert_equal(ret, 0, "LED off should succeed");
    
    /* Toggle should turn it on */
    ret = led_toggle();
    zassert_equal(ret, 0, "LED toggle should succeed");
    
    ret = led_get_state();
    zassert_equal(ret, 1, "LED should be on after toggle");
    
    /* Toggle again should turn it off */
    ret = led_toggle();
    zassert_equal(ret, 0, "LED toggle should succeed");
    
    ret = led_get_state();
    zassert_equal(ret, 0, "LED should be off after second toggle");
}

/* Test suite setup with before hook to reset state */
ZTEST_SUITE(led_tests, NULL, NULL, test_before, NULL, NULL);
