cmake_minimum_required(VERSION 3.23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(GameEngine)

add_executable(main)
add_library(serialib)

target_sources(serialib
	PRIVATE
	Lib/serialib.cpp

	PUBLIC
	FILE_SET serialib
	TYPE HEADERS
	BASE_DIRS
		Lib
	FILES
		Lib/serialib.h
)

target_sources(main
	PRIVATE
	Program.cpp
	Parse.cpp
	GameEngine.cpp
	Serial.cpp
	Debug.cpp

	Types.hpp
	Program.hpp
	Parse.hpp
	Serial.hpp
	Debug.hpp
)

target_link_libraries(main
	PRIVATE
		serialib
)

