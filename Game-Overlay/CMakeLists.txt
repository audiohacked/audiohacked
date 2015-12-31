cmake_minimum_required(VERSION 2.8)
project(AGO) # Audiohacked Game Overlay

# set(AGO_CMAKE_DIR "" ${CMAKE_MODULE_PATH} "${AGO_SOURCE_DIR}/cmake")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake") # For custom cmake modules

find_package(Boost 1.48 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(FreeType REQUIRED)
find_package(FTGL REQUIRED)
# find_package(GLUT REQUIRED)
# find_package(SDL REQUIRED)
# find_package(SDL2 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

set(HEADERS
	error.hpp
	hook.hpp
	keyboard.hpp
	main.hpp
	render.hpp
	settings.hpp
	text.hpp
)

IF(${OPENGL_FOUND})
set(SOURCES
	${SOURCES}
	hook-opengl.cpp
	overlay-opengl.cpp
	render-opengl.cpp
)
ENDIF()

IF(${GLFW_FOUND})
	set(SOURCES
		${SOURCES}
		error-glfw.cpp
		keyboard-glfw.cpp
	)
ENDIF()

IF(${FTGL_FOUND})
	set(SOURCES
		${SOURCES}
		text-opengl.cpp
	)
ENDIF()

IF(${SDL_FOUND})
	set(SOURCES
		${SOURCES}
		error-sdl.cpp
		keyboard-sdl.cpp
	)
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	set(SOURCES
		${SOURCES}
		main-linux.cpp
	)
ENDIF()
		
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	set(SOURCES
		${SOURCES}
		main-mac.cpp
	)
ENDIF()	

IF(WIN32)
	set(SOURCES
		${SOURCES}
		hook-directx.cpp
		overlay-directx.cpp
		render-directx.cpp
		text-directx.cpp
	)
	set(SOURCES
		${SOURCES}
		main-win.cpp
	)
ENDIF()

add_executable(AGO  ${SOURCES} ${HEADERS}
	# WIN32 # Only if you don't want the DOS prompt to appear in the background in Windows
	#MACOSX_BUNDLE
)

include_directories(
	${OPENGL_INCLUDE_DIRS}
	${GLEW_INCLUDE_DIRS}
	${FREETYPE_INCLUDE_DIRS}
	${FTGL_INCLUDE_DIRS}
	${GLUT_INCLUDE_DIRS}
	${SDL_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
)

target_link_libraries(AGO
	${OPENGL_LIBRARIES}
	${GLEW_LIBRARIES}
	${FREETYPE_LIBRARIES}
	${FTGL_LIBRARIES}
	${GLUT_LIBRARIES}
	${SDL_LIBRARIES}
	${SDL2_LIBRARIES}
	${GLFW_LIBRARIES}
	# ${GLFW_STATIC_LIBRARIES}
)

