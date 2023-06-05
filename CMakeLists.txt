cmake_minimum_required(VERSION 3.10)

# set the project name
project(RayTracer)
project(
    RayTracer
  VERSION 0.1
  DESCRIPTION "The Raytracer Challenge"
  LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(CTest)
include_directories(include)
add_subdirectory(src)

add_subdirectory(app)

include(CTest)
enable_testing()
add_subdirectory(test)