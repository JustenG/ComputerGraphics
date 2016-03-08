cmake_minimum_required (VERSION 2.6)

project (ComputerGraphics)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C15}")
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

enable_testing()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)

#add common include directories for dependancies
include_directories(${CMAKE_SOURCE_DIR}/dep/gl)
include_directories(${CMAKE_SOURCE_DIR}/dep/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/dep/utilities)
include_directories(${CMAKE_SOURCE_DIR}/dep/fbx)
include_directories(${CMAKE_SOURCE_DIR}/dep/stb)

add_definitions(-DGLM_SWIZZLE)
include_directories(${CMAKE_SOURCE_DIR}/dep/glm)

add_subdirectory (JustnEngine)
add_subdirectory (TestEngine)