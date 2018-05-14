#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "common.h"
#include "solution.h"

typedef struct {
	int	*clauses;
	int	numLiterals;
	int	size;
} Solver;

Solver *generateSolver(int *clauses, int cSize, int numLiterals);

void destroySolver(Solver **solver);

Solution *solve(Solver *solver);

Solution *solveWithHC(Solver *solver);
Solution *solveWithSA(Solver *solver, const double T0, const double tMin, const double alpha, const int nOfIter);

#endif
