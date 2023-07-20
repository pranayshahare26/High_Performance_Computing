#!/bin/bash

set -e

export CUR_ROOT=`pwd`
export TARS_DIR=${CUR_ROOT}/TARS
export MY_PREFIX=$HOME/smokie/Pranay/Profiling/hpc/gcc
export MPI_HOME=/home/smokie/Pranay/Profiling/hpc/gcc

export PATH=${MPI_HOME}/bin:${MY_PREIFX}/bin:$PATH
export LD_LIBRARY_PATH=${MPI_HOME}/lib:${MY_PREFIX}/lib:$LD_LIBRARY_PATH
export CPATH=${MPI_HOME}/include:${MY_PREFIX}/include:$CPATH

export CC=mpicc
export CXX=mpicxx
export FC=mpifort
export F77=mpifort
export SEQ_CC=gcc

export CFLAGS="-O2 -fPIC"
export CXXFLAGS="-O2 -fPIC"
export FFLAGS="-O2 -fPIC"
export FCFLAGS="-O2 -fPIC"

#ZLIB
cd ${CUR_ROOT}
rm -rf zlib-1.2.13/
tar -xvf ${TARS_DIR}/zlib-1.2.13.tar.gz
cd zlib-1.2.13/
./configure --prefix=${MY_PREFIX}
make
#make check
make install

#SZIP
cd ${CUR_ROOT}
rm -rf szip-2.1.1
tar -xvf ${TARS_DIR}/szip-2.1.1.tar.gz
cd szip-2.1.1
./configure --prefix=${MY_PREFIX}
make 
#make check 
make install

#HDF5
cd ${CUR_ROOT}
CC=mpicc
FC=mpifort
rm -rf hdf5-1.14.1-2
tar -xvf ${TARS_DIR}/hdf5-1.14.1-2.tar.gz
cd hdf5-1.14.1-2
./configure --prefix=${MY_PREFIX} \
	--enable-parallel \
	--enable-fortran \
	--with-zlib=${MY_PREFIX} \
	--with-szlib=${MY_PREFIX}
make -j 8
#make check 
make install

#PNETCDF
cd ${CUR_ROOT}
rm -rf pnetcdf-1.12.3
tar -xvf ${TARS_DIR}/pnetcdf-1.12.3.tar.gz
cd pnetcdf-1.12.3
./configure --prefix=${MY_PREFIX} 
make -j 8
#make check
#make ptest
make install

#NETCDF-C
cd ${CUR_ROOT}
rm -rf netcdf-c-4.9.2/
tar -xvf ${TARS_DIR}/netcdf-c-4.9.2.tar.gz
cd netcdf-c-4.9.2/
export LDFLAGS="-L${MY_PREFIX}/lib"
export CPPFLAGS="-I${MY_PREFIX}/include"
export LIBS="-lpnetcdf -lhdf5 -lhdf5_fortran -lhdf5_hl -lhdf5_hl_fortran -lsz -lz" 
./configure --prefix=${MY_PREFIX} --enable-pnetcdf
make
make check 
make install

#NETCDF-F
cd ${CUR_ROOT}
rm -rf netcdf-fortran-4.6.1
tar -xvf ${TARS_DIR}/netcdf-fortran-4.6.1.tar.gz
cd netcdf-fortran-4.6.1
export LDFLAGS="-L${MY_PREFIX}/lib"
export CPPFLAGS="-I${MY_PREFIX}/include"
export LIBS="-lnetcdf -lpnetcdf -lhdf5 -lhdf5_fortran -lhdf5_hl -lhdf5_hl_fortran -lsz -lz" 
./configure --prefix=${MY_PREFIX} 
make
make check 
make install

echo "DONE!"
