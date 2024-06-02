add_executable(ras_read_geometry read_geometry.c ch_ras.c)
target_link_libraries(ras_read_geometry chl)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/BEAVCREK.g01 ${CMAKE_CURRENT_BINARY_DIR}/BEAVCREK.g01 COPYONLY)
