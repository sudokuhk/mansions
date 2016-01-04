/*************************************************************************
    > File Name: macro.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-28 21:08:06
 ************************************************************************/

#ifndef __MON_MACRO_H__
#define __MON_MACRO_H__

#define MON_ARRAY_SIZE(array)   \
    (sizeof(array) / sizeof(array[0]))

#define MON_MAX(a, b)   ((a) > (b) ? (a) : (b))
#define MON_MIN(a, b)   ((a) < (b) ? (a) : (b))
#define MON_ABS(a)      ((a) > 0 ? (a) : -(a))
        
#define mon_memcpy(dst, src, n) \
    ((int8_t *)(memcpy(dst, src, n)) + n)

#define __cdecl  //__attribute__((__cdecl__))
    
#if ((__GNU__ == 2) && (__GNUC_MINOR__ < 8))
#define MON_MAX_UINT32_VALUE  (uint32_t) 0xffffffffLL
#else
#define MON_MAX_UINT32_VALUE  (uint32_t) 0xffffffff
#endif

#define MON_MAX_INT32_VALUE   (uint32_t) 0x7fffffff
#endif
