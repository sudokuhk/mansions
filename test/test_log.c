/*************************************************************************
    > File Name: test_log.c
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 09:41:49
 ************************************************************************/
//gcc test_log.c log.c -I. -I.. -I../string -DMON_HAVE_GCC_VARIADIC_MACROS ../string/mon_string.c ../string/mon_printf.c

#include <log.h>

int main()
{
    mon_log_t log;
    log.log_level = LOG_DEBUG;
    mon_log_error(LOG_DEBUG, &log, "abcd\n");
    mon_log_error(LOG_DEBUG, &log, "1 args:%s\n", "hi");

    return 0;
}
