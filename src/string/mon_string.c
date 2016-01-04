/*************************************************************************
    > File Name: mon_string.c
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 14:09:46
 ************************************************************************/

#include <mon_string.h>

int32_t mon_isdigit(int8_t ch)
{
    return ch >= '0' && ch <= '9';
}

size_t mon_strlen(int8_t * str)
{
    size_t len = 0;
    if (str != NULL) {
        for (; *str; str ++, len ++);
    }
    return len;
}

int8_t * mon_strcpy(int8_t * dst, const int8_t * src)
{
    int8_t * pdst = dst;
    while ((*pdst ++ = *src ++));
    return dst;
}

