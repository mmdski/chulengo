set(CH_SRCS
    ch_xs_coords.c
    ch_xs_def.c
    ch_xs_subdiv.c
    ch_xs_subsect.c
)
add_library(chl ${CH_SRCS})

target_sources(chl
    PUBLIC
    FILE_SET HEADERS
    FILES
    chl.h
)

if(PY_MEM)
    set_target_properties(chl PROPERTIES OUTPUT_NAME "chl.pymem")
    target_link_libraries(chl PRIVATE Python::Python)
endif()

install(TARGETS chl FILE_SET HEADERS DESTINATION include)

if(BUILD_TESTS)
    add_executable(ch_xs_coords.test ch_xs_coords.test.cpp)
    target_link_libraries(ch_xs_coords.test chl GTest::gtest_main)
    gtest_add_tests(TARGET ch_xs_coords.test TEST_LIST ch_xs_coords.test-list)
    set_tests_properties(${ch_xs_coords.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")

    add_executable(ch_xs_subdiv.test ch_xs_subdiv.test.cpp)
    target_link_libraries(ch_xs_subdiv.test chl GTest::gtest_main)
    gtest_add_tests(TARGET ch_xs_subdiv.test TEST_LIST ch_xs_subdiv.test-list)
    set_tests_properties(${ch_xs_subdiv.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")

    add_executable(ch_xs_def.test ch_xs_def.test.cpp)
    target_link_libraries(ch_xs_def.test chl GTest::gtest_main)
    gtest_add_tests(TARGET ch_xs_def.test TEST_LIST ch_xs_def.test-list)
    set_tests_properties(${ch_xs_def.test-list} PROPERTIES ENVIRONMENT "${TEST_ENV}")
endif()
