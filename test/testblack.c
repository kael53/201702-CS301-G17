#include "solver.h"
#include "omp.h"

//usage: numClauses numLiterals randSeed
int main(int argc, char **argv) {
	printf("1. Empty formula\n"); //expected output: 0
	int* c = (int *)malloc(sizeof(int) * 0);
	Solver *s = generateSolver(c, 0, 0);
	printSolution(solve(s));
	printSolution(solveWithHC(s));
	printSolution(solveWithSA(s, 10000, 0, 0.85, 10000));
	free(c);

	printf("2. A satisfiable formula of size 1\n"); //expected output: 1
	c = (int *)malloc(sizeof(int) * 2);
	c[0] = 1;
	c[1] = -1;
	s = generateSolver(c, 2, 2);
	printSolution(solve(s));
	printSolution(solveWithHC(s));
	printSolution(solveWithSA(s, 10000, 0, 0.85, 10000));
	free(c);

	printf("3. An unsatisfiable formula of size 2\n"); //expected output: 1
	c = (int *)malloc(sizeof(int) * 4);
	c[0] = 1;
	c[1] = 0;
	c[2] = -1;
	c[3] = 0;
	s = generateSolver(c, 4, 1);
	printSolution(solve(s));
	printSolution(solveWithHC(s));
	printSolution(solveWithSA(s, 10000, 0, 0.85, 10000));
	free(c);

	printf("4. A fully satisfiable formula of size 10 with 1 literal\n"); //expected output: 10
	c = (int *)malloc(sizeof(int) * 20);
	for (int i = 0; i < 20; i++)
		c[i] = 1;
	s = generateSolver(c, 20, 1);
	printSolution(solve(s));
	printSolution(solveWithHC(s));
	printSolution(solveWithSA(s, 10000, 0, 0.85, 10000));
	free(c);

	printf("5. A fully satisfiable formula of size 8 with 16 literals\n"); //expected output: 8
	c = (int *)malloc(sizeof(int) * 16);
	for (int i = 0; i < 16; i++)
		c[i] = i + 1;
	s = generateSolver(c, 16, 16);
	printSolution(solve(s));
	printSolution(solveWithHC(s));
	printSolution(solveWithSA(s, 10000, 0, 0.85, 10000));
	free(c);

	printf("6. An unsatisfiable formula of size 4 with 4 literals\n"); //expected output: at most 3
	c = (int *)malloc(sizeof(int) * 8);
	c[0] = 1;
	c[1] = 0;
	c[2] = -1;
	c[3] = 0;
	for (int i = 4; i < 8; i++)
		c[i] = rand() % 5;
	s = generateSolver(c, 8, 4);
	printSolution(solve(s));
	printSolution(solveWithHC(s));
	printSolution(solveWithSA(s, 10000, 0, 0.85, 10000));
	free(c);

	printf("7. A random clause of size 32 with 16 literals \n");
	c = (int *)malloc(sizeof(int) * 64);
	for (int i = 0; i < 64; i++)
		c[i] = rand() % 17;
	s = generateSolver(c, 64, 16);
	printSolution(solve(s));
	printSolution(solveWithHC(s));
	printSolution(solveWithSA(s, 10000, 0, 0.85, 10000));
	free(c);

	return 0;
}
