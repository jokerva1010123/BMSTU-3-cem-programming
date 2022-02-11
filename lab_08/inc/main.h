#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>

#define OK 0
#define INPUT_ERROR 1
#define INVALID_INPUT 2
#define MEMORY_ERROR 3
#define ERROR 4

typedef struct matrix
{
    int **matrix;
    int numb_rows;
    int numb_columns;
} matrix_t;

#endif
