cmake_minimum_required(VERSION 3.18)

project(sds VERSION 2.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_library(sds sds.c)
add_library(sds::sds ALIAS sds)
target_sources(sds
    PUBLIC
    FILE_SET HEADERS
    FILES sds.h
)

if(sds_BUILD_TEST)
    add_executable(sds-test sds.c)
    target_compile_definitions(sds-test PRIVATE SDS_TEST_MAIN)

    set_target_properties(sds-test PROPERTIES COMPILE_OPTIONS "")

    if(MSVC)
        # /wd6326 "Potential comparison of a constant with another constant."
        # /wd4200 "nonstandard extension used: zero-sized array in struct/union"
        target_compile_options(sds-test PRIVATE /guard:cf /analyze /permissive- /W4 /WX /wd6326 /wd4200)

    else()
        target_compile_options(sds-test PRIVATE -Wall -pedantic -O2)
    endif()
endif()
