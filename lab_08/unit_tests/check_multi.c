#include "check_multi.h" 

START_TEST(norm_matrix_multipl)
{
    matrix_t matrix_a;

    matrix_a.numb_columns = matrix_a.numb_rows = 2;

    matrix_a.matrix = allocate_matrix(matrix_a.numb_rows, matrix_a.numb_columns);

    matrix_a.matrix[0][0] = 1;
    matrix_a.matrix[0][1] = 2;
    matrix_a.matrix[1][0] = 4;
    matrix_a.matrix[1][1] = 5;

    matrix_t matrix_b;

    matrix_b.numb_columns = matrix_b.numb_rows = 2;

    matrix_b.matrix = allocate_matrix(matrix_b.numb_rows, matrix_b.numb_columns);

    matrix_b.matrix[0][0] = 0;
    matrix_b.matrix[0][1] = 1;
    matrix_b.matrix[1][0] = 2;
    matrix_b.matrix[1][1] = 0;

    matrix_t matrix_res;

    matrix_res.numb_columns = matrix_res.numb_rows = 2;

    matrix_res.matrix = allocate_matrix(matrix_res.numb_rows, matrix_res.numb_columns);

    matrix_res.matrix[0][0] = 4;
    matrix_res.matrix[0][1] = 1;
    matrix_res.matrix[1][0] = 10;
    matrix_res.matrix[1][1] = 4;

    matrix_t matrix_c;

    matrix_c.numb_rows = 3;
    matrix_c.numb_columns = matrix_c.numb_rows;

    matrix_c.matrix = allocate_matrix(matrix_c.numb_rows, matrix_c.numb_columns);

    matrix_multiplication(&matrix_c, &matrix_a, &matrix_b);
    int r = 0;
    r += (matrix_c.numb_rows != matrix_res.numb_rows);
    r += (matrix_c.numb_columns != matrix_res.numb_columns);

    if (r)
        ck_assert_int_eq(r, OK);
    else
    {
        for (int i = 0; i < matrix_res.numb_rows; i++)
            for (int j = 0; j < matrix_res.numb_columns; j++)
                r += (matrix_c.matrix[i][j] != matrix_res.matrix[i][j]);
        ck_assert_int_eq(r, OK);
    }

    delete(matrix_a.matrix, matrix_a.numb_rows);
    delete(matrix_b.matrix, matrix_b.numb_rows);
    delete(matrix_res.matrix, matrix_res.numb_rows);
    delete(matrix_c.matrix, matrix_c.numb_rows);
}
END_TEST

Suite *multi_suite(Suite *s)
{
    TCase *tcase_pos;

    tcase_pos = tcase_create("positives");

    tcase_add_test(tcase_pos, norm_matrix_multipl);

    suite_add_tcase(s, tcase_pos);
    
    return s;
}
