#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define n_values 4
#define N0 12500000
#define N1 13500000
#define N2 17000000
#define N3 30000000

/** Multithread will execute daxpy using the 4 cores that this system has

*/
#define num_exec_multi 25
#define num_exec_single 100

void daxpy_single_thread(double a, double *x, double *y, int N, int num_threads, FILE *output_file) {

    double start_time, run_time;

    omp_set_num_threads(1);
    start_time = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        y[i] = a * x[i] + y[i];
    }

    if (output_file) {
            fprintf(output_file, "num_threads = %d computed daxpy in %3.15f seconds N = %d\n", 1, omp_get_wtime() - start_time, N);
            
        }

}

void daxpy_multi_thread(double a, double *x, double *y, int N, int num_threads, FILE *output_file) {
    double run_time, start_time;

    for (int t = 1; t <= num_threads; t++) {
        omp_set_num_threads(t);
        start_time = omp_get_wtime();

        #pragma omp parallel default(none) shared(N, x, y, a) private(run_time)
        {
            int i;

            #pragma omp for
            for (i = 0; i < N; i++) {
                y[i] = a * x[i] + y[i];
            }        
        }

        run_time = omp_get_wtime() - start_time;
        
        if (output_file) {
            fprintf(output_file, "num_threads = %d computed daxpy in %3.15f seconds N = %d\n", t, run_time, N);
        }
    }
}

int main() {
    double a = 3.14;
    int N_values[n_values] = {N0, N1, N2, N3};
    double *x_ptrs[n_values];
    double *y_ptrs[n_values];
    int num_threads = omp_get_num_procs();

    
    char multi[50];
    sprintf(multi, "results_daxpy/multi.txt");
    FILE *output_file = fopen(multi, "w"); 

    for (int k = 0; k < num_exec_multi; k++) {
        for (int i = 0; i < n_values; i++) {
            x_ptrs[i] = (double *)malloc(N_values[i] * sizeof(double));
            y_ptrs[i] = (double *)malloc(N_values[i] * sizeof(double));

            for (int j = 0; j < N_values[i]; j++) {
                x_ptrs[i][j] = (double)rand() / RAND_MAX;
                y_ptrs[i][j] = (double)rand() / RAND_MAX;
            }

            daxpy_multi_thread(a, x_ptrs[i], y_ptrs[i], N_values[i], num_threads, output_file);
            
            free(x_ptrs[i]);
            free(y_ptrs[i]);
        }
    }

    fclose(output_file);

    char single[50];
    sprintf(single, "results_daxpy/single.txt");
    FILE *single_file = fopen(single, "w");

    for (int k = 0; k < num_exec_single; k++)
    {
        for (int i = 0; i < n_values; i++)
        {
           
            x_ptrs[i] = (double *)malloc(N_values[i] * sizeof(double));
            y_ptrs[i] = (double *)malloc(N_values[i] * sizeof(double));

            for (int j = 0; j < N_values[i]; j++) {
                x_ptrs[i][j] = (double)rand() / RAND_MAX;
                y_ptrs[i][j] = (double)rand() / RAND_MAX;
            }

            daxpy_single_thread(a, x_ptrs[i], y_ptrs[i], N_values[i], num_threads, output_file);
            
            free(x_ptrs[i]);
            free(y_ptrs[i]);
        }
    }
    fclose(single_file);

    return 0;
}
