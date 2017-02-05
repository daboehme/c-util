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

/*! \file  strutil.h
 *  \brief Miscellaneous string utility functions.
 */

#pragma once

#include <stddef.h> /* size_t */

#ifdef __cplusplus
extern "C" {
#endif

inline const char*
strutil_find_first_of(const char* src, const char* chars)
{
    const char* c = "";

    for ( ; *src && *src != *c; ++src)
        for (c = chars; *c && *c != *src; ++c)
            ;

    return src;
}


/*! \brief Return the length of the string s or n, whichever is smaller.
 *
 * The strutil_strnlen() function returns the length of the string given in 
 * s, excluding the terminating null byte, if the string length is less
 * or equal than n. Otherwise, the function returns \a n.
 *
 * This function is thread-safe and signal-safe.
 */

inline size_t
strutil_strnlen(const char* s, size_t n)
{ 
    size_t len = 0;

    for ( ; len < n && *s++; ++len)
        ;

    return len;
}

/*! \brief Concatenate a list of strings into a single string.
 */

char*
strutil_flatten_d(char* dst, size_t dst_len, const char* src[], 
                      const char* delim);

inline char*
strutil_flatten(char* dst, size_t dst_len, const char* src[])
{
    return strutil_flatten_d(dst, dst_len, src, NULL);
}

char* 
strutil_flatten_nd(char* dst, size_t dst_len, size_t num_src, const char* src[], 
                       const char* delim);

inline char* 
strutil_flatten_n(char* dst, size_t dst_len, size_t num_src, const char* src[])
{
    return strutil_flatten_nd(dst, dst_len, num_src, src, NULL);
}

/*! \brief Split a string in-line by replacing \a delim with '\0'
 */

char*
strutil_split_inline(char* src, char delim, char** next);

/*! \brief Split a string by replacing \a delim with '\0'
 */

char*
strutil_split_copy(const char* src, char delim, char* dst, const char** next);

#ifdef __cplusplus
} /* extern "C" */
#endif
