#ifndef _INOUT_H_
#define _INOUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymain.h"

void init_polynom(polynom_t *polynom);
int input_polynom(polynom_t *polynom);
void print_polynom(factor_t *head);
void delete(factor_t *head);
factor_t *new_factor(const int value);
void push_end(polynom_t *polynom, factor_t *factor);

#endif