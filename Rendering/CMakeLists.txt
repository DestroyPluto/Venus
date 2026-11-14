cmake_minimum_required (VERSION 3.25)

# Tell cmake we want it to automate generating an export stub for the dll
SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(Rendering)

add_library(Rendering SHARED 
"source/renderingEngine.cpp" 
"source/RenderCommand.cpp" 
"source/Geometry.cpp" 
"source/glad.c"
"source/Shader.cpp")

target_include_directories(Rendering PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(OpenGL REQUIRED)

target_link_libraries(Rendering PUBLIC 
	glfw
	OpenGL::GL
	Math
)

# Copy shaders folder to build output: <output>/Shaders
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory
		"$<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${CMAKE_SOURCE_DIR}/Rendering/Shaders"
		"$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Shaders"
	COMMENT "Copying shader files to output directory"
)