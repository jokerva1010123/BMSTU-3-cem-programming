#include "../inc/functions.h"
#include "../inc/inout.h"
#include "../inc/polynom.h"

int process()
{
    char function[MAX_LEN];
    scanf("%s", function);

    if (strlen(function) >= MAX_LEN)
        return ERROR_INPUT;

    if (strcmp(function, "val") == 0)
        return get_value();
    if (strcmp(function, "ddx") == 0)
        return get_derivative();
    if (strcmp(function, "sum") == 0)
        return get_sum();
    if (strcmp(function, "dvd") == 0)
        return divide_polynom();
    return ERROR_INPUT;
}

int get_value(void)
{
    polynom_t polynom;
    init_polynom(&polynom);
    int rc = input_polynom(&polynom);
    if (rc)
        return rc;
    int value;
    rc = scanf("%d", &value);
    if (rc != 1)
    {
        delete(polynom.head);
        return ERROR_INPUT;
    }
    printf("%d\n", calc_value(polynom.head, value));
    delete(polynom.head);
    return OK;
}

int get_derivative(void)
{
    polynom_t polynom;
    init_polynom(&polynom);
    int rc = input_polynom(&polynom);
    if (rc)
        return rc;
    find_new_factor(polynom.head, polynom.power);
    pop_end(&polynom);
    print_polynom(polynom.head);
    delete(polynom.head);
    return OK;
}

int get_sum(void)
{
    polynom_t first, second;
    init_polynom(&first);
    int rc = input_polynom(&first);
    if (rc)
        return rc;
    init_polynom(&second);
    rc = input_polynom(&second);
    if (rc)
    {
        delete(first.head);
        return rc;
    }
    
    if (first.power > second.power)
    {
        factor_t *node = first.head;
        for (int i = 0; i < first.power - second.power; i++)
            node = node->next;
        plus(node, second.head);
        print_polynom(first.head);
    }
    else
    {
        factor_t *node = second.head;
        for (int i = 0; i < second.power - first.power; i++)
            node = node->next;
        plus(node, first.head);
        print_polynom(second.head);
    }
    delete(first.head);
    delete(second.head);
    return OK;
}

int divide_polynom(void)
{
    polynom_t polynom;
    init_polynom(&polynom);
    int rc = input_polynom(&polynom);
    if (rc)
        return rc;
    if (polynom.power % 2)
    {
        print_devide_polynom(polynom.head);
        print_devide_polynom(polynom.head->next);
    }
    else
    {
        print_devide_polynom(polynom.head->next);
        print_devide_polynom(polynom.head);
    }
    delete(polynom.head);
    return OK;
}   