#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define EPS 1e-6

typedef struct node node_t;

struct node
{
    void *data;
    node_t *next;
};

#endif