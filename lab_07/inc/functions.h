#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN_ARGC 3
#define MAX_ARGC 4
#define SUCCESS 0
#define ARG_ERR -1
#define READ_FILE_ERR -2
#define EMPTY_FILE -3
#define ALLOCATION_ERR -4
#define POINTER_ERR -5
#define FILTER_ERR -6
#define OPEN_FILE_ERR -7
#define ARR_ERR -8

int read_int_from_file(FILE *f, int **bg, int **en);
void print_arr(FILE *f, int *arr, int n);

#endif