#ifndef _FUNC_MATRIX_H_
#define _FUNC_MATRIX_H_

#include <math.h>

#include "main.h"
#include "read_print.h"

int search_desired_row(matrix_t matrix);

void delete_row(matrix_t *matrix, int numb_row);

void delete_specific_rows(matrix_t *matrix);

int search_desired_column(matrix_t matrix);

void delete_column(matrix_t *matrix, int numb_column);

void delete_specific_columns(matrix_t *matrix);

void reduce_matrix(matrix_t *matrix);

int geometric_mean(matrix_t *matrix, int j);

int add_row(matrix_t *matrix);

int add_column(matrix_t *matrix);

int change_matrix(matrix_t *matrix, int new_size);

int add_to_matrix(matrix_t *matrix_a, matrix_t *matrix_b);

void copy_matrix(int **source, int **destination, int numb_rows, int numb_columns);

int find_matrix_element(matrix_t *matrix_a, matrix_t *matrix_b, int i, int j);

void matrix_multiplication(matrix_t *res_matrix,
matrix_t *matrix_a, matrix_t *matrix_b);

int prepare_matrix_for_work(matrix_t *matrix, int size);

int raise_matrix_to_power(matrix_t *matrix, int power_mat);

int raise_matrices_to_power(matrix_t *matrix_a, matrix_t *matrix_b);

int calculate_result_matrix(matrix_t *matrix_res, 
matrix_t *matrix_a, matrix_t *matrix_b);

#endif
