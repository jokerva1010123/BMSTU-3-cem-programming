#include "../inc/polynom.h"

int calc_value(factor_t *head, const int value)
{
    int result = head->value;
    head = head->next;
    for (; head; head = head->next)
        result = result * value + head->value;
    return result;
}

void find_new_factor(factor_t *head, const int power)
{
    int i = 0;
    for (; head; head = head->next, i++)
        head->value = head->value * (power - i - 1);
}

void pop_end(polynom_t *polynom)
{
    if (polynom->head == NULL)
        return;
    factor_t *tmp = polynom->head;
    if (tmp->next)
    {
        for (; tmp->next->next; tmp = tmp->next);
        free(tmp->next);
        tmp->next = NULL;
    }
    else
    {
        free(tmp);
        polynom->head = NULL;
    }
    polynom->power--;
}   

void plus(factor_t *first, factor_t *second)
{
    while (first)
    {
        first->value += second->value;
        first = first->next;
        second = second->next;
    }
}

void print_devide_polynom(factor_t *head)
{
    while (head)
    {
        printf("%d ", head->value);
        if (head->next == NULL)
            break;
        head = head->next->next;
    }
    printf("L\n");
}