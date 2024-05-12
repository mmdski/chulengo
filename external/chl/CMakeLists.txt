cmake_minimum_required(VERSION 3.18)

project(chl LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

option(BUILD_TESTS "Build tests" NO)
option(PY_MEM "Use PyMem" NO)

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

if(PY_MEM)
    add_compile_definitions(PY_MEM)
    find_package(
        Python
        COMPONENTS Development
        REQUIRED)
endif()

add_subdirectory(src)
