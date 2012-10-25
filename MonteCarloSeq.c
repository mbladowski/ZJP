#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	int i, k = 0;
	long int czas_pocz;
	double x, y, pi, czas_ogolem;

	srand(time(NULL));

	czas_pocz = czas();

	for(i = 0; i < N; i++)
	{
		x = ((double)rand() / RAND_MAX);
		y = ((double)rand() / RAND_MAX);
		if((x * x + y * y) <= 1) k++;
	}

	czas_ogolem = (double)(czas() - czas_pocz)/(double)TIMER_SCALE;
	pi = 4 * (double)k / N;

	printf("Liczba pi wg programu sekwencyjnego: %lf\n", pi);
	printf("Czas wykonania programu: %lf\n", czas_ogolem);

	return 0;
}
