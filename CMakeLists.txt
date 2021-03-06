cmake_minimum_required (VERSION 2.8.12)

project (ComputerGraphics)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_CHAR_IS_UNSIGNED_CHAR} ${STD_C15}")
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

enable_testing()

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Builds)
set (ASSETS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

set	(TARGET_PHYSX_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/physx/dll/release)
set	(TARGET_PHYSX_DIR_D ${CMAKE_CURRENT_SOURCE_DIR}/deps/physx/dll/debug)
set (BUILD_DIR ${CMAKE_BINARY_DIR}/Builds/Release)
set (BUILD_DIR_D ${CMAKE_BINARY_DIR}/Builds/Debug)

#add common include directories for dependancies
include_directories(${CMAKE_SOURCE_DIR}/deps/gl)
include_directories(${CMAKE_SOURCE_DIR}/deps/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/utilities)
include_directories(${CMAKE_SOURCE_DIR}/deps/memalign)
include_directories(${CMAKE_SOURCE_DIR}/deps/imgui)
include_directories(${CMAKE_SOURCE_DIR}/deps/imguihelpers)
include_directories(${CMAKE_SOURCE_DIR}/deps/fbx)
include_directories(${CMAKE_SOURCE_DIR}/deps/stb)
include_directories(${CMAKE_SOURCE_DIR}/deps/physx/include)

add_definitions(-DGLM_SWIZZLE)
add_definitions(-DGLM_FORCE_PURE)
include_directories(${CMAKE_SOURCE_DIR}/deps/glm)

add_subdirectory (JustnEngine)
add_subdirectory (TestEngine)