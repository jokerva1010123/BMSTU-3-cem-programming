#include "../inc/filter.h"
#include "../inc/functions.h"
#include "check_key.h"

START_TEST(test_key_nullptr)
{
    int arr[] = {1, 2, 3, 4};
    int rc = 0;

    int *dst_a = NULL;
    int *dst_b = NULL;

    rc = key(NULL, NULL, &dst_a, &dst_b);
    ck_assert_int_eq(rc, POINTER_ERR);

    rc = key(arr, NULL, &dst_a, &dst_b);
    ck_assert_int_eq(rc, POINTER_ERR);

    rc = key(NULL, arr, &dst_a, &dst_b);
    ck_assert_int_eq(rc, POINTER_ERR);
}
END_TEST

START_TEST(test_key_all_pos)
{
    int arr[] = {1, 2, 3, 4};
    int res[] = {1, 2, 3, 4};

    size_t res_len = 4;
    int rc = 0;

    int *dst_a = NULL;
    int *dst_b = NULL;

    rc = key(arr, arr + res_len, &dst_a, &dst_b);
    ck_assert_int_eq(rc, 0);
    free(dst_a);

    ck_assert_mem_eq(arr, res, sizeof(int) * res_len);
}
END_TEST

START_TEST(test_key_with_neg)
{
    int arr[] = {1, -2, 3, 4};
    int res[] = {1};

    size_t arr_len = 4;
    size_t res_len = 1;
    int rc = 0;

    int *dst_a = NULL;
    int *dst_b = NULL;

    rc = key(arr, arr + arr_len, &dst_a, &dst_b);
    ck_assert_int_eq(rc, 0);

    ck_assert_mem_eq(arr, res, sizeof(int) * res_len);
    free(dst_a);
}
END_TEST

START_TEST(test_key_with_neg_on_last_pos)
{
    int arr[] = {1, 2, 3, -4};
    int res[] = {1, 2, 3};

    size_t arr_len = 4;
    size_t res_len = 3;
    int rc = 0;

    int *dst_a = NULL;
    int *dst_b = NULL;

    rc = key(arr, arr + arr_len, &dst_a, &dst_b);
    ck_assert_int_eq(rc, 0);
    free(dst_a);

    ck_assert_mem_eq(arr, res, sizeof(int) * res_len);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_pos;
    TCase *tc_neg;

    s = suite_create("key");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_key_all_pos);
    tcase_add_test(tc_pos, test_key_with_neg);
    tcase_add_test(tc_pos, test_key_with_neg_on_last_pos);

    suite_add_tcase(s, tc_pos);

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_key_nullptr);

    suite_add_tcase(s, tc_neg);
    return s;
}