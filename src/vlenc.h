/*! \file  vlenc.h
 *  \brief Variable-length integer encoding
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief Write 64-bit value into buffer using variable-length encoding.
 *  
 * \param  val  64-bit unsigned integer value to be written.
 * \param  buf  Character buffer. Must be large enough to hold 10 bytes.
 * \return      Number of bytes written.
 */
inline size_t
vlenc_u64(uint64_t val, unsigned char* buf)
{
    size_t nbytes = 1;

    *buf++ = val & 0x7F;

    while (val > 0x7F) {
        val    >>= 7;
        *buf++   = (val & 0x7F) | 0x80;
        ++nbytes;
    }

    return nbytes;
}

/*! \brief Read variable-length encoded 64-bit value from buffer.
 *
 * \param  buf  Buffer to read from.
 * \param  inc  The function increments this value by the number of bytes read.
 * \return      The decoded value.
 */    
inline uint64_t
vldec_u64(const unsigned char* buf, size_t* inc)
{
    uint64_t val = buf[0] & 0x7F;
    size_t   p   = 1;

    for ( ; p < 10 && (buf[p] & 0x80); ++p)
        val |= ((uint64_t) (buf[p] & 0x7F) << (7*p));
    
    if (inc)
        *inc += p;
    
    return val;
}
    
#ifdef __cplusplus
} /* extern "C" */
#endif
