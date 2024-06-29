cmake_minimum_required(VERSION 3.10)

project("Domaci_5" LANGUAGES CXX)

file(GLOB SRC_FILES src/*.cpp)
add_executable(main ${SRC_FILES})

target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/fibheap/include)
target_link_libraries(main ${CMAKE_CURRENT_SOURCE_DIR}/lib/fibheap/libfibheap.a)
