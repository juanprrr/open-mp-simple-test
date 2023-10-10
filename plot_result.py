import os
import glob
import re
import numpy as np
import matplotlib.pyplot as plt

def plotter(path):
    files = [txt for txt in glob.glob(path)]
    # Log file format
    # num_threads = 4 computed pi = 3.141592653589683 in 0.071467046000180 seconds threads =  4 % error = -0.000000000003421
    pattern = re.compile("num_threads\s+=\s+(\d+).+in\s+(\d+.\d+).+error = (-*\d+.\d+)")
    total_tests = float(len(files))
    acc_runtimes = []
    acc_errors = []
    acc_speedups = []
    for txt in files:
        with open(txt) as fd:
            # get both time and thread lists
            threads, runtimes, errors = zip(*[(float(match.group(1)), float(match.group(2)), float(match.group(3))) for line in fd.readlines() for match in [pattern.search(line)] if match])

            # speedup T(1)/Tn
            speed_ups = [runtimes[0] / runt for runt in runtimes]

            # first iteration acc and error are empty
            if len(acc_runtimes) == 0:
                acc_runtimes = [0.0] * len(runtimes)
                acc_errors = [0.0] * len(runtimes)
                acc_speedups = [0.0] * len(runtimes)

            # add previous runtime
            acc_runtimes = [sum(runt) for runt in zip(runtimes, acc_runtimes)]

            # add previous error
            acc_errors = [sum(error) for error in zip(errors, acc_errors)]

            # add previous speedup
            acc_speedups = [sum(speedup) for speedup in zip(speed_ups, acc_speedups)]

    average_runtimes = [acc_time / total_tests for acc_time in acc_runtimes]
    average_errors = [acc_error / total_tests for acc_error in acc_errors]
    average_speedups = [acc_speedup / total_tests for acc_speedup in acc_speedups]

    # Create subplots
    fig, axs = plt.subplots(3, 1, figsize=(8, 12))
    fig.suptitle('Performance Metrics vs. Number of Threads')

    axs[0].plot(threads, average_runtimes, marker='o')
    axs[0].set_ylabel('Average Runtime (s)')
    axs[0].set_title('Threads and Avg Runtimes')

    axs[1].plot(threads, average_errors, marker='o', color='orange')
    axs[1].set_ylabel('Average % Error')
    axs[1].set_title('Threads and Avg Error')

    axs[2].plot(threads, average_speedups, marker='o', color='green')
    axs[2].set_xlabel('Num of Threads')
    axs[2].set_ylabel('Average Speedup')
    axs[2].set_title('Threads and Speedup')

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    #path_pi = "results_pi/*.txt"
    path_e  = "results_e/*.txt"
    #plotter(path_pi)
    plotter(path_e)
