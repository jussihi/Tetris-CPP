# Check that we aren't building in the source tree
IF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	MESSAGE(FATAL_ERROR "In-tree build is bad practice.")
ENDIF(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

# settings
CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(Tetris-CPP)


# Set compiler and linker flags
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-g")

SET(SOURCES
	src/RenderClasses.hpp src/graphics.hpp src/TetrisUtils.hpp src/main.cpp
	src/TetrisClasses.hpp src/TetrisClasses.cpp
	src/RenderClasses.hpp src/RenderClasses.cpp)


ADD_EXECUTABLE(tetris ${SOURCES})
TARGET_LINK_LIBRARIES(tetris sfml-graphics sfml-window sfml-system)