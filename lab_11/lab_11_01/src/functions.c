#include "../inc/functions.h"

void reverse_string(char *str, int ind)
{
    for (int i = 0; i < ind / 2; i++)
    {
        char tmp = str[i];
        str[i] = str[ind - i - 1];
        str[ind - i - 1] = tmp;
    }
}

int translate_int(int data, char *str)
{
    int ind = 0;
    if (data == 0)
        str[ind++] = '0';
    while (data != 0)
    {
        char ch = data % 10 + '0';
        data /= 10;
        str[ind++] = ch;
    }
    reverse_string(str, ind);
    if (ind != 0)
        str[ind] = '\0';
    return ind;
}

int translate_sixteen(unsigned int data, char *str)
{   
    int ind = 0;
    if (data == 0)
        str[ind++] = '0';
    while (data != 0)
    {
        int num = data % 16;
        if (num < 10)
            str[ind++] = num + '0';
        else
        {
            char ch = 'a';
            for (int i = 10; i < num; i++)
                ch++;
            str[ind++] = ch;
        }
        data /= 16;
    }
    reverse_string(str, ind);
    if (ind != 0)
        str[ind] = '\0';
    return ind;
}

int int_type(int data, int size_limit, int *ind, char *str)
{
    int count = 0;
    if (data < 0)
    {
        if (size_limit > *ind)
            str[(*ind)++] = '-';
        count++;
        data *= -1;
    }
    char data_int[MAX_LEN];
    int len = translate_int(data, data_int);
    int i = 0;
    while (i < len)
    {
        if (size_limit > *ind)
            str[(*ind)++] = data_int[i];
        count++;
        i++;
    }  
    return count;  
}

int hex_type(unsigned int data, int size_limit, int *ind, char *str)
{
    char data_uint[MAX_LEN];
    int len = translate_sixteen(data, data_uint);
    int i = 0;
    while (i < len)
    {
        if (size_limit > *ind)
            str[(*ind)++] = data_uint[i];
        i++;
    }
    return i;
}

int char_type(char *str, char data, size_t max_size, int *index)
{
    if (*index < max_size)
        str[(*index)++] = data;
    return 1;
}

int string_type(char *str, char *data, size_t max_size, int *index)
{
    int i = 0;
    while (data[i] != '\0')
    {
        if (*index < max_size)
            str[(*index)++] = data[i];
        i++;
    }
    return i;
}

int my_snprintf(char *str, size_t size, const char *format, ...)
{
    va_list argument;
    va_start(argument, format);
    int input_cnt = 0;
    int index = 0;

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format ++;
            if (*format == SHORT && *(format + 1) == INT)
            {
                int data = va_arg(argument, int);
                input_cnt += int_type(data, size, &index, str);
                format += 2;
            }
            else if (*format == CHAR)
            {
                char data = va_arg(argument, int);
                input_cnt += char_type(str, data, size, &index);
                format++;
            }
            else if (*format == STRING)
            {
                char *data = va_arg(argument, char*);
                input_cnt += string_type(str, data, size, &index);
                format++;
            }
            else if (*format == HEX)
            {
                unsigned int data = va_arg(argument, unsigned int);
                input_cnt += hex_type(data, size, &index, str);
                format ++;
            }
        }
        else
        {
            input_cnt += char_type(str, *format, size, &index);
            format++;
        }
    }
    if (size == index && size != 0)
        str[index - 1] = '\0';
    else if (size > 0)
        str[index] = '\0';
    va_end(argument);
    return input_cnt;
}