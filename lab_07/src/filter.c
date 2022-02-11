#include "../inc/functions.h"
#include "../inc/filter.h"

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (!pb_src || !pe_src || !pb_dst || !pe_dst)
        return POINTER_ERR;

    if (pb_src >= pe_src)
        return POINTER_ERR;

    size_t len = pe_src - pb_src;
    size_t neg_index = len;
    for (int *cur = (int *)pb_src; cur < pe_src; cur++)
        if (*cur < 0)
            neg_index = cur - pb_src;
    if (!neg_index)
    {
        int *ptemp = (int*)pb_src;
        free(ptemp);
        return FILTER_ERR;
    }
    
    int *parr_des = (int *)malloc(neg_index * sizeof(int));
    if (!parr_des) 
        return ALLOCATION_ERR;

    memcpy(parr_des, pb_src, sizeof(int) * neg_index);

    *pb_dst = parr_des;
    *pe_dst = parr_des + neg_index;
    return SUCCESS;
}