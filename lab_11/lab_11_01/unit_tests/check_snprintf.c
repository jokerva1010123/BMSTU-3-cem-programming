#include "check_snprintf.h"

START_TEST(test_d)
{
    char test_my_snprintf[BUF_LEN];
    char test_snprintf[BUF_LEN];

    short int data = 12;

    int len_my_snprintf = my_snprintf(test_my_snprintf, BUF_LEN, "%hd", data);
    int len_snprintf = snprintf(test_snprintf, BUF_LEN, "%hd", data);

    ck_assert_int_eq(len_my_snprintf, len_snprintf);
    ck_assert_str_eq(test_my_snprintf, test_snprintf);
}
END_TEST

START_TEST(test_c)
{
    char test_my_snprintf[BUF_LEN];
    char test_snprintf[BUF_LEN];

    char data = 'a';

    int len_my_snprintf = my_snprintf(test_my_snprintf, BUF_LEN, "%c", data);
    int len_snprintf = snprintf(test_snprintf, BUF_LEN, "%c", data);

    ck_assert_int_eq(len_my_snprintf, len_snprintf);
    ck_assert_str_eq(test_my_snprintf, test_snprintf);
}
END_TEST


START_TEST(test_s)
{
    char test_my_snprintf[BUF_LEN];
    char test_snprintf[BUF_LEN];

    char *data = "dinh viet anh";

    int len_my_snprintf = my_snprintf(test_my_snprintf, BUF_LEN, "%s", data);
    int len_snprintf = snprintf(test_snprintf, BUF_LEN, "%s", data);
    ck_assert_int_eq(len_my_snprintf, len_snprintf);
    ck_assert_str_eq(test_my_snprintf, test_snprintf);
}
END_TEST


START_TEST(test_x)
{
    char test_my_snprintf[BUF_LEN];
    char test_snprintf[BUF_LEN];

    int data = 12345;

    int len_my_snprintf = my_snprintf(test_my_snprintf, BUF_LEN, "%x", data);
    int len_snprintf = snprintf(test_snprintf, BUF_LEN, "%x", data);

    ck_assert_int_eq(len_my_snprintf, len_snprintf);
    ck_assert_str_eq(test_my_snprintf, test_snprintf);
}
END_TEST

Suite *my_snprintf_suite(Suite *s)
{
    TCase *tcase_pos = tcase_create("positives");
    tcase_add_test(tcase_pos, test_d);
    tcase_add_test(tcase_pos, test_c);
    tcase_add_test(tcase_pos, test_s);
    tcase_add_test(tcase_pos, test_x);

    suite_add_tcase(s, tcase_pos);

    return s;
}
