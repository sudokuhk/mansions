/*************************************************************************
    > File Name: test_string.c
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 14:25:15
 ************************************************************************/
//gcc test_string.c mon_printf.c mon_string.c -I. -I.. -g

#include <stdio.h>

#include <mon_string.h>
#include <mon_printf.h>

#include <string.h>

int main()
{
    int8_t * str = "abcdefg";
    int8_t  ia  = 'A';
    int8_t  i8  = '8';
    int16_t i16 = 16;
    int32_t i32 = 32;
    int64_t i64 = 64;
    double  d64 = 123.123;
    int8_t buf[200];
    size_t off = 0;

    printf("mon_isdigit:%d\n", mon_isdigit(i8)); 
    printf("mon_isdigit:%d\n", mon_isdigit(ia)); 
    printf("str:%s, len:%llu\n", str, mon_strlen(str));
    
    mon_strcpy(buf, str);
    printf("buf:%s, len:%llu\n", buf, mon_strlen(buf));

    off += mon_snprintf(buf, 200, "mon_snprintf:%%, %d, %s, %010.10f, a:%f",
        i16, str, d64, d64);
    buf[off] = 0;
    printf("off:%d, out:%s\n", off, buf);

    off = 0;
    off += mon_snprintf(buf, 200, "mon_snprintf:%XD",
        i16);
    buf[off] = 0;
    printf("off:%d, out:%s\n", off, buf);
    
    return 0;
}

