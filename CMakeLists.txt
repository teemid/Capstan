cmake_minimum_required(VERSION 3.6)

project(Capstan)

set(PROJECT_NAME "Capstan")

set(CAPSTAN_VERSION_MAJOR "0")
set(CAPSTAN_VERSION_MINOR "1")
set(CAPSTAN_VERSION_PATCH "0")

set(CAPSTAN_VERSION "${CAPSTAN_VERSION_MAJOR}.${CAPSTAN_VERSION_MINOR}.${CAPSTAN_VERSION_PATCH}")

set(CAPSTAN_PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR})

set(CAPSTAN_SOURCE_DIR ${CAPSTAN_PROJECT_DIR}/source)

find_package(OpenGL REQUIRED)

if (NOT OPENGL_FOUND)
    message(FATAL_ERROR "OpenGL not found.")
endif(NOT OPENGL_FOUND) 

file(GLOB CAPSTAN_GENERAL_SOURCES "${CAPSTAN_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE CAPSTAN_ALLOCATORS_SOURCES "${CAPSTAN_SOURCE_DIR}/Allocators/*.cpp")
file(GLOB_RECURSE CAPSTAN_GRAPHICS_SOURCES "${CAPSTAN_SOURCE_DIR}/Graphics/*.cpp")
file(GLOB_RECURSE CAPSTAN_MATH_SOURCES "${CAPSTAN_SOURCE_DIR}/Math/*.cpp")
file(GLOB_RECURSE CAPSTAN_PHYSICS_SOURCES "${CAPSTAN_SOURCE_DIR}/Physics/*.cpp")

include_directories(${CAPSTAN_PROJECT_DIR}/include)

set(CAPSTAN_SOURCES
    ${CAPSTAN_GENERAL_SOURCES}
    ${CAPSTAN_ALLOCATORS_SOURCES}
    ${CAPSTAN_GRAPHICS_SOURCES}
    ${CAPSTAN_MATH_SOURCES}
    ${CAPSTAN_PHYSICS_SOURCES}
)

add_subdirectory(targets/Windows)
