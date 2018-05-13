#include "solution.h"

Solution *generateSolution(char *clauses, int cSize, char *literals, int lSize) {
	Solution *solution = (Solution *) malloc(sizeof(Solution));

	solution->clauses = (char *) malloc(sizeof(char) * cSize);
	memcpy(solution->clauses, clauses, cSize);

	solution->size = cSize;

	solution->literals = (char *) malloc(sizeof(char) * lSize);
	memcpy(solution->literals, literals, lSize);

	solution->score = -1;

	return solution;
}

void destroySolution(Solution **solution) {
	if (!*solution) return;
	free((*solution)->clauses);
	free((*solution)->literals);
	free(*solution);
	*solution = 0;
}

void calculateScore(Solution *solution) {
	solution->score = 0;
	int i;

	for (i = 0; i < solution->size; i += 2)
		if ((solution->literals[abs(solution->clauses[i]) - 1] ^ (solution->clauses[i] < 0)) ||
			(solution->clauses[i + 1] &&
				(solution->literals[abs(solution->clauses[i + 1]) - 1] ^ (solution->clauses[i + 1] < 0))))
			solution->score++;
}

void printSolution(Solution *solution) {
	int i;
	if (solution->score == -1)
		calculateScore(solution);
	printf("Score:\t%d\n", solution->score);

	printf("Solution:\t");

	for (i = 0; i < solution->size; i += 2)
		if (solution->clauses[i + 1])
			printf("(%d V %d)%s", solution->literals[abs(solution->clauses[i]) - 1] ^ (solution->clauses[i] < 0) ,
						solution->literals[abs(solution->clauses[i + 1]) - 1] ^ (solution->clauses[i + 1] < 0),
							i == solution->size - 2 ? "\n" : " ^ ");
		else
			printf("%d%s", solution->literals[abs(solution->clauses[i]) - 1] ^ (solution->clauses[i] < 0),
						i == solution->size - 2 ? "\n" : " ^ ");
}
