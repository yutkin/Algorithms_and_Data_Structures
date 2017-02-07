cmake_minimum_required(VERSION 3.6)
project(Algorithms_and_Data_Structures)

set(CMAKE_CXX_STANDARD 14)

set(MY_COMPILE_FLAGS "-O2 -Wall -Wpedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MY_COMPILE_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${MY_COMPILE_FLAGS}")

set(BINARY_HEAP
    binary_heap/binary_heap.cpp
    binary_heap/binary_heap.h)

set(BINARY_SEARCH_TREE
    binary_search_tree/binary_search_tree.cpp
    binary_search_tree/binary_search_tree.h)

set(HEAP_SORT
    heap_sort/heap_sort.cpp
    heap_sort/heap_sort.h)

set(DIJKSTRA
    dijkstra/dijkstra.h
    dijkstra/dijkstra_test.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(heap_sort ${HEAP_SORT})
add_executable(bin_search_tree ${BINARY_SEARCH_TREE})
add_executable(bin_heap ${BINARY_HEAP})
add_executable(dijkstra_test ${DIJKSTRA})