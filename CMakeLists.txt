cmake_minimum_required(VERSION 3.6)
project(Algorithms_and_Data_Structures)

set(CMAKE_CXX_STANDARD 11)

set(BINARY_HEAP
    binary_heap/binary_heap.cpp
    binary_heap/binary_heap.h)

set(BINARY_SEARCH_TREE
    binary_search_tree/binary_search_tree.cpp
    binary_search_tree/binary_search_tree.h)

set(HEAP_SORT
    heap_sort/heap_sort.cpp
    heap_sort/heap_sort.h)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(heap_sort ${HEAP_SORT})
add_executable(bin_search_tree ${BINARY_SEARCH_TREE})
add_executable(bin_heap ${BINARY_HEAP})