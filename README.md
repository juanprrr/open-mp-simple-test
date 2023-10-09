## Taller 1 Arquitectura de Computadores II

Compilar  pi
gcc -fopenmp src_pi/pi.c -o bin/pi
gcc -fopenmp src_pi/pi_loop.c -o bin/pi_loop

ejecutar pi
bin/pi
bin/pi_loop


clean folder

rm -r results_pi/*.txt
rm -r results_e/*.txt