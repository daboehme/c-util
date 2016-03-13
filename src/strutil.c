/* Copyright (c) 2016, David Boehme.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "strutil.h"

#define _GNU_SOURCE
#include <string.h> /* mempcpy() needs _GNU_SOURCE */ 


extern inline const char*
strutil_find_first_of(const char* src, const char* chars);


char*
strutil_split_inline(char* src, char delim, char** next)
{
    char* tmp = src;

    if (tmp) {
        while (*tmp && *tmp != delim)
            ++tmp;

        if (*tmp == delim)
            *tmp++ = '\0';
        else
             tmp   = NULL;
    }
    
    *next = tmp;

    return src;
}

char*
strutil_split_copy(const char* src, char delim, char* dst, const char** next)
{
    if (src) {
        char* tmp = dst;

        while (*src && *src != delim)
            *tmp++ = *src++;

        *tmp = '\0';

        if (*src++ == '\0')
            src = NULL;
    } else
        dst = NULL;
    
    *next = src;

    return dst;
}

#if 0
char*
strutil_escape(const char* src, const char* chars_to_esc, char esc, char* dst)
{

}

char*
strutil_unescape(const char* src, char esc, char* dst)
{

}
#endif

extern inline size_t 
strutil_strnlen(const char* s, size_t n);


extern inline char* 
strutil_flatten(char* dst, size_t dst_len, const char* src[]);

char* 
strutil_flatten_d(char* dst, size_t dst_len, const char* src[], const char* delim)
{
    char* p = dst;

    for (size_t n = 0; *src && (p-dst+1) < dst_len; ++src) {
        if (n++ > 0 && delim)
            p = mempcpy(p, delim, strutil_strnlen(delim, dst_len-(p-dst+1)));

        p = mempcpy(p, *src, strutil_strnlen(*src, dst_len-(p-dst+1)));
    }

    if ((p-dst) < dst_len)
        *p = '\0';

    return dst;
}

extern inline char* 
strutil_flatten_n(char* dst, size_t dst_len, size_t num_src, const char* src[]);

char* 
strutil_flatten_nd(char* dst, size_t dst_len, size_t num_src, const char* src[],
                   const char* delim)
{
    char* p = dst;

    for (size_t n = 0; n < num_src && (p-dst+1) < dst_len; ++n) {
        if (n && delim)
            p = mempcpy(p, delim, strutil_strnlen(delim, dst_len-(p-dst+1)));

        p = mempcpy(p, src[n], strutil_strnlen(src[n], dst_len-(p-dst+1)));
    }

    if ((p-dst) < dst_len)
        *p = '\0';

    return dst;
}

