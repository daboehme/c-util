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
 * or equal than n. Otherwise, the function returns \param n.
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

/*! \brief Split a string in-line by replacing \param delim with '\0'
 */

char*
strutil_split_inline(char* src, char delim, char** next);

/*! \brief Split a string by replacing \param delim with '\0'
 */

char*
strutil_split_copy(const char* src, char delim, char* dst, const char** next);

#ifdef __cplusplus
} /* extern "C" */
#endif
