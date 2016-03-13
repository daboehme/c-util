#include "vlenc.h"

extern inline size_t
vlenc_u64(uint64_t val, unsigned char* buf);

extern inline uint64_t
vldec_u64(const unsigned char* buf, size_t* inc);
