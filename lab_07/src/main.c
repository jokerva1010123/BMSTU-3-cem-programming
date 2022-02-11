#include "../inc/functions.h"
#include "../inc/filter.h"
#include "../inc/sort.h"

int main(int argc, char **argv)
{
    if (argc != MIN_ARGC && argc != MAX_ARGC)
        return ARG_ERR;
    if (argc == MAX_ARGC && strcmp(argv[3], "f") != 0)
        return ARG_ERR;

    FILE *f_in = fopen(argv[1], "r");
    if (!f_in)
        return OPEN_FILE_ERR;

    FILE *f_out = fopen(argv[2], "w");
    if (!f_out)
        return OPEN_FILE_ERR;

    int rc = 0;
    int *parr_beg = NULL;
    int *parr_end = NULL;
    rc = read_int_from_file(f_in, &parr_beg, &parr_end);
    if (rc)
        return rc;

    fclose(f_in);

    int key_filter = 0;
    if (argc == MAX_ARGC)
        key_filter = 1;

    size_t n = parr_end - parr_beg;
    if (!key_filter)
    {
        mysort(parr_beg, n, sizeof(int), mycmp);
        print_arr(f_out, parr_beg, n);
    }
    else
    {
        int *dst_bg = NULL;
        int *dst_end = NULL;
        rc = key(parr_beg, parr_end, &dst_bg, &dst_end);
        if (rc)
            return rc;
        n = dst_end - dst_bg;
        mysort(dst_bg, n, sizeof(int), mycmp);
        print_arr(f_out, dst_bg, n);
        free(dst_bg);
    }

    free(parr_beg);
    fclose(f_out);
    return EXIT_SUCCESS;
}