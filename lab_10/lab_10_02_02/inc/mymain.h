#ifndef _MYMAIN_H_
#define _MYMAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0;
#define ERROR_INPUT 1
#define INVALID_INPUT 2
#define ERROR_MEMORY 3
#define MAX_LEN 6

typedef struct factor
{
    int value;
    struct factor *next;    
} factor_t;

typedef struct polynom
{
    int power;
    factor_t *head;
} polynom_t;

#endif