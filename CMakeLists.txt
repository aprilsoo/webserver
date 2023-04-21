cmake_minimum_required(VERSION 3.10)

project(Webserver CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# file(GLOB
#  resources 
#  ./src/buffer/*.cpp
#  ./src/server/*.cpp
#  ./src/log/*.cpp
#  ./src/pool/*.cpp
# )

add_subdirectory(./src/buffer)
add_subdirectory(./src/server)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include/)

add_executable(${PROJECT_NAME} ./src/server/main.cpp)

target_link_libraries(${PROJECT_NAME} Buffer)
target_link_libraries(${PROJECT_NAME} Server)