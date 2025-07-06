cmake_minimum_required(VERSION 3.20.0)

# Set board if not specified
if(NOT DEFINED BOARD)
    set(BOARD nrf52840dk_nrf52840)
endif()

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(zephyr_firmware)

# Include directories
target_include_directories(app PRIVATE src)

# Source files
target_sources(app PRIVATE
    src/main.c
    # Add more source files here
)

# Compiler flags
target_compile_options(app PRIVATE
    -Wall
    -Wextra
    -Werror
)