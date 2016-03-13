#include "strutil.h"
#include "vlenc.h"

#include <stdio.h>
#include <string.h>

void test_split_inline()
{
    const char* teststrings[] = {
        "This is a test string", "This,is,,a,test,string", ",This,is,,a,test,string,", ",", "", NULL
    };

    char buf[64];
        
    for (const char** strp = teststrings; *strp; ++strp) {
        char* tmp = strncpy(buf, *strp, sizeof(buf)-1);
        
        printf("strutil_split_inline(\"%s\"):\n  ", tmp);

        char* split;
        int   n = 0;
        while ((split = strutil_split_inline(tmp, ',', &tmp)) != NULL)
            printf("%s\"%s\"", (n++ > 0 ? ", " : ""), split);

        puts("\n(done)\n");
    }
}

void test_split_copy()
{
    const char* teststrings[] = {
        "This is a test string", "This,is,,a,test,string", ",This,is,,a,test,string,", "", NULL
    };

    char buf[64];
    
    for (const char** strp = teststrings; *strp; ++strp) {
        const char* tmp = *strp;
        
        printf("strutil_split_copy(\"%s\"):\n  ", tmp);

        char* split;
        int   n = 0;
        while ((split = strutil_split_copy(tmp, ',', buf, &tmp)) != NULL)
            printf("%s\"%s\"", (n++ > 0 ? ", " : ""), split);


        puts("\n(done)\n");
    }
}

void test_flatten()
{
    const char* strings[] = { "This", " ", "is", " ", "a", " ", "test", NULL };

    char res[64];

    printf("Test flatten      64: %s\n", strutil_flatten(res, 64, strings));
    printf("Test flatten       7: %s\n", strutil_flatten(res,  7, strings));

    printf("Test flatten_n 7  64: %s\n", strutil_flatten_n(res, 64, 7, strings));
    printf("Test flatten_n 7   7: %s\n", strutil_flatten_n(res,  7, 7, strings));
    printf("Test flatten_n 3  64: %s\n", strutil_flatten_n(res, 64, 3, strings));

    printf("Test flatten_nd 7 64: %s\n", strutil_flatten_nd(res, 64, 7, strings, ","));
    printf("Test flatten_nd 7  7: %s\n", strutil_flatten_nd(res,  7, 7, strings, ","));
    printf("Test flatten_nd 3 64: %s\n", strutil_flatten_nd(res, 64, 3, strings, ","));

    printf("Test flatten_d    64: %s\n", strutil_flatten_d(res, 64, strings, ","));
    printf("Test flatten_d     7: %s\n", strutil_flatten_d(res,  7, strings, ","));
}

void test_vlenc()
{
    puts("*** Test vlenc: ");
    
    uint64_t inputs[8] = { 0, 1, 127, 128, 0xdeadbeef, 1337, 0xFFFFFFFFFFFFFFFF, 4242 };

    for (int i = 0; i < 8; ++i) {
        union {
            uint64_t      i;
            unsigned char bytes[8];
        } bytes;

        bytes.i = inputs[i];
        
        printf("enc: %10ld   %#19lx   0x%02x %02x %02x %02x %02x %02x %02x %02x   0x",
               bytes.i, bytes.i,
               bytes.bytes[0], bytes.bytes[1], bytes.bytes[2], bytes.bytes[3],
               bytes.bytes[4], bytes.bytes[5], bytes.bytes[6], bytes.bytes[7]);

        unsigned char buf[10] = { 0 };
        size_t        p, len  = vlenc_u64(inputs[i], buf);

        for (p = 0; p < len; ++p)
            printf("%02x ", buf[p]);

        puts("");

        bytes.i = vldec_u64(buf, NULL);

        printf("dec: %10ld   %#19lx   0x%02x %02x %02x %02x %02x %02x %02x %02x\n\n",
               bytes.i, bytes.i,
               bytes.bytes[0], bytes.bytes[1], bytes.bytes[2], bytes.bytes[3],
               bytes.bytes[4], bytes.bytes[5], bytes.bytes[6], bytes.bytes[7]);
    }

    unsigned char buf[128]   = { 0 };
    unsigned char*  p        = buf;

    for (int i = 0; i < 8; ++i)
        p += vlenc_u64(inputs[i], p);

    printf("Encoded %d integers in %lu bytes: 0x", 8, (p-buf));

    for (int i = 0; i < (p-buf); ++i)
        printf("%02x ", buf[i]);

    puts("\n");

    size_t   n = 0;

    for (int i = 0; i < 8; ++i) {
        printf("pos: %4lu   ", n);
        printf("in: %#19lx   out: %#19lx\n", inputs[i], vldec_u64(buf+n, &n));
    }

    puts("*** Test vlenc done.");
}

int main(int argc, const char* argv[])
{
    /* test_flatten(); */
    test_split_inline();
    test_split_copy();
    test_vlenc();
    
    return 0;
}
