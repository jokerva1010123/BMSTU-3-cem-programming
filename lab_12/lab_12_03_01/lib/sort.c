#include "../inc/functions.h"
#include "../inc/mymain.h"
#include "../inc/sort.h"

void swap(void *a1, void *a2, int size)
{
    char *p = a1, *q = a2, temp;

    for (int i = 0; i < size; i++)
    {
        temp = *p;
        *p = *q;
        *q = temp;
        p++; q++;
    }
}

int mycmp(const void *a, const void *b)
{
    int p = *(int *)a;
    int q = *(int *)b;
    return (p - q);
}

void mysort(void *base, size_t len, size_t size, int (*cmp)(const void*, const void*))
{
    if (len <= 0 || base == NULL || cmp == NULL)
        return;
    char *ptemp1, *ptemp2, *pbegin, *pend;
    char *pa = (char*)base;
    for (pbegin = pa, pend = pa + len * size ; pbegin < pend - size; pbegin += size)
        for (ptemp1 = pa; ptemp1 < pend - (pbegin - pa) - size; ptemp1 += size)
        {
            ptemp2 = ptemp1 + size;
            if (cmp(ptemp1, ptemp2) > 0)
                swap(ptemp1, ptemp2, size);
        }
}

