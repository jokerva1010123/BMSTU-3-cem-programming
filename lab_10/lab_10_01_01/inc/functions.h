#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "main.h"

void *pop_front(node_t **head);
void *pop_back(node_t **head);
node_t *reverse(node_t *head);
void front_back_split(node_t *head, node_t **back);
node_t *sort(node_t *head, int (*my_cmp)(const void *, const void *));
node_t *sorted_merge(node_t **head_a, node_t **head_b, int (*my_cmp)(const void *, const void *));
int my_cmp_int(const void *p, const void *q);
int my_cmp_char(const void *p, const void *q);
int my_cmp_double(const void *p, const void *q);
void delete(node_t *head);

#endif 