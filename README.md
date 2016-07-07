# obj2ply
A simple tool that converts Wavefront OBJ files to Stanford PLY files.

## Build
To build

    mkdir build
    cd build
    cmake -DIGL_INCLUDE_DIR=$PATH_TO_LIB_IGL -DEIGEN3_INCLUDE_DIR=$PATH_TO_EIGEN3 ..
    make

## Install

Copy obj2ply to anywhere you like.
No `make install` target is provided since this is really a tiny tool.

## Use
```obj2ply <obj files>```

No need to specify the output file names. This tool will output PLY files with
the same base name of OBJ files.  Files without .obj as the extension will be
ignored (case sensitive).
