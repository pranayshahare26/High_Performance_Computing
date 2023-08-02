#!/bin/bash

set -e

export CUR_ROOT=`pwd`
export TARS_DIR=${CUR_ROOT}/TARS
export MY_PREFIX=${HOME}/smokie/Pranay/Profiling/hpc/gcc
export MPI_HOME=/smokie/Pranay/Profiling/hpc/gcc

export PATH=${MPI_HOME}/bin:${MY_PREIFX}/bin:$PATH
export LD_LIBRARY_PATH=${MPI_HOME}/lib:${MY_PREFIX}/lib:$LD_LIBRARY_PATH
export CPATH=${MPI_HOME}/include:${MY_PREFIX}/include:$CPATH

export CC=mpicc
export FC=mpifort
export F77=mpifort
export MPICC=mpicc
export MPIFC=mpifort
export CFLAGS="-O2 -fPIC"
export FFLAGS="-O2 -fPIC"

#BLAS
cd ${CUR_ROOT}
rm -rf BLAS-3.11.0
tar -xvf ${TARS_DIR}/blas-3.11.0.tgz
cd BLAS-3.11.0
#Change compiler and FFLAGS in make.inc since, 
#environment variables are not influential
sed -i -e "s|^FC .*|FC = ${FC}|" make.inc
sed -i -e "s|^FFLAGS .*|& ${FFLAGS}|" make.inc
make -j 8
cp -f blas_LINUX.a ${MY_PREFIX}/lib/libblas.a


#LAPACK
cd ${CUR_ROOT}
rm -rf lapack-3.11.0
tar -xvf ${TARS_DIR}/lapack-3.11.0.tar.gz
cd lapack-3.11.0
cp make.inc.example make.inc
sed -i -e "s|^CC .*|FC = ${CC}|" make.inc
sed -i -e "s|^CFLAGS .*|& ${CFLAGS}|" make.inc
sed -i -e "s|^FC .*|FC = ${FC}|" make.inc
sed -i -e "s|^FFLAGS .*|& ${FFLAGS}|" make.inc
make -j 8
make cblaslib
cp -f *.a ${MY_PREFIX}/lib/

#FFTW
cd ${CUR_ROOT}
rm -rf fftw-3.3.10
tar -xvf ${TARS_DIR}/fftw-3.3.10.tar.gz
cd fftw-3.3.10
./configure --prefix=${MY_PREFIX} --enable-single --enable-openmp --enable-mpi
make -j 8
make install
make clean
./configure --prefix=${MY_PREFIX} --enable-long-double --enable-openmp --enable-mpi
make -j 8
make install
make clean
./configure --prefix=${MY_PREFIX} --enable-quad-precision --enable-openmp 
make -j 8
make install
make clean

echo "DONE!!"
