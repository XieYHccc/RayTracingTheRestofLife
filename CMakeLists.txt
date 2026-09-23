cmake_minimum_required(VERSION 3.25)

project(RayTracingTheNextWeek)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# 所有可执行文件统一输出到 build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(PROJECT_SOURCE_ROOT ${PROJECT_SOURCE_DIR})

configure_file(config/RootPath.h.in config/RootPath.h)

include_directories (
	${PROJECT_BINARY_DIR}/config
	# ...
)

add_subdirectory(framework)
add_subdirectory(chapters)
