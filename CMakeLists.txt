cmake_minimum_required(VERSION 3.15...3.27)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(dpmatchsrvf)
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/nanobind)

set(PYTHON_MODULE_NAME dpmatchsrvf)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/dpmatchsrvf)

nanobind_add_module(${PYTHON_MODULE_NAME} ${SRC_DIR}/pydpmatchsrvf.cpp ${SRC_DIR}/dpmatch.cpp ${SRC_DIR}/dpmatch.h)

include_directories("${SRC_DIR}")
include_directories("${SRC_DIR}/ext/nanobind/include/")

add_executable(dpmatchsrvfapp
	${SRC_DIR}/dpmatchsrvfapp.cpp
	${SRC_DIR}/dpmatch.cpp
	${SRC_DIR}/dpmatch.h)

#add_library(ldpmatchsrvf ${SRC_DIR}/dpmatch.cpp ${SRC_DIR}/dpmatch.h)
