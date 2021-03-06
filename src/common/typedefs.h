/*************************************************************************
    > File Name: typedefs.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 09:38:41
 ************************************************************************/

#ifndef __MON_TYPE_DEF_H__
#define __MON_TYPE_DEF_H__

#include <unistd.h>

#ifndef NULL
#define NULL 0
#endif

/* There is some amount of overlap with <sys/types.h> as known by inet code */
#ifndef __int8_t_defined
# define __int8_t_defined
typedef signed char             int8_t;
typedef short int               int16_t;
typedef int                     int32_t;
# if __WORDSIZE == 64
typedef long int                int64_t;
# else
//__extension__
typedef long long int           int64_t;
# endif
#endif

/* Unsigned.  */
typedef unsigned char         uint8_t;
typedef unsigned short int    uint16_t;
#ifndef __uint32_t_defined
typedef unsigned int          uint32_t;
# define __uint32_t_defined
#endif
#if __WORDSIZE == 64
typedef unsigned long int       uint64_t;
#else
//__extension__
typedef unsigned long long int    uint64_t;
#endif

/* Types for `void *' pointers.  */
#if __WORDSIZE == 64
# ifndef __intptr_t_defined
typedef long int               intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned long int    uintptr_t;
#else
# ifndef __intptr_t_defined
typedef int                    intptr_t;
#  define __intptr_t_defined
# endif
typedef unsigned int        uintptr_t;
#endif

#if __WORDSIZE == 64
typedef uint64_t            size_t;
typedef int64_t             ssize_t;
#else
typedef uint32_t            size_t;
typedef int32_t             ssize_t;
#endif

typedef pid_t               mon_pid_t;

#endif
