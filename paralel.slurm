#!/bin/bash
#SBATCH --job-name=projeto_gabriel
#SBATCH --nodes=1
#SBATCH --partition=express
#SBATCH --mem=500M
echo Output do Job $SLURM_JOB_ID
./mpi5
