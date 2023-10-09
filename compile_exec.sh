#!/bin/bash
mkdir bin
gcc -fopenmp src_pi/pi.c -o bin/pi
gcc -fopenmp src_pi/pi_loop.c -o bin/pi_loop
gcc -fopenmp src_e/e_loop.c -o bin/e_loop

bin/pi

bin/pi_loop

bin/e_loop
