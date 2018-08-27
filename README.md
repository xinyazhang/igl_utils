# IGL UTILS
A set of command line utilities that process geometry files with libigl.

## List of Binaries
* obj2ply: Convert Wavefront OBJ files to Stanford PLY files.
* obj2m: Convert Wavefront OBJ files to Mathematica BoundaryMeshRegion object.
* objtl: Translate geometry stored in the Wavefront OBJ file.

## Build
To build

    mkdir build
    cd build
    cmake -DIGL_INCLUDE_DIR=$PATH_TO_LIB_IGL -DEIGEN3_INCLUDE_DIR=$PATH_TO_EIGEN3 ..
    make

## Install

Copy the binaries to anywhere you like.
No `make install` target is provided since this is really a tiny tool.

## Use
### obj2ply
```obj2ply <obj files>```

No need to specify the output file names. This tool will output PLY files with
the same base name of OBJ files.  Files without .obj as the extension will be
ignored (case sensitive).

### obj2m
```obj2m <obj files>```

### objtl
```obj2m <input obj file> <X> <Y> <Z> <output obj file>```

Translate the geometry stored in the input file by XYZ and write the results
to the output file.
