cmake_minimum_required(VERSION 3.26)

if(NOT DEFINED SKBUILD)
    set(PROJECT_NAME chulengo)
else()
    set(PROJECT_NAME ${SKBUILD_PROJECT_NAME})
endif()

project(${PROJECT_NAME} LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
    # /wd6326 "Potential comparison of a constant with another constant."
    # /wd4200 "nonstandard extension used: zero-sized array in struct/union"
    add_compile_options(/guard:cf /analyze /permissive- /W4 /WX /wd6326 /wd4200)

else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(ExternalProject)
set(chl_LIB_NAME ${CMAKE_STATIC_LIBRARY_PREFIX}chl${CMAKE_STATIC_LIBRARY_SUFFIX})
ExternalProject_Add(chlExternal
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/chl
    INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${PROJECT_NAME}
    CMAKE_ARGS
    -D CMAKE_BUILD_TYPE=Release
    -D CMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    -D PY_MEM=YES
    -D BUILD_SHARED_LIBS=YES
)
