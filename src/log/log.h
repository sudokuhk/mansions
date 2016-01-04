/*************************************************************************
    > File Name: log.h
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-28 22:58:10
 ************************************************************************/

#ifndef __MON_LOG_H__
#define __MON_LOG_H__

#include <typedefs.h>

//RFC 3164
enum LOG_LEVEL {
    LOG_EMER    = 0,
    LOG_ALERT,
    LOG_CRIT,
    LOG_ERR,
    LOG_WARN,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG,
};

typedef struct mon_log_s {
    uint32_t log_level;
} mon_log_t;

#define LOG_PRIMASK         (0x07)
#define LOG_FACILITY(p)     ((p) & LOG_PRIMASK)
#define LOG_PRI(fac, pri)   (((fac) << 3) | (pri))

#if (MON_HAVE_C99_VARIADIC_MACROS)

#define MON_HAVE_VARIADIC_MACROS    1

#define mon_log_error(level, log, ...)                      \
    if ((log)->log_level >= level && level <= LOG_DEBUG) {  \
        mon_log_error_impl(level, log, __VA_ARGS__);        \
    }
    
void mon_log_error_impl(uint32_t level, mon_log_t * log, 
    const char * fmt, ...);

#elif (MON_HAVE_GCC_VARIADIC_MACROS)                    

#define MON_HAVE_VARIADIC_MACROS    1

#define mon_log_error(level, log, args...)                  \
    if ((log)->log_level >= level && level <= LOG_DEBUG) {  \
        mon_log_error_impl(level, log, args);               \
    }

void mon_log_error_impl(uint32_t level, mon_log_t * log,
    const char * fmt, ...);

#else

#define MON_HAVE_VARIADIC_MACROS    0

void mon_log_error(uint32_t level, mon_log_t * log, 
    const char * fmt, ...);

void mon_log_error_impl(uint32_t level, mon_log_t * log,
    const char * fmt, ...);
#endif

#endif
