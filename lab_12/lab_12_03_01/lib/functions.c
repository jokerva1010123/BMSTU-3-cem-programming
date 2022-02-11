#include "../inc/functions.h"
#include "../inc/mymain.h"

int count_int(FILE *f, size_t *size)
{
    size_t tmp = 0;
    int num;
    while (fscanf(f, "%d ", &num) == 1)
        tmp++;
    if (!tmp)
        return EMPTY_FILE;
    if (!feof(f))
        return READ_ERR;
    *size = tmp;
    return SUCCESS;
}

int file_to_array(FILE *f, int *pa, int *pb)
{
    int *beg = pa;
    while (beg < pb)
        if (fscanf(f, "%d", beg++) != 1)
            return READ_ERR;
    return SUCCESS;
}

void print_arr(FILE *f, int *arr, size_t n)
{
    for (int *cur = arr; cur < arr + n; cur++)
        fprintf(f, "%d ", *cur);
    fprintf(f, "\n");
}
