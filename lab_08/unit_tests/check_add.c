#include "check_add.h"

START_TEST(rectangular_matrix)
{
    matrix_t matrix;

    matrix.numb_rows = matrix.numb_columns = 2;
    matrix.matrix = allocate_matrix(matrix.numb_rows, matrix.numb_columns);
    if (matrix.matrix == NULL)
        return;
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;
    matrix.matrix[1][0] = 3;
    matrix.matrix[1][1] = 4;

    matrix_t matrix_res;

    matrix_res.numb_rows = matrix_res.numb_columns = 3;

    matrix_res.matrix = allocate_matrix(matrix_res.numb_rows, matrix_res.numb_columns);
    if (matrix_res.matrix == NULL)
    {
        delete(matrix.matrix, matrix.numb_rows);
        return;
    }
    matrix_res.matrix[0][0] = 1;
    matrix_res.matrix[0][1] = 2;
    matrix_res.matrix[0][2] = 1;
    matrix_res.matrix[1][0] = 3;
    matrix_res.matrix[1][1] = 4;
    matrix_res.matrix[1][2] = 3;
    matrix_res.matrix[2][0] = 1;
    matrix_res.matrix[2][1] = 2;
    matrix_res.matrix[2][2] = 1;
    
    int r = change_matrix(&matrix, matrix_res.numb_rows);  

    r += (matrix.numb_rows != matrix_res.numb_rows);
    r += (matrix.numb_columns != matrix_res.numb_columns);

    if (r)
        ck_assert_int_eq(r, OK);
    else
    {
        for (int i = 0; i < matrix_res.numb_rows; i++)
            for (int j = 0; j < matrix_res.numb_columns; j++)
                r += (matrix.matrix[i][j] != matrix_res.matrix[i][j]);
        ck_assert_int_eq(r, OK);
    }

    delete(matrix.matrix, matrix.numb_rows);
    delete(matrix_res.matrix, matrix_res.numb_rows);
}
END_TEST

START_TEST(square_matrix)
{
    matrix_t matrix;

    matrix.numb_columns = matrix.numb_rows = 2;

    matrix.matrix = allocate_matrix(matrix.numb_rows, matrix.numb_columns);
    if (matrix.matrix == NULL)
        return;
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 1;
    matrix.matrix[1][0] = 1;
    matrix.matrix[1][1] = 1;

    matrix_t matrix_res;
    
    matrix_res.numb_columns = matrix_res.numb_rows = 2;

    matrix_res.matrix = allocate_matrix(matrix_res.numb_rows, matrix_res.numb_columns);
    if (matrix_res.matrix == NULL)
    {
        delete(matrix.matrix, matrix.numb_rows);
        return;
    }
    matrix_res.matrix[0][0] = 1;
    matrix_res.matrix[0][1] = 1;
    matrix_res.matrix[1][0] = 1;
    matrix_res.matrix[1][1] = 1;

    int r = change_matrix(&matrix, matrix_res.numb_rows);  
    r += (matrix.numb_rows != matrix_res.numb_rows);
    r += (matrix.numb_columns != matrix_res.numb_columns);

    if (r)
    {
        ck_assert_int_eq(r, OK);
        delete(matrix.matrix, matrix.numb_rows);
        delete(matrix_res.matrix, matrix_res.numb_rows);
    }
    else
    {
        for (int i = 0; i < matrix_res.numb_rows; i++)
            for (int j = 0; j < matrix_res.numb_columns; j++)
                r += (matrix.matrix[i][j] != matrix_res.matrix[i][j]);
        ck_assert_int_eq(r, OK);
        delete(matrix.matrix, matrix.numb_rows);
        delete(matrix_res.matrix, matrix_res.numb_rows);
    } 
}
END_TEST

Suite *add_suite(Suite *s)
{
    TCase *tcase_pos;

    tcase_pos = tcase_create("positive");

    tcase_add_test(tcase_pos, square_matrix);
    tcase_add_test(tcase_pos, rectangular_matrix);

    suite_add_tcase(s, tcase_pos);

    return s;
}
