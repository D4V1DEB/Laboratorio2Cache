cmake_minimum_required(VERSION 3.10)
project(Laboratorio2Cache CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -Wall")

add_executable(1anidados 1anidados.cpp)
add_executable(2mutiplicacionmatrices 2mutiplicacionmatrices.cpp)
add_executable(3multiplicacionbloques 3multiplicacionbloques.cpp)
add_executable(4strassen 4strassen.cpp)
add_executable(5winograd 5winograd.cpp)
