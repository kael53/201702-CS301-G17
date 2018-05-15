#include "solver.h"
#include "omp.h"


int main(int argc, char **argv) {
	int c1[] = {0};
	Solver *s1 = generateSolver(c1, 0, 0);
	printf("Brute-Force\n");
	printSolution(solve(s1));
	printf("\nHillClimbing\n");
	printSolution(solveWithHC(s1));
	printf("\nSimulatedAnnealing\n");
	printSolution(solveWithSA(s1, 10000, 0, 0.85, 10000));
	destroySolver(&s1);

	int c2[] = { 1, 2, -1, 3, 4, 0 };
	Solver *s2 = generateSolver(c2, 6, 4);
	printf("Brute-Force\n");
	printSolution(solve(s2));
	printf("\nHillClimbing\n");
	printSolution(solveWithHC(s2));
	printf("\nSimulatedAnnealing\n");
	printSolution(solveWithSA(s2, 10000, 0, 0.85, 10000));
	destroySolver(&s2);

	return 0;
}
