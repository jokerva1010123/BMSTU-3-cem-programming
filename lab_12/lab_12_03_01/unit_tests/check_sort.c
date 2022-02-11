#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../inc/sort.h"

START_TEST(test_mycmp_equal_values)
{
    int a, b;
    int rc = 0;
    a = b = 1;

    rc = mycmp(&a, &b);
    ck_assert_int_eq(rc, 0);
}
END_TEST

START_TEST(test_mycmp_first_bg)
{
    int a, b;
    int rc = 0;
    a = 2;
    b = 1;
    rc = mycmp(&a, &b);
    ck_assert_int_gt(rc, 0);
}
END_TEST

START_TEST(test_mycmp_sec_bg)
{
    int a, b;
    int rc = 0;
    a = 1;
    b = 2;
    rc = mycmp(&a, &b);
    ck_assert_int_lt(rc, 0);
}
END_TEST

START_TEST(test_mysort_eq_nums)
{
    int arr[] = {1, 1, 1, 1, 1};
    size_t len_arr = 5;
    int res[] = {1, 1, 1, 1, 1};

    mysort(arr, len_arr, sizeof(int), mycmp);

    ck_assert_mem_eq(arr, res, sizeof(int) * len_arr);
}
END_TEST

START_TEST(test_mysort_nums_sorted)
{
    int arr[] = {1, 2, 3};
    size_t len_arr = 3;
    int res[] = {1, 2, 3};

    mysort(arr, len_arr, sizeof(int), mycmp);

    ck_assert_mem_eq(arr, res, sizeof(int) * len_arr);
}
END_TEST

START_TEST(test_mysort_nums_req_swap)
{
    int arr[] = {2, 3, 1, 5, 4};
    size_t len_arr = 5;
    int res[] = {1, 2, 3, 4, 5};

    mysort(arr, len_arr, sizeof(int), mycmp);

    ck_assert_mem_eq(arr, res, sizeof(int) * len_arr);
}
END_TEST

START_TEST(test_mysort_nums_sort_not_all)
{
    int arr[] = {1, 2, 3, 5, 4};
    size_t len_arr = 5;
    int res[] = {1, 2, 3, 4, 5};

    mysort(arr, len_arr, sizeof(int), mycmp);

    ck_assert_mem_eq(arr, res, sizeof(int) * len_arr);
}
END_TEST

START_TEST(test_mysort_one_el)
{
    int arr[] = {1};
    size_t len_arr = 1;
    int res[] = {1};
    mysort(arr, len_arr, sizeof(int), mycmp);
    ck_assert_mem_eq(arr, res, sizeof(int) * len_arr);
}
END_TEST

Suite *mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("my_sort");

    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_mysort_eq_nums);
    tcase_add_test(tc_pos, test_mysort_nums_sorted);
    tcase_add_test(tc_pos, test_mysort_nums_req_swap);
    tcase_add_test(tc_pos, test_mysort_nums_sort_not_all);
    tcase_add_test(tc_pos, test_mysort_one_el);

    suite_add_tcase(s, tc_pos);

    return s;
}

Suite *mycmp_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("mycmp");
    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_mycmp_equal_values);
    tcase_add_test(tc_pos, test_mycmp_first_bg);
    tcase_add_test(tc_pos, test_mycmp_sec_bg);
    suite_add_tcase(s, tc_pos);
    return s;
}