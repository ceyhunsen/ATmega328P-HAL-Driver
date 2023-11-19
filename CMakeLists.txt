cmake_minimum_required(VERSION 3.11)

add_library(ATmega328P_HAL_Driver src/hal_power.c src/hal_system.c)

target_include_directories(ATmega328P_HAL_Driver PUBLIC include)
target_compile_definitions(ATmega328P_HAL_Driver PUBLIC __AVR_ATmega328P__)
