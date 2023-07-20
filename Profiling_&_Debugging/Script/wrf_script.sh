cd WRF/
export MPI_HOME=/home/hpcap/MPI_Installtion

export PATH=${MPI_HOME}/bin:${MY_PREIFX}/bin:$PATH
export LD_LIBRARY_PATH=${MPI_HOME}/lib:${MY_PREFIX}/lib:$LD_LIBRARY_PATH
export CPATH=${MPI_HOME}/include:${MY_PREFIX}/include:$CPATH
export NETCDF=$HOME/home/hpcap/hpc/gcc


export PATH=$NETCDF/bin:$PATH
export LD_LIBRARY_PATH=$NETCDF/lib:$LD_LIBRARY_PATH
export CPATH=$NETCDF/include:$CPATH

export WRFIO_NCD_LARGE_FILE_SUPPORT=1
