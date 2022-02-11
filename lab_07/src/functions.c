#include "../inc/functions.h"

int read_int_from_file(FILE *f, int **bg, int **en)
{
    int rc, number, count = 0;

    while ((rc = fscanf(f, "%d", &number)) == 1)
        count++;

    if (count == 0)
        return EMPTY_FILE;

    rewind(f);

    *bg = malloc(count * sizeof(int));
    if (*bg == NULL)
        return ALLOCATION_ERR;
    int *ptemp = *bg;
    while ((rc = fscanf(f, "%d", &number)) == 1)
    {
        *ptemp = number;
        ptemp++;
    }
    *en = ptemp;

    return SUCCESS;
}

void print_arr(FILE *f, int *arr, int n)
{
    for (int *cur = arr; cur < arr + n; cur ++)
        fprintf(f, "%d ", *cur);
}
