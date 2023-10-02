message("BUILDING MAIN")
cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 17) #<filesystem>
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main LANGUAGES CXX C)

add_executable(${PROJECT_NAME} main.cpp)