#include "../inc/inout.h"

void init_polynom(polynom_t *polynom)
{
    polynom->power = 0;
    polynom->head = NULL;
}

factor_t *new_factor(const int value)
{
    factor_t *factor = malloc(sizeof(factor_t));
    if (!factor) 
        return NULL;
    factor->next = NULL;
    factor->value = value;
    return factor;
}

void push_end(polynom_t *polynom, factor_t *factor)
{
    if (polynom->head == NULL)
        polynom->head = factor;
    else
    {
        factor_t *tmp = polynom->head;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = factor;
    }
}

int input_polynom(polynom_t *polynom)
{
    int rc = scanf("%d", &polynom->power);
    if (rc != 1)
        return ERROR_INPUT;
    if (polynom->power < 0)
        return INVALID_INPUT;

    factor_t *factor;
    int value;
    for (int i = 0; i < polynom->power; i++)
    {
        rc = scanf("%d", &value);
        if (rc != 1)
        {
            delete(polynom->head);
            return ERROR_INPUT;
        }
        factor = new_factor(value);
        if (factor == NULL)
        {
            delete(polynom->head);
            return ERROR_MEMORY;
        }
        push_end(polynom, factor);
    }
    return OK;
}

void print_polynom(factor_t *head)
{
    for (; head; head = head->next)
        printf("%d ", head->value);

    printf("L\n");
}

void delete(factor_t *head)
{
    while (head)
    {
        factor_t *tmp = head;
        head = head->next;
        free(tmp);
    }
}