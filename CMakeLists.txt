cmake_minimum_required(VERSION 3.17)
project(DPmatchsrvf)
set(CMAKE_CXX_STANDARD 14)
set (SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

include_directories("${SRC_DIR}")

add_executable(DPmatchsrvfapp 
	${SRC_DIR}/DPmatchsrvf.cpp
	${SRC_DIR}/DPmatch.cpp 
	${SRC_DIR}/DPmatch.h)

add_library(DPmatchsrvf ${SRC_DIR}/DPmatch.cpp ${SRC_DIR}/DPmatch.h)

add_subdirectory(lib/pybind11)
pybind11_add_module(pyDPmatchsrvf ${SRC_DIR}/pyDPmatchsrvf.cpp ${SRC_DIR}/DPmatch.cpp ${SRC_DIR}/DPmatch.h)
set (PYBIND_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/pybind11/include/pybind11)
target_include_directories(pyDPmatchsrvf PRIVATE ${PYBIND_INCLUDE_DIR})

