#include "check_delete.h"

START_TEST(delete_rows)
{
    matrix_t matrix;

    matrix.numb_rows = 2;
    matrix.numb_columns = 1;

    matrix.matrix = allocate_matrix(matrix.numb_rows, matrix.numb_columns);
    matrix.matrix[0][0] = 2;
    matrix.matrix[1][0] = 1;

    matrix_t matrix_res;

    matrix_res.numb_columns = matrix_res.numb_rows = 1;

    matrix_res.matrix = allocate_matrix(matrix_res.numb_rows, matrix_res.numb_columns);
    matrix_res.matrix[0][0] = 2;
 
    reduce_matrix(&matrix);
    int r = 0;

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

START_TEST(delete_columns)
{
    matrix_t matrix;

    matrix.numb_rows = 1;
    matrix.numb_columns = 2;

    matrix.matrix = allocate_matrix(matrix.numb_rows, matrix.numb_columns);
    matrix.matrix[0][0] = 1;
    matrix.matrix[0][1] = 2;

    matrix_t matrix_res;

    matrix_res.numb_columns = matrix_res.numb_rows = 1;

    matrix_res.matrix = allocate_matrix(matrix_res.numb_rows, matrix_res.numb_columns);
    matrix_res.matrix[0][0] = 2;
 
    reduce_matrix(&matrix);

    int r = 0;
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

Suite *delete_suite(Suite *s)
{
    TCase *tcase_pos;
    tcase_pos = tcase_create("positives");
    tcase_add_test(tcase_pos, delete_rows);
    tcase_add_test(tcase_pos, delete_columns);

    suite_add_tcase(s, tcase_pos);
    
    return s;
}
