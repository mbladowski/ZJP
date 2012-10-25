#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#define TIMER_SCALE 1000000000
#define N 1000000

// Pomiar czasu
long int czas() 
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return ((t.tv_sec * TIMER_SCALE) + t.tv_nsec);
}

// Wersja sekwencyjna
double vectors_dot_seq()
{
	long int i;
	long long unsigned int zsumowane = 0;
	long int a[N], b[N], czas_pocz;
	double czas_ogolem;
	
	srand(time(NULL));

	for(i = 0; i < N; i++) 
	{
		a[i] = 1 + (int)( 1000.0 * rand() / ( RAND_MAX + 1.0 ) );
		b[i] = 1 + (int)( 1000.0 * rand() / ( RAND_MAX + 1.0 ) );
	}

	czas_pocz = czas();
	for(i = 0; i < N; i++) 
	{
		zsumowane += a[i] * b[i];
	}

	czas_ogolem = (double)(czas() - czas_pocz)/(double)TIMER_SCALE;

	return czas_ogolem;
}

// Wersja rownolegla
double vectors_dot_paral()
{
	long int i;
	long long unsigned int zsumowane = 0;
	long int a[N], b[N], czas_pocz;
	double czas_ogolem;
	
	srand(time(NULL));

	for(i = 0; i < N; i++) 
	{
		a[i] = 1 + (int)( 1000.0 * rand() / ( RAND_MAX + 1.0 ) );
		b[i] = 1 + (int)( 1000.0 * rand() / ( RAND_MAX + 1.0 ) );
	}

	czas_pocz = czas();

	#pragma omp parallel for default(shared) private(i) schedule(static,1) reduction(+:zsumowane)

	for(i = 0; i < N; i++) 
	{
		zsumowane += a[i] * b[i];
	}

	czas_ogolem = (double)(czas() - czas_pocz)/(double)TIMER_SCALE;

	return czas_ogolem;
}

// Funkcja main()
int main(int argc, char **argv)
{
	printf("Czas dzialania programu sekwencyjnego: %lf\n", vectors_dot_seq());	
	printf("Czas dzialania programu rownoleglego: %lf\n", vectors_dot_paral());
	return 0;
}
