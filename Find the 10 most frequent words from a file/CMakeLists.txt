cmake_minimum_required(VERSION 2.8.5)
project(hello_interview)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

set(CMAKE_CXX_FLAGS "-std=c++11")

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

include_directories(
${PROJECT_SOURCE_DIR}/include
)

add_library( TrieNode SHARED
  src/TrieNode.cpp
)




set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


add_executable(main  src/main.cpp)

target_link_libraries( main TrieNode)