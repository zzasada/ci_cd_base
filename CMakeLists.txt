cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(ci_cd_base
    VERSION 1.0.0
    DESCRIPTION "Embedded firmware with unit testing"
    LANGUAGES C
)

# Only build when not using west
if(NOT DEFINED ENV{ZEPHYR_BASE})
    message(STATUS "Building outside of Zephyr - creating standalone analysis build")
    
    # Create a minimal build for static analysis
    add_executable(firmware_analysis
        src/main.c
        src/led_driver.c
    )
    
    target_include_directories(firmware_analysis PRIVATE
        src
        # Mock Zephyr headers for analysis
        ${CMAKE_CURRENT_SOURCE_DIR}/mock_headers
    )
    
    # Create mock headers directory if it doesn't exist
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/mock_headers/zephyr)
    
    # Create minimal mock headers for analysis
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/mock_headers/zephyr/kernel.h 
        "#ifndef ZEPHYR_KERNEL_H\n#define ZEPHYR_KERNEL_H\n"
        "typedef unsigned int k_timeout_t;\n"
        "void k_msleep(int ms);\n"
        "#endif\n")
    
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/mock_headers/zephyr/drivers/gpio.h
        "#ifndef ZEPHYR_GPIO_H\n#define ZEPHYR_GPIO_H\n"
        "struct gpio_dt_spec { void* port; int pin; int flags; };\n"
        "int gpio_pin_configure_dt(const struct gpio_dt_spec* spec, int flags);\n"
        "int gpio_pin_set_dt(const struct gpio_dt_spec* spec, int value);\n"
        "int gpio_pin_toggle_dt(const struct gpio_dt_spec* spec);\n"
        "bool device_is_ready(const void* dev);\n"
        "#define GPIO_OUTPUT_INACTIVE 0\n"
        "#define DT_ALIAS(x) x\n"
        "#define GPIO_DT_SPEC_GET_OR(node, prop, default_value) default_value\n"
        "#endif\n")
else()
    message(STATUS "Building with Zephyr - using west build system")
endif()

target_sources(app PRIVATE 
    src/main.c
    src/led_driver.c
)

target_include_directories(app PRIVATE src)