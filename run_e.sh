#!/bin/bash
for i in {1..100}
do
    ./bin/e_loop > results_e/e_loop_$i.txt
done
rm -rf bin/*