#include "strutil.h"

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


int main(int argc, const char* argv[])
{
    /* test_flatten(); */
    test_split_inline();
    test_split_copy();
    
    return 0;
}
