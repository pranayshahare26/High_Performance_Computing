#!/bin/bash

export CC=mpicc
export CXX=mpicxx
export FC=mpifort
export F77=mpifort

export WRFIO_NCD_LARGE_FILE_SUPPORT=1

export MPI_HOME=/home/hpcap/MPI_Installtion

export PATH=${MPI_HOME}/bin:$PATH
export LD_LIBRARY_PATH=${MPI_HOME}/lib:$LD_LIBRARY_PATH
export CPATH=${MPI_HOME}/include:$CPATH

export NETCDF=$HOME/home/hpcap/hpc/gcc

export PATH=${NETCDF}/bin:$PATH
export LD_LIBRARY_PATH=${NETCDF}/lib:$LD_LIBRARY_PATH
export CPATH=$NETCDF/include:$CPATH
