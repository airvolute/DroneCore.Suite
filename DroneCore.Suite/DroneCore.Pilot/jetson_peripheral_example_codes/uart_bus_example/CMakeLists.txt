cmake_minimum_required(VERSION 2.8.3)
project(uart_driver)
add_compile_options(-std=c++11)

include_directories(
  include
)

## Declare a C++ library
add_library(uart_driver src/uart_driver.cpp)

## Declare a C++ executable
add_executable(example src/example.cpp)

target_link_libraries(example uart_driver)