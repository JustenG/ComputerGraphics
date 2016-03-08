project (JustnEngine)

#Need to find OpenGL link_libraries(
find_package(OpenGL REQUIRED)

#Bring the headers
include_directories(include)


#Gather additional source files/headers
SET(SOURCES
	src/Application.cpp
	src/main.cpp
	
	src/Cameras/Camera.cpp
	src/Cameras/FlyCamera.cpp
	
	src/Rendering/IndexBuffer.cpp
	src/Rendering/VertexArrayObject.cpp
	src/Rendering/VertexBuffer.cpp

	src/Assets/FBX.cpp
	src/Assets/Material.cpp
	src/Assets/Mesh.cpp
	src/Assets/Shader.cpp
	src/Assets/Texture.cpp
)
SET(HEADERS
	include/Application.h
	
	include/Cameras/Camera.h
	include/Cameras/FlyCamera.h
	
	include/Rendering/IndexBuffer.h
	include/Rendering/VertexArrayObject.h
	include/Rendering/VertexBuffer.h
	
	include/Assets/FBX.h
	include/Assets/Material.h
	include/Assets/Mesh.h
	include/Assets/Shader.h
	include/Assets/Texture.h
)

SET(EXTRA_SOURCES
    ${CMAKE_SOURCE_DIR}/dep/gl/gl_core_4_4.c
    ${CMAKE_SOURCE_DIR}/dep/utilities/Gizmos.cpp
    )
    



#Need to build GLFW if we haven't already..
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" ON)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/dep/glfw ${CMAKE_BINARY_DIR}/dep/glfw)
  
  
source_group(Base ./)
source_group(ExtraSources FILES ${EXTRA_SOURCES})
source_group(Assets .*/Assets.*/)
source_group(Cameras .*/Cameras/)
source_group(Rendering .*/Rendering/)
#source_group(AssetLoading .*/AssetLoading/)



#Tell cmake that this will be a library (and not a exectutable)
add_library(${PROJECT_NAME} ${SOURCES} ${EXTRA_SOURCES} ${HEADERS})

#And we need to link against GLFW
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

#and link against OpenGL
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

#Finally, we want the compiler to know where to find the headers
#for this library when compiling it into other projects
#TODO: Work out why this isn't working...
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
