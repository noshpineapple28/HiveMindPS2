# general metadata
cmake_minimum_required(VERSION 3.10)
project(HiveMindPS2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(Threads REQUIRED)

# source files = $SRC_FILES
add_subdirectory(./src)
# headers
include_directories(./include)
# build executable
add_executable(HiveMindPS2 ${SRC_FILES})

####################################################
#                   LIBRARIES
####################################################
add_subdirectory(./lib/socket.io-client-cpp)
add_subdirectory(./lib/simpleble/simpleble)
target_include_directories(
    HiveMindPS2 PRIVATE
    ./lib/socket.io-client-cpp
    ./lib/simpleble/simpleble/include/simpleble_c
    ./include
)
target_link_libraries(HiveMindPS2 sioclient)
target_link_libraries(HiveMindPS2 Threads::Threads)
target_link_libraries(HiveMindPS2 simpleble::simpleble-c)
