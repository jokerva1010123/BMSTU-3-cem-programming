#include "../inc/filter.h"
#include "../inc/functions.h"
#include "../inc/mymain.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (!pb_src || !pe_src || !pb_dst || !pe_dst)
        return POINTER_ERR;

    if (pb_src >= pe_src)
        return POINTER_ERR;

    size_t len = pe_src - pb_src;

    size_t p = len;

    for (int *cur = (int *)pb_src; cur < pe_src; cur++)
        if (*cur < 0)
            p = cur - pb_src;

    if (!p)
        return FILTER_ERR;

    int *pa_dst = (int *)malloc(p * sizeof(int));
    if (!pa_dst)
        return ALLOCATION_ERR;

    memcpy(pa_dst, pb_src, sizeof(int) * p);

    *pb_dst = pa_dst;
    *pe_dst = pa_dst + p;

    return SUCCESS;
}