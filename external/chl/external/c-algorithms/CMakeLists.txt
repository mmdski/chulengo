cmake_minimum_required(VERSION 3.18)

project(c-algorithms VERSION 1.2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CALG_SOURCES
  src/arraylist.c
  src/avl-tree.c
  src/binary-heap.c
  src/bloom-filter.c
  src/compare-int.c
  src/compare-pointer.c
  src/compare-string.c
  src/hash-int.c
  src/hash-pointer.c
  src/hash-string.c
  src/hash-table.c
  src/list.c
  src/queue.c
  src/rb-tree.c
  src/set.c
  src/slist.c
  src/sortedarray.c
  src/trie.c
)
add_library(calg ${CALG_SOURCES})
add_library(calg::calg ALIAS calg)
target_include_directories(calg PRIVATE include/libcalg)
target_sources(calg
  PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
)
