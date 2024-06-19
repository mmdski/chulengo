cmake_minimum_required(VERSION 3.23)
project(parson LANGUAGES C)

set(CMAKE_C_STANDARD 90)

set(PARSON_VERSION 1.5.3)

add_library(parson parson.c)
add_library(parson::parson ALIAS parson)
target_sources(parson
  PUBLIC
  FILE_SET HEADERS
  FILES parson.h
)

if(PARSON_BUILD_TESTS)
  file(COPY tests DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
  add_executable(test tests.c parson.c)
  target_compile_definitions(test PUBLIC TESTS_MAIN)

  if(NOT MSVC)
    target_compile_options(test PRIVATE -O0 -g -Wall -Wextra -pedantic-errors)
  endif()
endif()
