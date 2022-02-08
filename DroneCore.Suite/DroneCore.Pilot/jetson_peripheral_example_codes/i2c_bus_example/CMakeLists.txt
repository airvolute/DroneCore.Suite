cmake_minimum_required(VERSION 2.8.3)
project(i2c_driver)
add_compile_options(-std=c++11)


include_directories(
  include
)


## Declare a C++ library
add_library(i2c_driver src/i2c_driver.cpp)

## Declare a C++ executable
add_executable(example src/example.cpp)

target_link_libraries(example i2c_driver)
