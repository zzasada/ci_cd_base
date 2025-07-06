#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    LOG_INF("Hello, Zephyr test!");

    // Main loop
    while (1) {
        // Perform periodic tasks or sleep
        k_sleep(K_SECONDS(1));
    }

    return 0; // This line is never reached
}