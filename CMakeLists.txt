project(Controller)

cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++17 -pthread")

# set(CMAKE_CXX_STANDARD 17)

# Find all source code
file(GLOB project_SRCS src/*.cpp) #src/*.h

# Add project executable
add_executable(controller ${project_SRCS})