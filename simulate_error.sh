#!/bin/bash


gcc -Wall -pedantic -o generate_phred-score.o /data/measuring_error/NGS_simulation/generate_phred-score.c
./generate_phred-score.o /data/measuring_error/NGS_simulation/SRR30257158_no-phred.fastq SRR30257158_simulation.fastq

./measure-errors.sh SRR30257158_simulation.fastq

display error_cumulative_NGS-simulation.png &
