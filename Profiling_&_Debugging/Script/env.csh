#!/usr/bin/csh

setenv CC mpicc
setenv CXX mpicxx
setenv FC mpifort
setenv F77 mpifort

setenv WRFIO_NCD_LARGE_FILE_SUPPORT 1

setenv MPI_HOME /home/hpcap/MPI_Installtion

setenv PATH ${MPI_HOME}/bin:$PATH
setenv LD_LIBRARY_PATH ${MPI_HOME}/lib
setenv CPATH ${MPI_HOME}/include

setenv NETCDF $HOME/home/hpcap/hpc/gcc

setenv PATH ${NETCDF}/bin:$PATH
setenv LD_LIBRARY_PATH ${NETCDF}/lib:$LD_LIBRARY_PATH
setenv CPATH $NETCDF/include:$CPATH

