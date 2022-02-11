#ifndef _POLYNOM_H_
#define _POLYNOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mymain.h"
#include "inout.h"

int calc_value(factor_t *head, const int value);
void find_new_factor(factor_t *head, const int power);
void pop_end(polynom_t *polynom);
void plus(factor_t *first, factor_t *second);
void print_devide_polynom(factor_t *head);

#endif