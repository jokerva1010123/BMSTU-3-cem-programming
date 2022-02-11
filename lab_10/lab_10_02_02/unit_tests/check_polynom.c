#include "check_polynom.h"
#include "../inc/polynom.h"
#include "../inc/inout.h"

void fill_polynom(polynom_t *polynom)
{
    polynom->power = 4;
    factor_t *node;

    for (int i = 0; i < polynom->power; i++)
    {
        node = new_factor(polynom->power - i);
        push_end(polynom, node);
    }
}

void fill_derivative(polynom_t *polynom)
{
    polynom->power = 3;
    factor_t *node;

    node = new_factor(12);
    push_end(polynom, node);

    node = new_factor(6);
    push_end(polynom, node);

    node = new_factor(2);
    push_end(polynom, node);
}

void fill_add_polynom(polynom_t *polynom)
{
    polynom->power = 4;
    factor_t *node;

    for (int i = 0; i < polynom->power; i++)
    {
        node = new_factor((polynom->power - i) * 2);
        push_end(polynom, node);
    }
}

int compare_polynoms(factor_t *first, factor_t *second)
{
    for ( ; first; first = first->next)
    {
        if (first->value != second->value)
            return 1;
        second = second->next;
    }
    return 0;
}

START_TEST(test_get_value)
{
    polynom_t polynom;
    init_polynom(&polynom);
    fill_polynom(&polynom);

    int data = 7, true_result = 1534;
    int result = calc_value(polynom.head, data);

    delete(polynom.head);

    ck_assert_int_eq(true_result, result);
}
END_TEST

START_TEST(test_differentiate)
{
    polynom_t polynom;
    init_polynom(&polynom);
    fill_polynom(&polynom);

    polynom_t result;
    init_polynom(&result);
    fill_derivative(&result);

    find_new_factor(polynom.head, polynom.power);
    pop_end(&polynom);
    int rc = compare_polynoms(polynom.head, result.head);

    delete(polynom.head);
    delete(result.head);

    ck_assert_int_eq(rc, 0);
}
END_TEST


START_TEST(test_add_polynoms)
{
    polynom_t first;
    init_polynom(&first);
    fill_polynom(&first);

    polynom_t second;
    init_polynom(&second);
    fill_polynom(&second);

    polynom_t result;
    init_polynom(&result);
    fill_add_polynom(&result);

    plus(first.head, second.head);
    int rc = compare_polynoms(first.head, result.head);

    delete(first.head);
    delete(second.head);
    delete(result.head);

    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite *get_suite(Suite *s)
{
    TCase *tc_pos;

    tc_pos = tcase_create("positives");
    tcase_add_test(tc_pos, test_get_value);
    tcase_add_test(tc_pos, test_differentiate);
    tcase_add_test(tc_pos, test_add_polynoms);
    suite_add_tcase(s, tc_pos);

    return s;
}