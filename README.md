## Taller 1 Arquitectura de Computadores II

### Requerimientos
    - Compilador gcc
    - git 
    - Tener una shell que ejecute scripts de bash, en este caso se usó git bash
    - Python 3.x con matplotlib y numpy.

### Pasos para ejecutar:
    - git clone https://github.com/juanprrr/open-mp-simple-test
    - cd open-mp-simple-test
    - Compilar los programas que se encuentran en src, pi.c, pi_loop.c, e_loop.c, daxpy.c ejecutando el comando ./compile.sh
    - Generar resultados de pi_loop.c usando multithreading de OpenMP: ./run_pi.sh
    - Generar resultados de e_loop.c usando multithreading de OpenMP: ./run_e.sh
    - Generar resultados de daxpy.c : bin/daxpy
    - Generar graficas de pi_loop.c y e_loop.c: ejecutar script plot_result.py
    - Generar graficas de daxpy.c: ejecutar script daxpy_plot.py
### Resultados