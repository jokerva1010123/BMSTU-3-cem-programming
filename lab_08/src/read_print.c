#include "../inc/read_print.h"
#include "../inc/main.h"

int input_size_matrix(int *numb_rows, int *numb_columns)
{
    int r;
    r = scanf("%d", numb_rows);
    if (r != 1)
        return INPUT_ERROR; 

    if (*numb_rows <= 0)
        return INVALID_INPUT; 
    r = scanf("%d", numb_columns); 
    if (r != 1)
        return INPUT_ERROR;
    if (*numb_columns <= 0)
        return INVALID_INPUT;
    return OK;
}

int input_matrix(matrix_t *matrix)
{
    matrix->matrix = allocate_matrix(matrix->numb_rows, matrix->numb_columns);
    if (!(matrix->matrix))
        return MEMORY_ERROR; 
    int r;
    for (int i = 0; i < matrix->numb_rows; i++) 
    {
        for (int j = 0; j < matrix->numb_columns; j++) 
        {
            r = scanf("%d", (matrix->matrix)[i] + j);
            if (r != 1)
            {
                delete(matrix->matrix, matrix->numb_rows);
                return INPUT_ERROR;
            }
        }
    }
    return OK;
}

int read_matrices(matrix_t *matrix_a, matrix_t *matrix_b) 
{
    int r;
    r = input_size_matrix(&(matrix_a->numb_rows), &(matrix_a->numb_columns));
    if (r)
        return r;
    r = input_matrix(matrix_a);
    if (r)
        return r;
    r = input_size_matrix(&(matrix_b->numb_rows), &(matrix_b->numb_columns));

    if (r)
    {
        delete(matrix_a->matrix, matrix_a->numb_rows);
        return r;
    }
    r = input_matrix(matrix_b);
    if (r)
    {
        delete(matrix_a->matrix, matrix_a->numb_rows);
        return r;
    }
    return OK;  
}

void print_matrix(matrix_t *matrix)
{
    printf("\n");
    for (int i = 0; i < matrix->numb_rows; i++) 
    {
        for (int j = 0; j < matrix->numb_columns; j++) 
        {
            printf("%d ", (matrix->matrix)[i][j]);
        }
        printf("\n");
    }
}
int input_power(int *power_mat_a, int *power_mat_b)
{
    int r;
    r = scanf("%d", power_mat_a);
    if (r != 1)
        return INPUT_ERROR; 
    if (*power_mat_a < 0)
        return INVALID_INPUT; 
    r = scanf("%d", power_mat_b); 
    if (r != 1)
        return INPUT_ERROR; 
    if (*power_mat_b < 0)
        return INVALID_INPUT;
    return OK;
}

void delete(int **data, int n)
{
    for (int i = 0; i < n; i++)
        free(data[i]);

    free(data);
}

int **allocate_matrix(int n, int m)
{
    int **data = calloc(n, sizeof(int*));
    if (!data)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(int));
        if (!data[i])
        {
            delete(data, n);
            return NULL;
        }
    }
    return data;
}
