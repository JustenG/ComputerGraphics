project (TestEngine)

#Bring the headers
include_directories(include)

#Gather additional source files/headers
SET(SOURCES
	src/TestEngineApp.cpp
	src/main.cpp
)
SET(HEADERS
	include/TestEngineApp.h
)

#Tell cmake that this will be a library (and not a exectutable)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
source_group(Include FILES ${HEADERS}) #This will format the output project file so the headers are placed seperately

#This project uses the OpenGL project, so we need to add that to this project
target_link_libraries (${PROJECT_NAME} JustnEngine)

install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_SOURCE_DIR}/data)