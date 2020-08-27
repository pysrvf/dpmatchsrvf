cmake_minimum_required(VERSION 3.17)
project(dpmatchsrvf)
set(CMAKE_CXX_STANDARD 14)
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})
include(GNUInstallDirs)
include_directories("${SRC_DIR}")

add_executable(dpmatchsrvfapp
	${SRC_DIR}/dpmatchsrvfapp.cpp
	${SRC_DIR}/dpmatch.cpp
	${SRC_DIR}/dpmatch.h)

add_library(ldpmatchsrvf ${SRC_DIR}/dpmatch.cpp ${SRC_DIR}/dpmatch.h)

set(PYTHON_MODULE_NAME dpmatchsrvf)
add_subdirectory(lib/pybind11)
pybind11_add_module(${PYTHON_MODULE_NAME} MODULE ${SRC_DIR}/pydpmatchsrvf.cpp ${SRC_DIR}/dpmatch.cpp ${SRC_DIR}/dpmatch.h)
set (PYBIND_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11/include/pybind11)
target_include_directories(${PYTHON_MODULE_NAME} PRIVATE ${PYBIND_INCLUDE_DIR})
