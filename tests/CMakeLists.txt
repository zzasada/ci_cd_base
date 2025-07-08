cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(test_ci_cd_base)

# Coverage configuration - only instrument our source files
if(CONFIG_COVERAGE)
    target_compile_options(app PRIVATE
        --coverage
        -fprofile-arcs
        -ftest-coverage
    )
    target_link_libraries(app PRIVATE --coverage)
    
    # Only instrument our source files, not the mock
    set_source_files_properties(src/led_driver_mock.c 
        PROPERTIES COMPILE_FLAGS "-fno-profile-arcs -fno-test-coverage")
endif()

target_sources(app PRIVATE 
    src/test_led.c
    src/led_driver_mock.c
)

target_include_directories(app PRIVATE 
    ../src
    src
)
