#include "../inc/func_matrix.h"

int search_desired_row(matrix_t matrix)
{
    int i_min = 0, j_min = 0;
    for (int j = 0; j < matrix.numb_columns; j++)
        for (int i = 0; i < matrix.numb_rows; i++)
            if (matrix.matrix[i][j] <= matrix.matrix[i_min][j_min])
            {
                i_min = i;
                j_min = j;
            }
    return i_min;
}

void delete_row(matrix_t *matrix, int numb_row)
{
    free(matrix->matrix[numb_row]);
    for (int i = numb_row; i < matrix->numb_rows - 1; i++)
        matrix->matrix[i] = matrix->matrix[i + 1];
}

void delete_specific_rows(matrix_t *matrix)
{
    int numb_row;
    while (matrix->numb_rows > matrix->numb_columns)
    {
        numb_row = search_desired_row(*matrix);
        delete_row(matrix, numb_row);
        (matrix->numb_rows)--;
    }
}

int search_desired_column(matrix_t matrix)
{
    int i_min = 0, j_min = 0;
    for (int j = 0; j < matrix.numb_columns; j++)
        for (int i = 0; i < matrix.numb_rows; i++)
            if (matrix.matrix[i][j] <= matrix.matrix[i_min][j_min])
            {
                i_min = i;
                j_min = j;
            }
    return j_min;
}

void delete_column(matrix_t *matrix, int numb_column)
{
    for (int i = 0; i < matrix->numb_rows; i++)
        for (int j = numb_column; j < matrix->numb_columns - 1; j++)
            matrix->matrix[i][j] = matrix->matrix[i][j + 1];
}

void delete_specific_columns(matrix_t *matrix)
{
    int numb_column;
    while (matrix->numb_columns > matrix->numb_rows)
    {
        numb_column = search_desired_column(*matrix);
        delete_column(matrix, numb_column);
        (matrix->numb_columns)--;
    }
}

void reduce_matrix(matrix_t *matrix)
{
    if (matrix->numb_rows > matrix->numb_columns)
        delete_specific_rows(matrix);
    else if (matrix->numb_rows < matrix->numb_columns)
    {
        delete_specific_columns(matrix);
    }
}

int geometric_mean(matrix_t *matrix, int j)
{
    int prod_of_numbers = 1;
    double geom_meane;
    for (int i = 0; i < matrix->numb_rows - 1; i++)
        prod_of_numbers *= abs(matrix->matrix[i][j]);
    geom_meane = pow((double) prod_of_numbers, (double) 1 / (matrix->numb_rows - 1)); 
    return (int) geom_meane;
}

int add_row(matrix_t *matrix)
{
    int **p = realloc(matrix->matrix, ++matrix->numb_rows * sizeof(int*));
    if (!p)
    {
        delete(matrix->matrix, --matrix->numb_rows);
        return MEMORY_ERROR; 
    }
    matrix->matrix = p;
    matrix->matrix[matrix->numb_rows - 1] = malloc(matrix->numb_columns * sizeof(int));
    if (!(matrix->matrix[matrix->numb_rows - 1]))
    {
        delete(matrix->matrix, matrix->numb_rows);
        return MEMORY_ERROR; 
    }
    for (int j = 0; j < matrix->numb_columns; j++)
        matrix->matrix[matrix->numb_rows - 1][j] = geometric_mean(matrix, j);
    return OK;
}

int add_column(matrix_t *matrix)
{
    int *p;
    matrix->numb_columns++;
    for (int i = 0; i < matrix->numb_rows; i++)
    {
        p = realloc(matrix->matrix[i], matrix->numb_columns * sizeof(int));
        if (!p)
        {
            delete(matrix->matrix, matrix->numb_rows);
            return MEMORY_ERROR; 
        }
        matrix->matrix[i] = p;
    }
    int min_elem;
    for (int i = 0; i < matrix->numb_rows; i++)
    {
        min_elem = matrix->matrix[i][0];
        for (int j = 1; j < matrix->numb_columns - 1; j++)
            min_elem = (min_elem < matrix->matrix[i][j] ? min_elem : matrix->matrix[i][j]);
        matrix->matrix[i][matrix->numb_columns - 1] = min_elem;
    }
    return OK;
}

int change_matrix(matrix_t *matrix, int new_size)
{
    int r;
    while (matrix->numb_rows < new_size) 
    {
        r = add_row(matrix);
        if (r)
            return r;
    }
    while (matrix->numb_columns < new_size) 
    {
        r = add_column(matrix);
        if (r)
            return r;
    }
    return OK;
}

