cmake_minimum_required(VERSION 3.15...3.27)
set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(dpmatchsrvf)
find_package(Python 3.8 COMPONENTS Interpreter Development.Module REQUIRED)

if (NOT SKBUILD)
  message(WARNING "\
  This CMake file is meant to be executed using 'scikit-build'. Running
  it directly will almost certainly not produce the desired result. If
  you are a user trying to install this package, please use the command
  below, which will install all necessary build dependencies, compile
  the package in an isolated environment, and then install it.
  =====================================================================
   $ pip install .
  =====================================================================
  If you are a software developer, and this is your own package, then
  it is usually much more efficient to install the build dependencies
  in your environment once and use the following command that avoids
  a costly creation of a new virtual environment at every compilation:
  =====================================================================
   $ pip install nanobind scikit-build-core[pyproject]
   $ pip install --no-build-isolation -ve .
  =====================================================================
  You may optionally add -Ceditable.rebuild=true to auto-rebuild when
  the package is imported. Otherwise, you need to re-run the above
  after editing C++ files.")
endif()


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ext/nanobind)

set(PYTHON_MODULE_NAME dpmatchsrvf)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/dpmatchsrvf)

nanobind_add_module(${PYTHON_MODULE_NAME} STABLE_ABI NB_STATIC ${SRC_DIR}/pydpmatchsrvf.cpp ${SRC_DIR}/dpmatch.cpp ${SRC_DIR}/dpmatch.h)

include_directories("${SRC_DIR}")
include_directories("${SRC_DIR}/ext/nanobind/include/")

add_executable(dpmatchsrvfapp
	${SRC_DIR}/dpmatchsrvfapp.cpp
	${SRC_DIR}/dpmatch.cpp
	${SRC_DIR}/dpmatch.h)

add_library(ldpmatchsrvf ${SRC_DIR}/dpmatch.cpp ${SRC_DIR}/dpmatch.h)
