cmake_minimum_required(VERSION 3.26)

project(${SKBUILD_PROJECT_NAME} LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
    # /wd6326 "Potential comparison of a constant with another constant."
    # /wd4200 "nonstandard extension used: zero-sized array in struct/union"
    add_compile_options(/guard:cf /analyze /permissive- /W4 /WX /wd6326 /wd4200)

else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

set(BUILD_SHARED_LIBS ON)

add_subdirectory(external)

install(TARGETS chl DESTINATION ${SKBUILD_PROJECT_NAME})

set(PYBIND11_NEWPYTHON ON)
set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)
