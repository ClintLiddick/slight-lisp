cmake_minimum_required (VERSION 2.8.12)

project (SLIGHT_LISP)

SET( PROJ_SOURCES   "src/prompt.c" "src/mpc.c" )
SET( PROJ_LIBRARIES "edit" "m" )

INCLUDE_DIRECTORIES( "include" )
ADD_EXECUTABLE(prompt ${PROJ_SOURCES})
TARGET_LINK_LIBRARIES( prompt ${PROJ_LIBRARIES} )
TARGET_COMPILE_OPTIONS(prompt PUBLIC -std=c99 -Wall)
