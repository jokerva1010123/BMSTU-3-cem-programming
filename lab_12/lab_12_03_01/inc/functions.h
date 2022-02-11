#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_int(FILE *f, size_t *size);
int file_to_array(FILE *f, int *pa, int *pb);
void print_arr(FILE *f, int *arr, size_t n);

#endif 