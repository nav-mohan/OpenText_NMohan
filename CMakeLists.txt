message("BUILDING MAIN")
cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 17) #<filesystem>
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(main LANGUAGES CXX C)

# name of binary executable
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(libs/xmlparser)
add_subdirectory(libs/htmlbuilder)

target_include_directories(
    ${PROJECT_NAME} PUBLIC 
    libs/xmlparser
    libs/htmlbuilder
)

target_link_libraries(
    ${PROJECT_NAME} 
    xmlparser
    htmlbuilder
)