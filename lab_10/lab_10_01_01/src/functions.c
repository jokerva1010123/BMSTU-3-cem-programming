#include "../inc/functions.h"

void *pop_front(node_t **head)
{
    if (!head || !(*head))
        return NULL;

    node_t *buf = *head;
    void *data = buf->data;
    *head = buf->next;
    free(buf);
    
    return data;
}

void *pop_back(node_t **head)
{
    if (!head || !(*head))
        return NULL;
    
    void *data = NULL;

    node_t *tmp = *head;
    if (tmp)
    {
        if (tmp->next)
        {
            for (; tmp->next->next; tmp = tmp->next);
            data = tmp->next->data;
            free(tmp->next);
            tmp->next = NULL;
        }
        else
        {
            data = tmp->data;
            free(tmp);
            *head = NULL;
        }
    }

    return data;
}

node_t *reverse(node_t *head)
{
    node_t *new_head = NULL;
    node_t *next = NULL;

    while (head)
    {
        next = head->next;
        head->next = new_head;
        new_head = head;
        head = next;
    }

    return new_head;
}

void front_back_split(node_t *head, node_t **back)
{
    if (!head || !back)
        return;

    node_t *b = head;

    while (head->next && head->next->next)
    {
        b = b->next;
        head = head->next->next;
    }

    *back = b->next;
    b->next = NULL;
}

node_t *sort(node_t *head, int (*my_cmp)(const void *, const void *))
{
    if (!head || !head->next)
        return head;

    if (!my_cmp)
        return NULL;

    node_t *a = NULL;
    node_t *b = NULL;
    node_t *back = NULL;
    node_t *new_head = NULL;

    front_back_split(head, &back);
    a = sort(head, my_cmp);
    b = sort(back, my_cmp);

    new_head = sorted_merge(&a, &b, my_cmp);

    return new_head;
}

node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*my_cmp)(const void *, const void *))
{
    if (!head_a || !head_b)
        return NULL;
	
    if (my_cmp == NULL)
        return NULL;

    node_t *a = *head_a;
    node_t *b = *head_b;
    node_t *head = NULL;
    node_t *c = NULL;

    if (a || b)
    {
        if (!b || (a && my_cmp(a->data, b->data) < 0))
        {
            head = a;
            a = a->next;
        }
        else if (b)
        {
            head = b;
            b = b->next;
        }
    }
    c = head;
    while (a && b)
    {
        if (my_cmp(a->data, b->data) < 0)
        {
            c->next = a;
            c = c->next;
            a = a->next;
        }
        else
        {
            c->next = b;
            c = c->next;
            b = b->next;
        }
    }

    while (a)
    {
        c->next = a;
        c = c->next;
        a = a->next;
    }

    while (b)
    {
        c->next = b;
        c = c->next;
        b = b->next;
    }

    a = NULL;
    b = NULL;
    c = NULL;
    *head_a = NULL;
    *head_b = NULL;

    return head;
}

int my_cmp_int(const void *p, const void *q)
{
    const int *a = p;
    const int *b = q;
    return *a - *b;
}

int my_cmp_char(const void *p, const void *q)
{
    const char *a = p;
    const char *b = q;
    return *a - *b;
}

int my_cmp_double(const void *p, const void *q)
{
    const double *a = p;
    const double *b = q;
    if (fabs(*a - *b) < EPS)
        return 0;
    else if (*a - *b > EPS)
        return 1;
    else 
        return -1;
}

void delete(node_t *head)
{
    node_t *cur;
    while (head != NULL)
    {
        cur = head;
        head = head->next;
        free(cur);
    }
}