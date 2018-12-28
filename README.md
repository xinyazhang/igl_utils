# IGL UTILS
A set of command line utilities that process geometry files with libigl.

## List of Binaries
* obj2ply: Convert Wavefront OBJ files to Stanford PLY files.
* obj2m: Convert Wavefront OBJ files to Mathematica BoundaryMeshRegion object.
* tet2m: Translate [tetgen](http://www.tetgen.org/) output files to Mathematica MeshRegion object.
* objtl: Translate geometry stored in the Wavefront OBJ file.
* objcenter: Translate geometry so that the mean of its vertices is the origin.
* iglremesh: Remesh through upsampling and then downsampling
    + This code is derived from [Josh V's remesh-script](https://github.com/the13fools/remesh-script)
    + Unlike the other binaries, the iglremesh is licensed under MPL 2.0. See
      LICENSE.MPL2 for the details.

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
`obj2ply <obj files>`

No need to specify the output file names. This tool will output PLY files with
the same base name of OBJ files.  Files without .obj as the extension will be
ignored (case sensitive).

### obj2m and tet2m
`obj2m <obj files>`
`tet2m <prefix of tetgen output files> [-o <output file>]`

obj2m places the output to files of the same prefix with .m suffix.

tet2m prints the output to standard output if `-o` is not specified.

### objtl
`objtl <input obj file> <X> <Y> <Z> <output obj file>`

Translate the geometry stored in the input file by XYZ and write the results
to the output file.

### objcenter
`objcenter <input obj file> <output obj file>`
