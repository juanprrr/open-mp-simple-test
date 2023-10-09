#!/bin/bash
for i in {1..100}
do
    ./bin/pi_loop > results_pi/pi_loop_$i.txt
done
rm -rf bin/*