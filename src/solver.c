#include "solver.h"
#include <math.h>

Solver *generateSolver(int *clauses, int cSize, int numLiterals) {
        Solver *solver = (Solver *) malloc(sizeof(Solver));

        solver->clauses = (int *) malloc(sizeof(int) * cSize);
        memcpy(solver->clauses, clauses, sizeof(int) * cSize);

        solver->numLiterals = numLiterals;
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
        long long int i, j;
	char *literals = (char *) malloc(sizeof(char) * solver->numLiterals);
        memset(literals, 0, sizeof(char) * solver->numLiterals);

	long long int power = pow(2, solver->numLiterals);
	Solution *curSol, *bestSol = 0;
	for (i = 0; i < power; i++) {
		curSol = generateSolution(solver->clauses, solver->size, literals, solver->numLiterals);
		calculateScore(curSol);
		if (!bestSol || curSol->score > bestSol->score) {
			destroySolution(&bestSol);
			bestSol = curSol;
		} else destroySolution(&curSol);
		if (literals[solver->numLiterals - 1]) {
			for (j = solver->numLiterals - 2; j >= 0 && literals[j]; --j)
				literals[j] ^= 1;
			if (j >= 0)
				literals[j] ^= 1;
		}
		literals[solver->numLiterals - 1] ^= 1;
	}

        return bestSol;
}

Solution *solveWithHC(Solver *solver) {
	int i, oldScore = -1;

	Solution *solution = generateEmptySolution(solver->clauses, solver->size, solver->numLiterals);
	calculateScore(solution);
	while (oldScore != solution->score && (oldScore = solution->score) < solver->numLiterals) {
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

Solution *solveWithSA(Solver *solver, const double T0, const double Tmin, const double alpha, const int nOfIter) {
	int i;
	double T = T0;

	srand((unsigned) time(0));

	Solution *curSol = generateEmptySolution(solver->clauses, solver->size, solver->numLiterals), *bestSol = 0;
	calculateScore(curSol);
	if (!(solver->size > 0 && solver->numLiterals > 0)) {
		return curSol;
	}

	//for (T = T0; T > Tmin; T *= alpha) {
		for (i = 0; i < nOfIter; i++) {
			if (!bestSol || curSol->score > bestSol->score) {
				destroySolution(&bestSol);
				bestSol = curSol;
			}

			Solution *newSol = copySolution(curSol);
			newSol->literals[rand() % solver->numLiterals] ^= 1;
			calculateScore(newSol);
			if (exp((curSol->score - newSol->score) / T) * 100 > (rand() % 101)) {
				if (bestSol != curSol)
					destroySolution(&curSol);
				curSol = newSol;
			}
			T *= alpha;
		}

		/*if (2 * bestSol->score == solver->size)
			break;*/
	//}

	if (bestSol != curSol)
		destroySolution(&curSol);

	return bestSol;
}
