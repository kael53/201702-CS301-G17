#include "solver.h"

Solver *generateSolver(char *clauses, int cSize, int literals) {
        Solver *solver = (Solver *) malloc(sizeof(Solver));

        solver->clauses = (char *) malloc(sizeof(char) * cSize);
        memcpy(solver->clauses, clauses, cSize);

        solver->literals = literals;
        solver->size = cSize;

        return solver;
}

void destroySolver(Solver **solver) {
	if(!*solver) return;
        free((*solver)->clauses);
        free(*solver);
        *solver = 0;
}

Solution *solve(Solver *solver) {
        int i, j;
        char *literals = (char *) malloc(sizeof(char) * (solver->literals + 1));
        memset(literals, 0, sizeof(char) * (solver->literals + 1));

	int power = pow(2, solver->literals);
	Solution *curSol, *bestSol = 0;
	for (i = 0; i < power; i++) {
		curSol = generateSolution(solver->clauses, solver->size, literals, solver->literals);
		calculateScore(curSol);
		if (!bestSol || curSol->score > bestSol->score) {
			destroySolution(&bestSol);
			bestSol = curSol;
		} else destroySolution(&curSol);
		if (literals[solver->literals - 1]) {
			for (j = solver->literals - 2; j >= 0 && literals[j]; j--)
				literals[j] ^= 1;
			literals[j] ^= 1;
		}
		literals[solver->literals - 1] ^= 1;
	}

        return bestSol;
}

