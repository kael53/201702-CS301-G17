#include "solver.h"
#include "omp.h"

//usage: numClauses numLiterals randSeed
int main(int argc, char **argv) {
	m = atoi(argv[1]);
	int n = atoi(argv[2]);
	unsigned int seed = atoi(argv[3]);

	unsigned int tseed = (seed + 1912812);
	int* clauses = (int *)malloc(sizeof(int) * 2 * m);

#ifdef __GNUC__
	for (int i = 0; i < 2 * m; ++i) {
		int c = ((int)rand_r(&tseed)) % (n + 1); //pick a literal at random

		if (((int)rand_r(&tseed)) % 2 == 0) { //negated or not?
			clauses[i] = c;
		}

		else {
			clauses[i] = c * (-1);
		}

		if ((i % 2) == 1 && clauses[i] == 0 && clauses[i - 1] == 0) { //to fix an empty clause (otherwise we have less than m clauses)
			clauses[i] = (((int)rand_r(&tseed)) % n) + 1;
		}
	}
#endif


#ifdef _WIN32
	srand(tseed);

	for (int i = 0; i < 2 * m; ++i) {
		int lit = ((int)rand()) % (n + 1); //pick a literal at random

		if (((int)rand()) % 2 == 0) { //negated or not?
			clauses[i] = lit;
		}

		else {
			clauses[i] = lit * (-1);
		}

		if ((i % 2) == 1 && clauses[i] == 0 && clauses[i - 1] == 0) { //to fix an empty clause (otherwise we have less than m clauses)
			clauses[i] = (((int)rand()) % n) + 1;
		}
	}
#endif

	Solver *solver = generateSolver(clauses, 2*m, n);
	double t0, t1;

	printf("Brute-Force\n");
	t0 = omp_get_wtime();
	printSolution(solve(solver));
	t1 = omp_get_wtime();
	printf("Time is %f\n", t1 - t0);

	printf("\nHillClimbing\n");
	t0 = omp_get_wtime();
	printSolution(solveWithHC(solver));
	t1 = omp_get_wtime();
	printf("Time is %f\n", t1 - t0);

	printf("\nSimulatedAnnealing\n");
	t0 = omp_get_wtime();
	printSolution(solveWithSA(solver, 10*m*n, 100, 0.85, n*m));
	t1 = omp_get_wtime();
	printf("Time is %f\n", t1 - t0);

	destroySolver(&solver);

	return 0;
}
