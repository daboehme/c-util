#include "strutil.h"
#include "vlenc.h"

#include <iostream>

void test_vlenc()
{
    uint64_t      val     = 0xdeadbeef;
    unsigned char buf[64] = { 0 };

    vlenc_u64(val, buf);

    std::cout << vldec_u64(buf, nullptr) << " == " << val << std::endl;
}

int main()
{
    std::cout << "CXX link/use test" << std::endl;

    test_vlenc();
}
