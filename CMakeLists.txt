cmake_minimum_required(VERSION 3.18)

if(SCIKIT_BUILD)
    project(${SKBUILD_PROJECT_NAME} LANGUAGES C CXX)
else()
    project(chl LANGUAGES C CXX)
endif()

option(BUILD_TESTS "Build tests" NO)

if(PROJECT_IS_TOP_LEVEL)
    include(cmake/Sanitizers.cmake)
endif()

include(FetchContent)

if(BUILD_TESTS)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    include(GoogleTest)
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

if(MSVC)
    # /wd6326 "Potential comparison of a constant with another constant."
    # /wd4200 "nonstandard extension used: zero-sized array in struct/union"
    add_compile_options(/guard:cf /analyze /permissive- /W4 /WX /wd6326 /wd4200)

else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)

    if(COVERAGE)
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif()
endif()

if(SCIKIT_BUILD)
    find_package(Python COMPONENTS Development REQUIRED)
    add_compile_definitions(PY_BUILD)
endif()

#
# Build library
#
add_subdirectory(src/chl)
