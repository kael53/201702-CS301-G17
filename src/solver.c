#include "solver.h"

Solver *generateSolver(char *clauses, int cSize, int literals) {
        Solver *solver = (Solver *) malloc(sizeof(Solver));

        solver->clauses = (char *) malloc(sizeof(char) * cSize);
        memcpy(solver->clauses, clauses, sizeof(char) * cSize);

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

Solution *solveWithHC(Solver *solver) {
	int i, oldScore = -1;

	Solution *solution = generateEmptySolution(solver->clauses, solver->size, solver->literals);
	calculateScore(solution);
	while (oldScore != solution->score && (oldScore = solution->score) < solver->literals) {
		for (i = 0; i < solution->lSize; i++) {
			int tempScore = solution->score;

			solution->literals[i] ^= 1;
			calculateScore(solution);

			if (solution->score < tempScore) {
				solution->literals[i] ^= 1;
				calculateScore(solution);
			}
		}
	}

	return solution;
}

Solution *solveWithSA(Solver *solver, const double Tmin, const double alpha, const int nOfIter) {
	int i;
	double T;

	srand((unsigned) time(0));

	Solution *curSol = generateEmptySolution(solver->clauses, solver->size, solver->literals), *bestSol = 0;
	calculateScore(curSol);
	for (T = 1.0; T > Tmin; T *= alpha) {
		for (i = 0; i < nOfIter; i++) {
			if (!bestSol || curSol->score > bestSol->score) {
				destroySolution(&bestSol);
				bestSol = curSol;
			}

			Solution *newSol = copySolution(curSol);
			newSol->literals[rand() % solver->literals] ^= 1;
			calculateScore(newSol);
			if (exp((curSol->score - newSol->score) / T) * 100 > (rand() % 101)) {
				if (bestSol != curSol)
					destroySolution(&curSol);
				curSol = newSol;
			}
		}
	}

	if (bestSol != curSol)
		destroySolution(&curSol);

	return bestSol;
}
