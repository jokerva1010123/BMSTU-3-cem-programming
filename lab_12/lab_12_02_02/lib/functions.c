#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

ARR_DLL void fibonacci_arr(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        if (i == 0 || i == 1)
            arr[i] = 1;
        else
            arr[i] = arr[i - 1] + arr[i - 2];
}

ARR_DLL int make_new_arr(int *arr, int *new, int size, int set_size)
{
    int new_size = 0;
    int exist = 0;
    for (int i = 0; i < size; i++)
    {
        exist = 0;
        for (int j = 0; j < i; j++)
            exist += (arr[j] == arr[i]);
        if (exist)
            continue;
        if (set_size)
            new[new_size] = arr[i];
        new_size++;
    }
    return new_size;
}
