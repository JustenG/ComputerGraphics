project (JustnEngine)

find_package(FBX)
find_package(PhysX)
#Need to find OpenGL link_libraries(
find_package(OpenGL REQUIRED)

#Bring the headers
include_directories(include)


#Gather additional source files/headers
SET(SOURCES
	src/Application.cpp
	src/main.cpp
	
	src/Assets/Asset.cpp
	src/Assets/AssetManager.cpp
	src/Assets/Material.cpp
	src/Assets/Mesh.cpp
	src/Assets/MeshFile.cpp
	src/Assets/Shader.cpp
	src/Assets/Texture.cpp

	src/Components/Camera.cpp
	src/Components/Collider.cpp
	src/Components/ComponentManager.cpp
	src/Components/FlyCamera.cpp
	src/Components/Light.cpp
	src/Components/MeshRenderer.cpp
	src/Components/Particles.cpp
	src/Components/RigidBody.cpp
	src/Components/PlayerController.cpp
	src/Components/Terrain.cpp
	src/Components/Transform.cpp

	src/Entitys/GameObject.cpp
	src/Entitys/EntityManager.cpp

	src/Physics/ParticleEmitter.cpp
	src/Physics/PhysXManager.cpp

	src/Rendering/FrameBuffer.cpp	
	src/Rendering/IndexBuffer.cpp
	src/Rendering/VertexArrayObject.cpp
	src/Rendering/VertexBuffer.cpp

	src/Utilities/Data.cpp
	src/Utilities/GUI.cpp

)
SET(HEADERS
	include/Application.h
	
	include/Assets/Asset.h	
	include/Assets/AssetManager.h	
	include/Assets/Material.h
	include/Assets/Mesh.h
	include/Assets/MeshFile.h
	include/Assets/Shader.h
	include/Assets/Texture.h

	include/Components/BaseComponent.h
	include/Components/Camera.h
	include/Components/Collider.h
	include/Components/Component.h
	include/Components/ComponentCollection.h
	include/Components/ComponentManager.h
	include/Components/FlyCamera.h
	include/Components/IComponentCollection.h
	include/Components/Light.h
	include/Components/MeshRenderer.h
	include/Components/Particles.h
	include/Components/PlayerController.h
	include/Components/RigidBody.h
	include/Components/Terrain.h
	include/Components/Transform.h

	include/Entitys/GameObject.h
	include/Entitys/EntityManager.h

	include/Physics/ParticleEmitter.h
	include/Physics/PhysXManager.h
	
	include/Rendering/FrameBuffer.h
	include/Rendering/IndexBuffer.h
	include/Rendering/Vertex.h
	include/Rendering/VertexArrayObject.h
	include/Rendering/VertexBuffer.h

	include/Utilities/Data.h
	include/Utilities/GUI.h
	include/Utilities/Utils.h

)

SET(EXTRA_SOURCES
	${CMAKE_SOURCE_DIR}/deps/gl/gl_core_4_4.c
	${CMAKE_SOURCE_DIR}/deps/utilities/all_includes.cpp
	${CMAKE_SOURCE_DIR}/deps/utilities/global_includes.cpp
    ${CMAKE_SOURCE_DIR}/deps/utilities/Gizmos.cpp
    ${CMAKE_SOURCE_DIR}/deps/memalign/memaligned.cpp
    ${CMAKE_SOURCE_DIR}/deps/imgui/imgui.cpp
   	${CMAKE_SOURCE_DIR}/deps/imgui/imgui_Draw.cpp
    ${CMAKE_SOURCE_DIR}/deps/imguihelpers/imgui_impl_glfw_gl3.cpp
    )

IF(FBX_FOUND)
    SET(EXTRA_SOURCES ${EXTRA_SOURCES} ${CMAKE_SOURCE_DIR}/deps/fbx/FBXFile.cpp)
ENDIF(FBX_FOUND)

#Need to build GLFW if we haven't already..
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" ON)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${CMAKE_SOURCE_DIR}/deps/glfw ${CMAKE_BINARY_DIR}/deps/glfw)
  
#Tell cmake that this will be a library (and not a exectutable)
add_library(${PROJECT_NAME} ${SOURCES} ${EXTRA_SOURCES} ${HEADERS})
  
source_group(Base ./)
source_group(ExtraSources FILES ${EXTRA_SOURCES})
source_group(Assets .*/Assets.*/)
source_group(Components .*/Components/)
source_group(Entitys .*/Entitys/)
source_group(Physics .*/Physics/)
source_group(Rendering .*/Rendering/)
source_group(Utilities .*/Utilities/)

#And we need to link against GLFW
target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})

#and link against OpenGL
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

#Finally, we want the compiler to know where to find the headers
#for this library when compiling it into other projects
#TODO: Work out why this isn't working...
target_include_directories (${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


#Include FBX if supported by this PC
IF(FBX_FOUND)
    message("FBX Support enabled")
    
    include_directories(${CMAKE_SOURCE_DIR}/deps/fbx)
    include_directories(${FBX_INCLUDE_DIR})
    message(${FBX_INCLUDE_DIR})

    target_link_libraries(${PROJECT_NAME} debug ${FBX_LIBRARY_DEBUG})
    target_link_libraries(${PROJECT_NAME} optimized ${FBX_LIBRARY})
    
    target_compile_definitions(${PROJECT_NAME} PUBLIC FBX_SUPPORTED)
    
ELSE(FBX_FOUND)
    message("No FBX support in this development environement")
ENDIF(FBX_FOUND)

if(PHYSX_FOUND)
	message("Found NVIDIA PhysX SDK")
	include_directories(${PHYSX_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} debug ${PHYSX_LIBRARY_DEBUG})
	target_link_libraries(${PROJECT_NAME} debug ${PHYSX_COMMON_LIBRARY_DEBUG})
	target_link_libraries(${PROJECT_NAME} debug ${PHYSX_COOKING_LIBRARY_DEBUG})
	target_link_libraries(${PROJECT_NAME} debug ${PHYSX_PROFILE_SDK_LIBRARY_DEBUG})
	target_link_libraries(${PROJECT_NAME} debug ${PHYSX_EX_LIBRARY_DEBUG})
	target_link_libraries(${PROJECT_NAME} debug ${PHYSX_VD_SDK_LIBRARY_DEBUG})
	target_link_libraries(${PROJECT_NAME} debug ${PHYSX_CK_LIBRARY_DEBUG})
	
	target_link_libraries(${PROJECT_NAME} optimized ${PHYSX_LIBRARY})
	target_link_libraries(${PROJECT_NAME} optimized ${PHYSX_COMMON_LIBRARY})
	target_link_libraries(${PROJECT_NAME} optimized ${PHYSX_COOKING_LIBRARY})
	target_link_libraries(${PROJECT_NAME} optimized ${PHYSX_PROFILE_SDK_LIBRARY})
	target_link_libraries(${PROJECT_NAME} optimized ${PHYSX_EX_LIBRARY})
	target_link_libraries(${PROJECT_NAME} optimized ${PHYSX_CK_LIBRARY})
	
	target_compile_definitions(${PROJECT_NAME} PUBLIC PHYSX_SUPPORTED)
	
else(PHYSX_FOUND)
	message("Missing NVIDIA PhysX SDK")
endif(PHYSX_FOUND)