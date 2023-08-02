#!/bin/bash

which mpicc
sleep 10

cmake ../cmake/ \
	-DBUILD_MPI=yes \
	-DBUILD_OMP=yes \
	-DLAMMPS_MACHINE=mpi \
	-DCMAKE_CXX_COMPILER=mpicxx \
	-DCMAKE_C_COMPILER=mpicc \
	-DCMAKE_Fortran_COMPILER=mpifort \
	-DCMAKE_CXX_FLAGS="-O2 -fPIC -std=c++11" \
	-DCMAKE_C_FLAGS="-O2 -fPIC -std=c++11" \
	-DCMAKE_Fortran_FLAGS="-O2 -fPIC -std=c++11" \
	-DBUILD_SHARED_LIBS=yes \
	-DFFT="FFTW3" \
	-DFFT_SINGLE=YES \
	-DFFTW3_INCLUDE_DIR="$HOME/smokie/Pranay/Profiling/hpc/gcc/include/" \
	-DFFTW3_LIBRARY="$HOME/smokie/Pranay/Profiling/hpc/gcc/lib/libfftw3f.a" 

