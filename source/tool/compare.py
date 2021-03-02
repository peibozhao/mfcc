#!/usr/bin/env python

import sys
import numpy as np

fname1 = sys.argv[1]
fname2 = sys.argv[2]
print_thresh = 0.0001

arr1 = np.loadtxt(fname1)
arr2 = np.loadtxt(fname2)

ndim = arr1.ndim
dims = arr1.shape

if ndim != arr2.ndim:
    print("Ndim is not same {} {}".format(ndim, arr2.ndim))
    exit(-1)

if dims != arr2.shape:
    print("Dims is not same {} {}".format(dims, arr2.shape))
    exit(-1)

arr_diff = arr1 - arr2

idxs = np.where(np.abs(arr_diff) > print_thresh)

np.set_printoptions(threshold=np.inf)
print(idxs)
print(arr_diff[idxs])
