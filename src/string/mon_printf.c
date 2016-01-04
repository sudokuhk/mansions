/*************************************************************************
    > File Name: mon_printf.c
    > Author: sudoku.huang
    > Mail: sudoku.huang@gmail.com 
    > Created Time: 2015-12-29 10:39:32
 ************************************************************************/

#include <mon_printf.h>

#include <stdarg.h>

size_t mon_sprintf_num(int8_t * buf, size_t max, uint64_t ui64, int8_t zero,
    uint32_t hexadecimal, uint32_t width)
{
    static int8_t hex[] = "0123456789abcdef";
    static int8_t HEX[] = "0123456789ABCDEF";

    size_t off = 0, len;
    int8_t tmp[30] = {0}, *p;
    uint32_t ui32;
    p = &tmp[MON_ARRAY_SIZE(tmp) - 1];
    
    if (hexadecimal == 0) {
        if (ui64 <= (uint64_t)MON_MAX_UINT32_VALUE) {
            ui32 = (uint32_t)ui64;
            do {
                *--p = (int8_t)(ui32 % 10 + '0');
            } while (ui32 /= 10);
        } else {
            do {
                *--p = (int8_t)(ui64 % 10 + '0');
            } while (ui64 /= 10);
        }
    } else if (hexadecimal == 1) {
        do {
            *--p = hex[(uint32_t) (ui64 & 0xf)];
        } while (ui64 >>= 4);
    } else if (hexadecimal == 2) {
        do {
            *--p = HEX[(uint32_t) (ui64 & 0xf)];
        } while (ui64 >>= 4);
    }
    
    len = &tmp[MON_ARRAY_SIZE(tmp) - 1] - p;
    while (off < max && len ++ < width) {
        buf[off ++] = zero;
    }
    
    len = &tmp[MON_ARRAY_SIZE(tmp) - 1] - p;
    len = MON_MIN(max - off, len);
    
    mon_memcpy(buf + off, p, len);
    off += len;
    
    return off;
}

size_t mon_vsnprintf(int8_t * buf, size_t max, const char * fmt, va_list args)
{
    size_t off = 0;
    uint32_t width, sign, hex, max_width, frac_width, n;
    int64_t i64;
    uint64_t ui64, frac, scale;
    size_t len, slen;
    double f, t;
    int8_t zero, ch;
    int8_t * ptr;
 
    while ( *fmt && off < max) {
        if (*fmt == '%') {
            ++ fmt;

            i64     = 0;
            ui64    = 0;
            
            zero    = (* fmt) == '0' ? '0' : ' '; 
            width   = 0;
            sign    = 1;
            hex     = 0;
            max_width   = 0;
            frac_width  = 0;
            slen        = (size_t) -1;

            while (mon_isdigit(* fmt)) {
                width = width * 10 + (* fmt) - '0';
                ++ fmt;
            }
            
            while (ch = *fmt++) {
                switch (ch) {
                case 'u': 
                    sign = 0; 
                    continue;
                case 'm': 
                    max_width = 1; 
                    continue; 
                case 'X': 
                    hex = 2;
                    sign = 0; 
                    continue;
                case '*':
                    slen = va_arg(args, size_t);
                    continue;
                case '.':
                    while (mon_isdigit(*fmt)) {
                        frac_width = frac_width * 10 + *fmt++ - '0';
                    }
                    fmt ++;
                    break;
                default:
                    break;
                }
                fmt --;
                break;
            }
            
            switch (*fmt) {
                case 's':
                    ptr = va_arg(args, int8_t *);
                    len = MON_MIN(max - off, mon_strlen(ptr));
                    while ((off < max) && (buf[off ++] = *ptr ++));
                    off --; //due to copy '0 and end! sub.
                    fmt ++;
                    continue;
                case 'O':
                    i64     = (int64_t)va_arg(args, int64_t);
                    sign    = 1;
                    break;
                case 'P':
                    i64     = (int64_t)va_arg(args, pid_t);
                    sign    = 1;
                    break;
                /*case 'T':
                    i64     = (int64_t)va_arg(args, time_t);
                    sign    = 1;
                    break;*/
                case 'z':
                    if (sign) {
                        i64     = (int64_t)va_arg(args, ssize_t);
                    } else {
                        ui64    = (uint64_t)va_arg(args, size_t);
                    }
                    break;
                case 'i':
                    if (sign) {
                        i64     = (int64_t)va_arg(args, intptr_t);
                    } else {
                        ui64    = (uint64_t)va_arg(args, uintptr_t);
                    }    
                    break;
                case 'd':
                    if (sign) {
                        i64     = (int64_t)va_arg(args, int);
                    } else {
                        ui64    = (uint64_t)va_arg(args, unsigned int);
                    }    
                    break;
                case 'l':
                    if (sign) {
                        i64     = (int64_t)va_arg(args, long);
                    } else {
                        ui64    = (uint64_t)va_arg(args, unsigned long);
                    }    
                    break;
                 case 'D':
                    if (sign) {
                        i64     = (int64_t)va_arg(args, int32_t);
                    } else {
                        ui64    = (uint64_t)va_arg(args, uint32_t);
                    }    
                    break;
                case 'L':
                    if (sign) {
                        i64     = (int64_t)va_arg(args, int64_t);
                    } else {
                        ui64    = (uint64_t)va_arg(args, uint64_t);
                    }    
                    break;
                case 'f':
                    f = va_arg(args, double);
                    if (f < 0) {
                        buf[off ++] = '-';
                        f = -f;
                    }
                    
                    ui64    = (int64_t)f;
                    frac    = 0;
                    scale   = 1;
                    
                    if (frac_width) {
                        for (n = frac_width; n; n--) {
                            scale *= 10;
                        }
                        
                        frac = (uint64_t)((f - (double)ui64) * scale + 0.5);
                        
                        if (frac == scale) {
                            ui64 ++;
                            frac = 0;
                        }
                    } else {
                        f = (f - (double)ui64);
                        do {
                            frac_width ++;
                            scale   *= 10;
                            t       = f * scale;
                            frac    = (uint64_t)t;
                        } while ((t - frac) > 1e-8);
                    }
                    
                    off += mon_sprintf_num(buf + off, max - off, ui64, zero, 0, width);
                    
                    if (frac_width) {
                        if (off < max) {
                            buf[off ++] = '.';
                        }
                        off += mon_sprintf_num(buf + off, max - off, frac, '0', 0, frac_width);
                    }
                    fmt ++;
                    continue;
                case 'p':
                    ui64 = (uintptr_t)va_arg(args, uintptr_t);
                    hex  = 2;
                    sign = 0;
                    zero = '0';
                    break;
                case 'c':
                    ptr = va_arg(args, int8_t *);
                    buf[off ++] = *ptr;
                    fmt ++;
                    continue;
                case '%':
                    buf[off ++] = '%';
                    fmt ++;
                    continue;
                default:
                    buf[off ++] = *fmt ++;
                    continue;
            }    
            
            if (sign) {
                if (i64 < 0) {
                    buf[off ++] = '-';
                    ui64 = (uint64_t)-i64;
                } else {
                    ui64 = (uint64_t)i64;
                }
            }
            off += mon_sprintf_num(buf + off, max - off, ui64, zero, hex, width);
            fmt ++;
        } else {
            buf[off ++] = *fmt ++;
        }
    }
    return off;
}

size_t mon_snprintf(int8_t * buf, size_t max, const char * fmt,  ...)
{
    size_t size = 0;
    va_list args;
    
    va_start(args, fmt);
    size = mon_vsnprintf(buf, max, fmt, args);
    va_end(args);

    return size; 
}
