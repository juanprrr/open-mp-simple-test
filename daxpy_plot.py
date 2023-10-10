import re
import numpy as np
import matplotlib.pyplot as plt

def parse_results_file(filename):
    threads = []
    runtimes = []
    N_values = []

    with open(filename, 'r') as file:
        for line in file:
            match = re.search(r'num_threads = (\d+) computed daxpy in (\S+) seconds N = (\d+)\n', line)
            if match:
                threads.append(int(match.group(1)))
                runtimes.append(float(match.group(2)))
                N_values.append(int(match.group(3)))

    return threads, runtimes, N_values

def calculate_averages(threads, runtimes, N_values):
    unique_N_values = np.unique(N_values)
    avg_runtimes = []
    avg_speedups = []

    for N in unique_N_values:
        N_runtimes = [runtimes[i] for i in range(len(N_values)) if N_values[i] == N]
        
        avg_runtime = np.mean(N_runtimes)
        avg_runtimes.append(avg_runtime)

        avg_speedup = [N_runtimes[0] / rt for rt in N_runtimes]
        avg_speedup = np.mean(avg_speedup)
        avg_speedups.append(avg_speedup)

    return unique_N_values, avg_runtimes, avg_speedups

def plot_results(filename):
    threads, runtimes, N_values = parse_results_file(filename)
    unique_N_values, avg_runtimes, avg_speedups = calculate_averages(threads, runtimes, N_values)

    plt.figure(figsize=(12, 6))

    plt.subplot(1, 2, 1)
    for N in unique_N_values:
        N_runtimes = [avg_runtimes[i] for i in range(len(unique_N_values)) if unique_N_values[i] == N]
        N_threads = [threads[i] for i in range(len(unique_N_values)) if unique_N_values[i] == N]
        plt.plot(N_threads, N_runtimes, marker='o', label=f'N = {N}')
    plt.xlabel('Number of Threads')
    plt.ylabel('Average Runtime (s)')
    plt.title('Average Runtime vs. Number of Threads')
    plt.legend()

    plt.subplot(1, 2, 2)
    for N in unique_N_values:
        N_speedups = [avg_speedups[i] for i in range(len(unique_N_values)) if unique_N_values[i] == N]
        N_threads = [threads[i] for i in range(len(unique_N_values)) if unique_N_values[i] == N]
        plt.plot(N_threads, N_speedups, marker='o', label=f'N = {N}')
    plt.xlabel('Number of Threads')
    plt.ylabel('Average Speedup')
    plt.title('Average Speedup vs. Number of Threads')
    plt.legend()

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    filename = "results_daxpy/single.txt" 
    plot_results(filename)
    filename = "results_daxpy/single.txt" 
    plot_results(filename)