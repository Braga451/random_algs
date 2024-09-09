cmake_minimum_required(VERSION 2.8)

project(main)
add_executable(main main.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/src/gl.c)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
# file(GLOB BUTTERFLIES_SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR} *.c include/src/gl.c)

target_link_libraries(main glfw ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

