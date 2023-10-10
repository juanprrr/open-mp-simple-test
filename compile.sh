#!/bin/bash
mkdir bin
gcc -fopenmp src/pi.c -o bin/pi
gcc -fopenmp src/pi_loop.c -o bin/pi_loop
gcc -fopenmp src/e_loop.c -o bin/e_loop
gcc -fopenmp src/daxpy.c -o bin/daxpy

