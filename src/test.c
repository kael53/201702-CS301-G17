#include "solver.h"


int main(int argc, char **argv) {
	char clauses[] = { 1, 2, 3, 4, 5, 6, -8, -9, 7, 0 };

	Solver *solver = generateSolver(clauses, 10, 9);

	printSolution(solve(solver));

	destroySolver(&solver);

	return 0;
}
