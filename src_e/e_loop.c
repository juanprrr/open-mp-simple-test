/*

This program will numerically compute the Taylor expansion 
for the approximation of euler constant. 
        e = 1/1! + 1/2! + 1/3! + 1/4! + ... + 1/n!
The program was parallelized using OpenMP by adding just
four lines 

(1) A line to include omp.h -- the include file that 
contains OpenMP's function prototypes and constants.

(2) A pragma that tells OpenMP to create a team of threads

(3) A pragma to cause one of the threads to print the
number of threads being used by the program.

(4) A pragma to split up loop iterations among the team
of threads.  This pragma includes 2 clauses to (1) create a 
private variable and (2) to cause the threads to compute their
sums locally and then combine their local sums into a 
single global value.

History: Written by Tim Mattson, 11/99.

*/#include <stdio.h>
#include <omp.h>

static int num_terms = 1000000;
double e;
double reference_e = 2.718281828459045; 

int main() {
    int num_threads = omp_get_num_procs(); 
    double start_time, run_time;
    double tick = omp_get_wtick();

    for (int t = 1; t <= num_threads; t++) {
        e = 1.0; 
        omp_set_num_threads(t);
        start_time = omp_get_wtime();
        
#pragma omp parallel
{
    #pragma omp single
    printf("num_threads = %d ", omp_get_num_threads());

    double term = 1.0;

    #pragma omp for reduction(+:e) 
    for (int i = 1; i <= num_terms; i++) {
        term /= i;
        e += term;
    }
}
        run_time = (omp_get_wtime() - start_time);
        printf("computed e = %3.15f in %3.15f seconds threads = %d %% error = %3.15f\n", e, run_time, t, (e - reference_e) * 100.0 / reference_e);
    }

    return 0;
}
