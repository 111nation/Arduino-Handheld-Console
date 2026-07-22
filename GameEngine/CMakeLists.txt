cmake_minimum_required(VERSION 3.23)
project(GameEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SDL_SHARED OFF CACHE BOOL "Build SDL shared library" FORCE)
set(SDL_STATIC ON CACHE BOOL "Build SDL static library" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)

add_subdirectory(Lib/SDL EXCLUDE_FROM_ALL)

add_executable(main)
add_library(serialib STATIC)

target_sources(serialib
	PRIVATE
	Lib/serialib/lib/serialib.cpp

	PUBLIC
	FILE_SET serialib
	TYPE HEADERS
	BASE_DIRS
		Lib
	FILES
		Lib/serialib/lib/serialib.h
)

target_sources(main
	PRIVATE
	Display.cpp
	Serial.cpp
	Program.cpp
	Parse.cpp
	GameEngine.cpp
	Debug.cpp

	Types.hpp
	Display.hpp
	Program.hpp
	Parse.hpp
	Serial.hpp
	Debug.hpp
)

target_link_libraries(main
	PRIVATE
		serialib
		SDL3::SDL3-static
)

add_custom_target(run ALL 
    COMMAND $<TARGET_FILE:main>
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    DEPENDS main
)
