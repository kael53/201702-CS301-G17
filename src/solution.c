#include "solution.h"

Solution *generateSolution(char *clauses, char *literals) {
	Solution *solution = (Solution *) malloc(sizeof(Solution));

	int size = strlen(clauses) + 1;
	solution->clauses = (char *) malloc(sizeof(char) * size);
	memcpy(solution->clauses, clauses, size);

	solution->size = size - 1;

	size = strlen(literals) + 1;
	solution->literals = (char *) malloc(sizeof(char) * size);
	memcpy(solution->literals, literals, size);

	solution->score = -1;

	return solution;
}

void destroySolution(Solution *solution) {
	free(solution->clauses);
	free(solution->literals);
	free(solution);
	solution = 0;
}

void calculateScore(Solution *solution) {
	solution->score = 0;
	int i;

	for (i = 0; i < solution->size; i += 2)
		if ((solution->literals[abs(solution->clauses[i]) - 1] ^ (solution->clauses[i] < 0)) &&
			((solution->clauses[i + 1] == 0) ||
				(solution->literals[abs(solution->clauses[i + 1]) - 1] ^ (solution->clauses[i + 1] < 0))))
			solution->score++;
}

void printSolution(Solution *solution) {
	int i;
	if (solution->score == -1)
		calculateScore(solution);
	printf("Score:\t%d\n", solution->score);
	printf("Solution:\n");

	for (i = 0; i < solution->size; i += 2)
		printf("(%d ^ %d)%s", solution->literals[abs(solution->clauses[i]) - 1],
					solution->literals[abs(solution->clauses[i + 1]) - 1],
						i == solution->size - 1 ? "\n" : " V ");
}
