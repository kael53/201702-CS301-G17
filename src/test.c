#include "solver.h"


int main(int argc, char **argv) {
	char clauses[] = { 1, 2, 3, 4, 5, 6, -8, -9, 7, 0 };

	Solver *solver = generateSolver(clauses, 10, 9);

	printf("Brute-Force\n");

	printSolution(solve(solver));

	printf("\nHillClimbing\n");

	printSolution(solveWithHC(solver));

	printf("\nSimulatedAnnealing\n");

	printSolution(solveWithSA(solver, 0.0001, 0.9, 100));

	destroySolver(&solver);

	return 0;
}
