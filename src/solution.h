#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "common.h"

typedef struct {
	char	*clauses; //This has pairs of literal indices in it. (1-based indices, eg. [1, -5, 2, -3, 4, 0] ==> (1 V -5) ^ (2 V -3) ^ 4)
	char	*literals; //This has the assigned values of the literals. (0 or 1, eg. [1, 1, 0, 1, 0])
	int	score; //This shows how many clauses are satisfied with this solution.
	int	size; //Size of the clauses array.
} Solution;

Solution *generateSolution(char *clauses, int cSize, char *literals, int lSize);

void destroySolution(Solution **solution);

void calculateScore(Solution *solution);

void printSolution(Solution *solution);
#endif
