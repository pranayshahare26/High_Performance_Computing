#!/bin/bash
#SBATCH -N 2                                 # specify number of nodes
#SBATCH --ntasks-per-node=48                    # specify number of cores per node
#SBATCH --time=00:10:00                         # specify maximum duration of run in hours:minutes:seconds format
#SBATCH --job-name=lammps                       # specify job name
#SBATCH --error=lammps.%J.err                   # specify error file name
#SBATCH --output=lammps.%J.out                  # specify output file name
#SBATCH --partition=cpu                         # specify type of resource such as  CPU/GPU/High memory etc.

### Load the necessary modules and environment for running
ulimit -s unlimited                            #to avoid segmentation fault

# To load the lammps application
spack load lammps                      	       #load available lammps using spack            

#Change to the directory where the input files are located
cd /home/cdacapp/Application-Data/lammps/lammps-10Mar21/examples/melt

### Run the mpi program with mpirun
mpirun -np $SLURM_NTASKS lmp -in in.melt       #run command