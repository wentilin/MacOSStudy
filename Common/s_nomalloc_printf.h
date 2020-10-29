//
//  s_nomalloc_printf.h
//  MacOSStudy
//
//  Created by linwenhu on 2020/10/29.
//

#ifndef s_nomalloc_printf_h
#define s_nomalloc_printf_h

#include <stdarg.h>
#include <unistd.h>

extern void _simple_vdprintf(int, const char *, va_list);

static inline void nomalloc_printf(const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    _simple_vdprintf(STDOUT_FILENO, format, ap);
    va_end(ap);
}

#endif /* s_nomalloc_printf_h */
