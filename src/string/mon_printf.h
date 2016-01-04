/*************************************************************************
    > File Name: mon_printf.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 14:07:30
 ************************************************************************/

#ifndef __MON_PRINTF_H__
#define __MON_PRINTF_H__

#include <typedefs.h>
#include <macro.h>

#include <stdarg.h>

size_t __cdecl mon_vsnprintf(int8_t * buf, size_t max, const char * fmt, va_list args);

size_t __cdecl mon_snprintf(int8_t * buf, size_t max, const char * fmt,  ...);

#endif
