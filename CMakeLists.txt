cmake_minimum_required(VERSION 3.0)

project(igl_utils)
set (igl_utils_VERSION_MAJOR 0)
set (igl_utils_VERSION_MINOR 1)

find_package(Eigen3 REQUIRED)
include_directories(${IGL_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})

ADD_EXECUTABLE(obj2ply src/obj2ply.cc)
ADD_EXECUTABLE(obj2m src/obj2m.cc)
ADD_EXECUTABLE(objtl src/objtl.cc)
ADD_EXECUTABLE(objcenter src/objcenter.cc)

