/*

This program will numerically compute the Taylor expansion 
for the approximation of euler constant. 
        e = 1/1! + 1/2! + 1/3! + 1/4! + ... + 1/n!

*/
#include <stdio.h>
#include <omp.h>

static int num_terms = 10000000;
double e;
double reference_e = 2.718281828459045; 

int main() {
    int num_threads = omp_get_num_procs(); 
    double start_time, run_time;

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
        printf("computed e = %3.15f in %3.25f seconds threads = %d %% error = %3.15f\n", e, run_time, t, (e - reference_e) * 100.0 / reference_e);
    }

    return 0;
}
