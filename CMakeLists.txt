# CMakeList.txt : CMake project for 2D-Engine, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)
SET(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)


# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Venus")

# Add source to this project's executable.
add_executable (${PROJECT_NAME}  "Main.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/Engine/include
	${CMAKE_CURRENT_SOURCE_DIR}/Rendering/include
)

set(GLFW_DIR "${CMAKE_SOURCE_DIR}/ThirdParty/glfw-3.5.1")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(Rendering)
add_subdirectory(Engine)
add_subdirectory(${GLFW_DIR})

find_package( OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} 
	glfw
	Rendering 
	Engine
)

# Copy all runtime DLL dependencies (including Rendering/Engine) next to Venus.exe
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	COMMAND_EXPAND_LISTS
)