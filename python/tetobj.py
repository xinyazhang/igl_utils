#!/usr/bin/env python3

import sys, os, pathlib
sys.path.append(str(pathlib.Path.home().joinpath('bin')))
sys.path.append(os.getcwd())

import py11igl as igl
import argparse
import numpy as np

def main():
    p = argparse.ArgumentParser(formatter_class=argparse.ArgumentDefaultsHelpFormatter)
    p.add_argument('file', help='Files to tet')
    p.add_argument('-o', help='output npz file', required=True)
    p.add_argument('--scale', help='Scale applied to the mesh', default=1.0, type=float)
    args = p.parse_args()

    inV, inF = igl.loadOBJ(args.file)
    V, T, F = igl.tet(inV, inF, 1.0)
    np.savez(args.o, V=V, T=T, F=F)

if __name__ == '__main__':
    main()
