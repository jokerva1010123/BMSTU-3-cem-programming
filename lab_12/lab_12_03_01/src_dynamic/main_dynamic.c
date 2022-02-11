#include "../inc/mymain.h"

int (*key)(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);
int (*count_int)(FILE *f, size_t *size);
int (*file_to_array)(FILE *f, int *pa, int *pb);
void (*print_arr)(FILE *f, int *arr, size_t n);
void (*swap)(void *elem1, void *elem2, int size);
int (*mycmp)(const void *a, const void *b);
void (*mysort)(void *base, size_t len, size_t size, int (*cmp)(const void*, const void*));

int load()
{       
    void *libarr = dlopen("arr.dll", RTLD_LAZY);
    if (libarr == NULL)
        return LIB_ERR;
    key = dlsym(libarr, "key");
    count_int = dlsym(libarr, "count_int");
    file_to_array = dlsym(libarr, "file_to_array");
    print_arr = dlsym(libarr, "print_arr");
    swap = dlsym(libarr, "swap");
    mycmp = dlsym(libarr, "mycmp");
    mysort = dlsym(libarr, "mysort");
    return SUCCESS;
}   

int main(int argc, char *argv[])
{
    if (argc != MIN_ARGC && argc != MAX_ARGC)
        return ARG_ERR;
    if (argc == MAX_ARGC && strcmp(argv[3], "f") != 0)
        return ARG_ERR;

    int rc = 0;

    FILE *f_in = fopen(argv[1], "r");
    if (!f_in)
        return OPEN_ERR;

    FILE *f_out = fopen(argv[2], "w");
    if (!f_out)
        return OPEN_ERR;
    rc = load();
    if (rc)
        return rc;
    size_t n = 0;
    rc = count_int(f_in, &n);
    if (rc)
    {
        fclose(f_in);
        return rc;
    }

    int *arr = NULL;
    arr = (int *)malloc(n * sizeof(int));
    if (!arr)
    {
        fclose(f_in);
        return ALLOCATION_ERR;
    }
    fseek(f_in, 0, SEEK_SET);

    rc = file_to_array(f_in, arr, arr + n);
    if (rc)
    {
        free(arr);
        fclose(f_in);
        return READ_ERR;
    }

    int filter_key = 0;
    if (argc == MAX_ARGC)
        filter_key = 1;

    if (!filter_key)
    {
        mysort(arr, n, sizeof(int), mycmp);
        print_arr(f_out, arr, n);
    }
    else
    {
        int *dst_bg = NULL;
        int *dst_end = NULL;
        rc = key(arr, arr + n, &dst_bg, &dst_end);
        if (rc)
        {
            free(arr);
            fclose(f_in);
            fclose(f_out);
            return rc;
        }

        n = dst_end - dst_bg;
        mysort(dst_bg, n, sizeof(int), mycmp);
        print_arr(f_out, dst_bg, n);
        free(dst_bg);
    }
    free(arr);
    fclose(f_in);
    fclose(f_out);

    return rc;
}