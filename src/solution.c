#include "solution.h"

Solution *generateSolution(int *clauses, int cSize, char *literals, int lSize) {
	Solution *solution = (Solution *) malloc(sizeof(Solution));

	solution->clauses = (int *) malloc(sizeof(int) * cSize);
	memcpy(solution->clauses, clauses, sizeof(int) * cSize);

	solution->cSize = cSize;

	solution->literals = (char *) malloc(sizeof(char) * lSize);
	memcpy(solution->literals, literals, sizeof(char) * lSize);

	solution->lSize = lSize;
	solution->score = -1;

	return solution;
}

Solution *generateEmptySolution(int *clauses, int cSize, int lSize) {
	Solution *solution = (Solution *) malloc(sizeof(Solution));

	solution->clauses = (int *) malloc(sizeof(int) * cSize);
	memcpy(solution->clauses, clauses, sizeof(int) * cSize);

	solution->cSize = cSize;

	solution->literals = (char *) malloc(sizeof(char) * lSize);
	memset(solution->literals, 0, sizeof(char) * lSize);

	solution->lSize = lSize;
	solution->score = -1;

	return solution;
}

Solution *copySolution(Solution *solution) {
	return generateSolution(solution->clauses, solution->cSize, solution->literals, solution->lSize);
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

	for (i = 0; i < solution->cSize - 1; i += 2)
		if ((solution->literals[abs(solution->clauses[i]) - 1] ^ (solution->clauses[i] < 0)) ||
			(solution->clauses[i + 1] &&
				(solution->literals[abs(solution->clauses[i + 1]) - 1] ^ (solution->clauses[i + 1] < 0))))
			solution->score++;
}

void printSolution(Solution *solution) {
	int i;
	if (solution->score == -1)
		calculateScore(solution);
	printf("Score is %d\n", solution->score);

	printf("Formula:\t");

	for (i = 0; i < solution->cSize - 1; i += 2)
		if (solution->clauses[i + 1])
			printf("(%d V %d)%s", solution->clauses[i], solution->clauses[i + 1],
							i == solution->cSize - 2 ? "\n" : " ^ ");
		else
			printf("%d%s", solution->clauses[i],
						i == solution->cSize - 2 ? "\n" : " ^ ");

	printf("Literals:\t");

	for (i = 0; i < solution->lSize; i++)
		printf("%d(%d)%s", i + 1, solution->literals[i], i == solution->lSize - 1 ? "\n" : " ");

	printf("Solution:\t");

	for (i = 0; i < solution->cSize - 1; i += 2)
		printf("%d%s", (solution->literals[abs(solution->clauses[i]) - 1] ^ (solution->clauses[i] < 0)) ||
                        		(solution->clauses[i + 1] &&
                                		(solution->literals[abs(solution->clauses[i + 1]) - 1] ^ (solution->clauses[i + 1] < 0))),
							i == solution->cSize - 2 ? "\n" : " ^ ");

	//destroySolution(&solution); //?
}

void filePrintScore(Solution *solution, FILE *f) {
	if (solution->score == -1)
		calculateScore(solution);
	fprintf(f, "%d,", solution->score);
	//destroySolution(&solution); //?
}
