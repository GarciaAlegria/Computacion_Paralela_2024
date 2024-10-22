riemann_mpi.c instrucciones:
mpicc -o mpiriem riemann_mpi.c -lm
mpirun -np 4 ./mpiriem a b
	- a y b son los límites del intervalo de la integral.

riemann.c instrucciones:
gcc riemann.c -o riem -lm
./riem a b
	- a y b son los límites del intervalo de la integral.

riemann_omp.c instrucciones:
gcc -fopenmp riemann_omp.c -o riem_omp -lm
./riem_omp a b num_threads
	- a y b son los límites del intervalo de la integral.
	- num_threads es el número de hilos a utilizar.