int add_to_matrix(matrix_t *matrix_a, matrix_t *matrix_b)
{
    int r;

    if (matrix_a->numb_rows < matrix_b->numb_rows)
    {
        r = change_matrix(matrix_a, matrix_b->numb_rows);

        if (r)
        {
            delete(matrix_b->matrix, matrix_b->numb_rows);
            return r;
        }
    }
    else if (matrix_a->numb_rows > matrix_b->numb_rows)
    {
        r = change_matrix(matrix_b, matrix_a->numb_rows);

        if (r)
        {
            delete(matrix_a->matrix, matrix_a->numb_rows);
            return r;
        }
    }
    return OK;
}

void copy_matrix(int **source, int **destination, 
int numb_rows, int numb_columns)
{
    for (int i = 0; i < numb_rows; i++)
        for (int j = 0; j < numb_columns; j++)
            destination[i][j] = source[i][j];
}

int find_matrix_element(matrix_t *matrix_a, matrix_t *matrix_b, int i, int j)
{
    int new_matr_elem = 0;
    for (int u = 0; u < matrix_a->numb_columns; u++)
        new_matr_elem += matrix_a->matrix[i][u] * matrix_b->matrix[u][j];
    return new_matr_elem;
}

void matrix_multiplication(matrix_t *res_matrix,
matrix_t *matrix_a, matrix_t *matrix_b)
{
    for (int i = 0; i < res_matrix->numb_rows; i++)
        for (int j = 0; j < res_matrix->numb_columns; j++)
            res_matrix->matrix[i][j] = find_matrix_element(matrix_a, matrix_b, i, j);
}

int prepare_matrix_for_work(matrix_t *matrix, int size)
{   
    matrix->numb_rows = size;
    matrix->numb_columns = size;
    matrix->matrix = allocate_matrix(matrix->numb_rows, matrix->numb_columns);
    if (!matrix->matrix)
        return MEMORY_ERROR;
    for (int i = 0; i < matrix->numb_rows; i++)
        for (int j = 0; j < matrix->numb_columns; j++)
            matrix->matrix[i][j] = (i == j ? 1 : 0);
    return OK;
}

int raise_matrix_to_power(matrix_t *matrix, int power_mat)
{
    matrix_t res_matrix;
    int r = prepare_matrix_for_work(&res_matrix, matrix->numb_rows);
    if (r)
        return r;
    matrix_t interm_res_matrix;
    r = prepare_matrix_for_work(&interm_res_matrix, matrix->numb_rows);
    if (r)
    {
        delete(res_matrix.matrix, res_matrix.numb_rows);
        return r;
    }
    for (int i = 0; i < power_mat; i++)
    {
        matrix_multiplication(&res_matrix, &interm_res_matrix, matrix);
        copy_matrix(res_matrix.matrix, interm_res_matrix.matrix, res_matrix.numb_rows, 
        res_matrix.numb_columns);
    }
    copy_matrix(res_matrix.matrix, matrix->matrix, res_matrix.numb_rows, 
    res_matrix.numb_columns);
    delete(res_matrix.matrix, res_matrix.numb_rows);
    delete(interm_res_matrix.matrix, interm_res_matrix.numb_rows);
    return OK;
}

int raise_matrices_to_power(matrix_t *matrix_a, matrix_t *matrix_b)
{
    int power_a, power_b;
    int r = input_power(&power_a, &power_b);
    if (r)
    {
        delete(matrix_a->matrix, matrix_a->numb_rows);
        delete(matrix_b->matrix, matrix_b->numb_rows);
        return r;
    }
    r = raise_matrix_to_power(matrix_a, power_a);
    if (r)
    {
        delete(matrix_a->matrix, matrix_a->numb_rows);
        delete(matrix_b->matrix, matrix_b->numb_rows);
        return r;
    }
    r = raise_matrix_to_power(matrix_b, power_b);
    if (r)
    {
        delete(matrix_a->matrix, matrix_a->numb_rows);
        delete(matrix_b->matrix, matrix_b->numb_rows);
        return r;
    }
    return OK;
}

int calculate_result_matrix(matrix_t *matrix_res, 
matrix_t *matrix_a, matrix_t *matrix_b)
{
    matrix_res->numb_rows = matrix_a->numb_rows;
    matrix_res->numb_columns = matrix_b->numb_columns;
    matrix_res->matrix = allocate_matrix(matrix_res->numb_rows, matrix_res->numb_columns);
    if (!matrix_res->matrix)
        return MEMORY_ERROR;
    matrix_multiplication(matrix_res, matrix_a, matrix_b);
    return OK;
}
