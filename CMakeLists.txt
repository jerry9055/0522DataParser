cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 20)
set(THIS format_pro)
project(${THIS})
aux_source_directory(./src SRC)
add_executable(${THIS}.out main.cpp ${SRC})

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -Wall -ggdb3 -O0")