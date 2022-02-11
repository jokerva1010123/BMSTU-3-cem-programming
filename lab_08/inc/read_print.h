#ifndef _READ_PRINT_H_
#define _READ_PRINT_H_

#include <stdio.h>
#include <stdlib.h>

#include "main.h"

int input_size_matrix(int *numb_rows, int *numb_columns);

int input_matrix(matrix_t *matrix);

int read_matrices(matrix_t *matrix_a, matrix_t *matrix_b);

void print_matrix(matrix_t *matrix);

int input_power(int *power_mat_a, int *power_mat_b);

void delete(int **data, int n);

int **allocate_matrix(int n, int m);

#endif
