#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "common.h"

typedef struct {
	int	*clauses; //This has pairs of literal indices in it. (1-based indices, eg. [1, -5, 2, -3, 4, 0] ==> (1 V -5) ^ (2 V -3) ^ 4)
	int	*literals; //This has the assigned values of the literals. (0 or 1, eg. [1, 1, 0, 1, 0])
	int	score; //This shows how many clauses are satisfied with this solution.
	int	cSize; //Size of the clauses array.
	int	lSize; //Size of the literals array.
} Solution;

Solution *generateSolution(int *clauses, int cSize, int *literals, int lSize);
Solution *generateEmptySolution(int *clauses, int cSize, int lSize);

Solution *copySolution(Solution *solution);

void destroySolution(Solution **solution);

void calculateScore(Solution *solution);

void printSolution(Solution *solution);

void filePrintScore(Solution *solution, FILE *f);
#endif
