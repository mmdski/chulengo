configure_file(${CMAKE_CURRENT_SOURCE_DIR}/BEAVCREK.g01 ${CMAKE_CURRENT_BINARY_DIR}/BEAVCREK.g01 COPYONLY)

add_executable(ch_ras_geometry_ex read_geometry.c ch_ras.c)
target_link_libraries(ch_ras_geometry_ex chl)
