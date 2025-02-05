cmake_minimum_required (VERSION 3.11)

project(test_data_generator)

set (VERSION_MAJOR 1)
set (VERSION_MINOR 0)
set (VERSION_PATCH 0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-deprecated -Wconversion -Wunused")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

SET(CMAKE_VERBOSE_MAKEFILE OFF)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    SET(CMAKE_VERBOSE_MAKEFILE ON)
endif ()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SRC src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME}
	PUBLIC
		include
		${CMAKE_CURRENT_BINARY_DIR}
)
