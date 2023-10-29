cmake_minimum_required(VERSION 3.11)

add_library(ATmega328P_HAL_Driver src/hal_power.c)

target_include_directories(ATmega328P_HAL_Driver PUBLIC include)
