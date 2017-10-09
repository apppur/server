cmake_minimum_required (VERSION 2.6)

# debug or release
set(CMAKE_BUILD_TYPE "Debug")
#set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=gnu++11 -O0 -Wall -g -ggdb ")
#set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=gnu++11 -O3 -Wall ")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -std=c++11 -O0 -Wall -g -ggdb ")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -std=c++11 -O3 -Wall ")

project (engine)

set(ENGINE_VERSION_MAJOR 1)
set(ENGINE_VERSION_MINOR 0)

#set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  #"${PROJECT_BINARY_DIR}/config.h"
  "${PROJECT_SOURCE_DIR}/engine/include/config.h"
)
include_directories("${PROJECT_SOURCE_DIR}/engine/include")

# add lua
include_directories("${PROJECT_SOURCE_DIR}/3rd/lua-5.3.4/src")
link_directories("${PROJECT_SOURCE_DIR}/3rd/lua-5.3.4/src")
add_custom_target(
  build_lua ALL
  COMMAND ${CMAKE_MAKE_PROGRAM} linux
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/3rd/lua-5.3.4
  COMMENT "original lua makefile target"
)
add_library(lua STATIC IMPORTED)
add_dependencies(lua build_lua)

#add_executable(engine 
#  ./engine/src/engine_main.cpp
#  ./engine/src/engine_message.cpp
#)
aux_source_directory(./engine/src engine_src)
add_executable(Engine ${engine_src})

target_link_libraries(Engine liblua.a dl pthread)

enable_testing()
add_test(test_run engine)

# test version
add_test(test_version engine -version)

