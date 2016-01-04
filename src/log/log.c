/*************************************************************************
    > File Name: log.c
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-28 23:44:07
 ************************************************************************/

#include <log.h>

#include <stdio.h>
#include <stdarg.h>

const char * log_level_s[] = {
    NULL, 
    "emerg",
    "alert",
    "crit",
    "error",
    "warn",
    "notice",
    "info",
    "debug",
};

#if !(MON_HAVE_VARIADIC_MACROS)
void mon_log_error(uint32_t level, mon_log_t * log, 
    const char * fmt, ...)
{
    va_list args;
    
    if (log->log_level >= level && level <= LOG_DEBUG) {
        va_start(args, fmt);
        mon_log_error_impl(level, log, fmt, args);
        va_end(args);
    }
}
#endif

#if (MON_HAVE_VARIADIC_MACROS)
void mon_log_error_impl(uint32_t level, mon_log_t * log,
    const char * fmt, ...)
#else
void mon_log_error_impl(uint32_t level, mon_log_t * log,
    const char * fmt, va_list args) 
#endif
{
#if (MON_HAVE_VARIADIC_MACROS)
    va_list args;
#endif

#define LOG_BUF_SIZE 4096
    int8_t buf[LOG_BUF_SIZE] = {0};   
    size_t offset = 0, max = LOG_BUF_SIZE;
    
    offset += mon_snprintf(buf + offset, max - offset, "[%s]", log_level_s[level]); 
#if (MON_HAVE_VARIADIC_MACROS)
    va_start(args, fmt);
    offset += mon_vsnprintf(buf + offset, max - offset, fmt, args);
    va_end(args);
#endif
    buf[offset] = 0;

    fwrite(buf, offset, 1, stdout);
    
    return;
}
