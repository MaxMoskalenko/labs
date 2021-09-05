#include <stdlib.h>
#include <stdio.h>

int** del(int **m, int size, int di, int dj) {
	if (di < 0 || dj < 0) {
		return NULL;
	}

	int **new_m = malloc((size - 1) * sizeof(int*));

	int ik = 0;
	for (int i = 0; i < size; ++i) {
		if (i == di) {
			continue;
		}

		*(new_m + ik) = malloc((size - 1) * sizeof(int));

		int jk = 0;
		for (int j = 0; j < size; ++j) {
			if (j == dj) {
				continue;
			}

			*(*(new_m + ik) + jk) = *(*(m + i) + j);

			jk++;
		}

		ik++;
	}

	return new_m;
}

void write_matrix(int **m, int size) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			printf("%d ", *(*(m + i) + j));
		}
		printf("\n");
	}
}

int main() {
	int size = 3;

	int matrix[][3] = {
		{1, 2, 3},
		{2, 3, 4},
		{3, 4, 5}
	};

	int **m = malloc(size * sizeof(int*));
	for (int i = 0; i < size; ++i) {
		*(m + i) = malloc(size * sizeof(int));

		for (int j = 0; j < size; ++j) {
			*(*(m + i) + j) = matrix[i][j];
		}
	}

	int di = 1;
	int dj = 1;

	int **new_m = del(m, size, di, dj);

	write_matrix(new_m, size - 1);

	return 0;
}
