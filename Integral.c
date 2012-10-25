#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#define TIMER_SCALE 1000000000
#define A -2.0f
#define B 2.0f
#define N 512

long int czas() {
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC, &t);
        return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char *argv[])
{
	int moje_id, liczba_proc, i, z;
	long int czas_pocz;
	double czas_ogolem;
	float h, czesciowe, x, y, x_pom, zsumowane;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &moje_id);
	MPI_Comm_size(MPI_COMM_WORLD, &liczba_proc);
	MPI_Status status;

	h = (B - A) / (float)N;
	z = N / liczba_proc;
	x = A + (float)moje_id * (float)z * h;
	y = x + (float)z * h;
	czesciowe = ((1/exp(x*x))+(1/exp(y*y))) / 2.0;
	x_pom = x;

	czas_pocz = czas();
	for(i = 1; i <= z - 1; i++)
	{
		x_pom = x_pom + h;
		czesciowe = czesciowe + (1/exp(x_pom*x_pom));
	}
	czesciowe = czesciowe * h;

	MPI_Reduce(&czesciowe, &zsumowane, 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

	czas_ogolem = (double)(czas() - czas_pocz)/(double)TIMER_SCALE;

	if(moje_id == 0) 
	{
		printf("Pole (wartosc calki) wynosi: %lf\n", zsumowane);
		printf("Czas wykonania programu: %lf\n", czas_ogolem);
	}

	MPI_Finalize();
	return 0;
}
