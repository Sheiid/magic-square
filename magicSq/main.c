/*
 * main.c
 *
 *  Created on: Nov 24, 2017
 *      Author: sheida
 */
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#define dim 3

int magic(int **, int[dim], int);
int checkmagic(int **);
int main() {

	FILE *fp;
	int **mat, used[dim], level, res;
	//int matrix[dim][dim]={{2,7,6},{9,5,1},{4,3,8}};
	int i, j;
//	if(checkmagic(matrix)){
//		printf("yes!");
//	}

	mat = (int**) malloc(dim * sizeof(int *));
	if (mat == NULL) {
		printf("Allocation Error \n");
		return 0;
	}
	for (i = 0; i < dim; i++) {
		mat[i] = (int *) calloc(dim,sizeof(int));
		if (mat[i] == NULL) {
			printf("Error\n");
			return 0;
		}
	}
	for (i = 0; i < dim; i++) {
		used[i] = 0;

	}
	res = magic(mat, used, 0);

	fp = fopen("output.txt", "w");
	if (fp == NULL) {
		printf("ERROR file is not open correctly!\n");
		return 0;
	}

	if (res) {

		printf("solution is found !\n");
		for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) {
				fprintf(fp, "%d ", mat[i][j]);
			}
			fprintf(fp,"\n");
		}
	}else
		printf("magic square not Found !\n");
	for (i = 0; i < dim; i++) {
		free(mat[i]);
	}
	free(mat);
	fclose(fp);
	return 0;
}
int magic(int **mat, int used[], int level) {
	int i, j, k;

	//termination case
	if (level == 9) {
		return (checkmagic(mat));

	} else {
		i = level / dim;
		j = level % dim;

		//for checking used we need for loop


		for (k = 1; k <= dim * dim; k++) {
			//printf("%d matrix\n", mat[i][j]);
			if (used[k] == 0) {
				mat[i][j] = k;
				used[k] = 1;
				printf("%d matrix\n", mat[i][j]);
				if (magic(mat, used, level+1))
					return 1;
			}
			used[k] = 0;

		}

	}
	return 0;

}
int checkmagic(int **mat) {
	int sumfinal = 0, rowsum, sumcol, sumdim, sumdimr;
	int i, j;
	//printf("%d\n", rowsum);
//	for (i = 0; i < dim; i++) {

		//sumfinal += mat[0][i];
		sumfinal=15;
	//}
	for (i = 0; i < dim; i++) {
		rowsum = 0;
		for (j = 0; j < dim; j++) {
			rowsum += mat[i][j];
		}
		if (rowsum != sumfinal) {
			return 0;
		}

	}

	for (j = 0; j < dim; j++) {
		sumcol = 0;

		for (i = 0; i < dim; i++) {
			sumcol += mat[i][j];
		}
		if (sumfinal != sumcol) {
			return 0;
		}
	}

	sumdim = 0;
	for (i = 0; i < dim; i++) {
		sumdim += mat[i][i];
	}
	if (sumfinal != sumdim) {
		return 0;
	}

	sumdimr = 0;
	for (i = 0; i < dim; i++) {
		sumdimr += mat[i][(dim - 1) - i];
	}

	if (sumfinal != sumdimr) {
		return 0;
	}

	return 1;
}

