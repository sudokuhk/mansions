/*************************************************************************
    > File Name: mon_string.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 14:08:31
 ************************************************************************/

#ifndef __MON_STRING_H__
#define __MON_STRING_H__

#include <typedefs.h>

int32_t mon_isdigit(int8_t ch);

size_t mon_strlen(int8_t * str);

int8_t * mon_strcpy(int8_t * dst, const int8_t * src);

#endif
