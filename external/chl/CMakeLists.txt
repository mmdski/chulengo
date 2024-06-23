cmake_minimum_required(VERSION 3.23)

project(chl LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(chl_BUILD_TESTS "Build tests" NO)
option(chl_BUILD_EXAMPLES "Build examples" NO)
option(chl_PY_MEM "Use PyMem" NO)

if(PROJECT_IS_TOP_LEVEL)
  include(cmake/Sanitizers.cmake)

  if(MSVC)
    # /wd6326 "Potential comparison of a constant with another constant."
    # /wd4200 "nonstandard extension used: zero-sized array in struct/union"
    add_compile_options(/guard:cf /analyze /permissive- /W4 /WX /wd6326 /wd4200)

  else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
  endif()
endif()

if(chl_BUILD_TESTS)
  include(FetchContent)
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

if(chl_PY_MEM)
  find_package(
    Python
    COMPONENTS Development
    REQUIRED)
endif()

add_subdirectory(src)

if(chl_BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()
