cmake_minimum_required(VERSION 3.10)
project(ShapeManagerMonolith)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(shape_manager src/main.cpp src/model.cpp src/controller.cpp src/view.cpp)
