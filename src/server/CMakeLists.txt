cmake_minimum_required(VERSION 3.12)

project(Server)

# 设置变量
file(GLOB MY_SOURCES "*.cpp")

# 生成静态库
add_library(${PROJECT_NAME} STATIC ${MY_SOURCES})

target_link_libraries(${PROJECT_NAME} Buffer)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../include/)