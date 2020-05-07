cmake_minimum_required(VERSION 3.0)

project(igl_utils)
set (igl_utils_VERSION_MAJOR 0)
set (igl_utils_VERSION_MINOR 1)

find_package(Eigen3 REQUIRED)
find_package(Threads REQUIRED)
include_directories(${IGL_INCLUDE_DIR})
include_directories(${EIGEN3_INCLUDE_DIR})

ADD_EXECUTABLE(obj2ply src/obj2ply.cc)
ADD_EXECUTABLE(ply2obj src/ply2obj.cc)
ADD_EXECUTABLE(obj2m src/obj2m.cc)
ADD_EXECUTABLE(objtl src/objtl.cc)
ADD_EXECUTABLE(objsa src/objsa.cc)
ADD_EXECUTABLE(objpca src/objpca.cc)
ADD_EXECUTABLE(objpca_align src/objpca_align.cc)
ADD_EXECUTABLE(objcenter src/objcenter.cc)
ADD_EXECUTABLE(objscale src/objscale.cc)
ADD_EXECUTABLE(objaddvn src/objaddvn.cc)
ADD_EXECUTABLE(plycenter src/plycenter.cc)
ADD_EXECUTABLE(tet2m src/tet2m.cc)
ADD_EXECUTABLE(iglremesh src/iglremesh.cc)

TARGET_LINK_LIBRARIES(iglremesh Threads::Threads)
TARGET_LINK_LIBRARIES(objsa Threads::Threads)
TARGET_LINK_LIBRARIES(objaddvn Threads::Threads)

