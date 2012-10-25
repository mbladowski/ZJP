all: VectorsDot MonteCarloSeq MonteCarloParal Integral

VectorsDot : VectorsDot.c
	gcc -fopenmp VectorsDot.c -lrt -o VectorsDot

MonteCarloSeq : MonteCarloSeq.c
	gcc MonteCarloSeq.c -lrt -o MonteCarloSeq

MonteCarloParal : MonteCarloParal.c
	mpicc MonteCarloParal.c -lrt -o MonteCarloParal

Integral : Integral.c
	mpicc Integral.c -lrt -lm -o Integral

