cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(unit_tests)

# Include main app source (exclude main.c)
target_include_directories(app PRIVATE 
    ../../app/src
)

# Test source files
target_sources(app PRIVATE
    src/test_main.c
    # Add more test files here
)