#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <mpi.h>
#define TIMER_SCALE 1000000000
#define N 100000
#define MIN 0
#define MAX 100

long int czas() 
{
        struct timespec t;
        clock_gettime(CLOCK_MONOTONIC, &t);
        return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

int main(int argc, char *argv[])
{
	int moje_id, liczba_proc, zsumowane, i, k = 0;
	long int czas_pocz;
	double x, y, pi, czas_ogolem;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &moje_id);
	MPI_Comm_size(MPI_COMM_WORLD, &liczba_proc);
	MPI_Status status;

	srand(time(NULL));

	czas_pocz = czas();

	for(i = (moje_id * N / liczba_proc) + 1; i <= (moje_id + 1) * N / liczba_proc; i++)
	{
		x = ((double)rand() / RAND_MAX);
		y = ((double)rand() / RAND_MAX);
		if((x * x + y * y) <= 1) k++;
	}

	MPI_Reduce(&k, &zsumowane, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	czas_ogolem = (double)(czas() - czas_pocz)/(double)TIMER_SCALE;
	pi = 4 * (double)zsumowane / N;

	if(moje_id == 0) 
	{
		printf("Liczba pi wg programu rownoleglego: %lf\n", pi);
		printf("Czas wykonania programu: %lf\n", czas_ogolem);
	}

	MPI_Finalize();
	return 0;
}
