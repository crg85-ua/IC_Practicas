cmake_minimum_required(VERSION 3.27)
project(IC LANGUAGES CXX)

add_executable(${PROJECT_NAME} "src/main.cc")
target_include_directories(${PROJECT_NAME} PRIVATE "include")
# target_link_libraries(${PROJECT_NAME} pthread)