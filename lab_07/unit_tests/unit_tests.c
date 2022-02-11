#include <time.h>

#include "../inc/functions.h"

#define N 10
#define TRUE 1
#define FALSE 0

void swap(void *elem1, void *elem2, int size)
{
    char *p = elem1, *q = elem2, temp;

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

int last_neg(int *beg, int *end)
{
    int neg_index = end - beg;
    for (int *cur = (int *)beg; cur < end; cur++)
        if (*cur < 0)
            neg_index = cur - beg;
    return neg_index;
}

int test_key()
{
    time_t t;
    srand((unsigned)time(&t));
    int *pb_src = malloc(sizeof(int) * N);
    int *pe_src = pb_src + N;
    int *ptemp = pb_src;
    for (; ptemp < pe_src; ptemp++)
        *ptemp = rand() % 10000 - 5000;
    int *pb_dst = NULL;
    int *pe_dst = NULL;
    key(pb_src, pe_src, &pb_dst, &pe_dst);
    int x = last_neg(pb_src, pe_src);
    if (x == pe_dst - pb_dst)
        return TRUE;
    return FALSE;
}

int test_comp()
{
    time_t t;
    srand((unsigned)time(&t));
    int value_a = rand() % 10000 - 5000;
    int value_b = rand() % 10000 - 5000;
    if (mycmp(&value_a, &value_b) == value_a - value_b)
        return TRUE;
    return FALSE;
}
int test_swap()
{
    time_t t;
    srand((unsigned)time(&t));
    int value_a = rand() % 10000 - 5000;
    int value_b = rand() % 10000 - 5000;
    int temp1 = value_a;
    int temp2 = value_b;
    swap(&value_a, &value_b, sizeof(int));
    if (value_a == temp2 && value_b == temp1)
        return TRUE;
    return FALSE;
}

int main()
{   
    int count = 0;

    count += test_swap();
    count += test_swap();
    count += test_swap();
    printf("%d/3 Test Swap Passed\n", count);

    count = 0;
    count += test_comp();
    count += test_comp();
    count += test_comp();
    printf("%d/3 Test Comparator Passed\n", count);

    count = 0;
    count += test_key();
    count += test_key();
    count += test_key();
    printf("%d/3 Test Key Passed\n", count);

    return EXIT_SUCCESS;
}
