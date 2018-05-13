#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "common.h"
#include "solution.h"

typedef struct {
	char	*clauses;
	int	literals;
	int	size;
} Solver;

Solver *generateSolver(char *clauses, int cSize, int literals);

void destroySolver(Solver **solver);

Solution *solve(Solver *solver);

Solution *solveWithHC(Solver *solver);
Solution *solveWithSA(Solver *solver, const double tMin, const double alpha, const int nOfIter);

#endif
