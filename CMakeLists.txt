cmake_minimum_required(VERSION 3.20.0)

set(DEFAULT_ROOT ${CMAKE_CURRENT_LIST_DIR})

project(adc_filter_example)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Inc)

file(GLOB EXAMPLE_SOURCE Src/*.c*)
set(TEST_ADC_FILTER ${DEFAULT_ROOT}/Src/main.c)

add_executable(test_adc_filter ${TEST_ADC_FILTER})