# cmake needs this line
cmake_minimum_required(VERSION 2.8)
add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "-march=native -O3  -pthread")
# Define project name
project(airport)

add_library(3rd_libs SHARED Mesh.cpp gate.cpp timeline.cpp Graph.cpp plan.cpp passenger.cpp flight.cpp)
# Declare the executable target built from your sources
add_executable(airport main.cpp)
target_link_libraries( airport
        3rd_libs
        )