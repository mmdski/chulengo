cmake_minimum_required(VERSION 3.18)

project(chlib)

include(FetchContent)

if(TESTS)
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

set(TEST_ENV "")

if(ASAN)
  if(MSVC)
    add_compile_options(/fsanitize=address)
  else()
    add_compile_options(-fno-omit-frame-pointer)

    # for ASan and LSan
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)

    # for UBSan
    add_compile_options(-fsanitize=undefined -fno-sanitize-recover=all)
    add_link_options(-fsanitize=undefined)

    set(ASAN_OPTIONS "ASAN_OPTIONS=detect_leaks=1:abort_on_error=0")
    set(LSAN_OPTIONS "LSAN_OPTIONS=suppressions=${CMAKE_SOURCE_DIR}/lsan.supp")
    set(UBSAN_OPTIONS "UBSAN_OPTIONS=print_stacktrace=1")

    string(CONCAT TEST_ENV "${TEST_ENV}" "${ASAN_OPTIONS};${LSAN_OPTIONS};${UBSAN_OPTIONS}")
  endif()
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

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

#
# Build library
#
set(CH_SRCS
  src/ch_xs_coords.c
  src/ch_xs_subdiv.c
  src/ch_xs_subsect.c
)
add_library(chlib ${CH_SRCS})
target_include_directories(chlib PUBLIC "${CMAKE_SOURCE_DIR}/include")

if(MSVC)
  set_target_properties(chlib PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS YES)
endif()

if(TESTS)
  add_executable(ch_xs_coords.test src/ch_xs_coords.test.cpp)
  target_link_libraries(ch_xs_coords.test chlib GTest::gtest GTest::gtest_main)
  gtest_add_tests(TARGET ch_xs_coords.test TEST_LIST ch_xs_coords.test-list)
  set_tests_properties(${ch_xs_coords.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")

  add_executable(ch_xs_subdiv.test src/ch_xs_subdiv.test.cpp)
  target_link_libraries(ch_xs_subdiv.test chlib GTest::gtest GTest::gtest_main)
  gtest_add_tests(TARGET ch_xs_subdiv.test TEST_LIST ch_xs_subdiv.test-list)
  set_tests_properties(${ch_xs_subdiv.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")
endif()

if(EXAMPLES)
  add_subdirectory(examples)
endif()
