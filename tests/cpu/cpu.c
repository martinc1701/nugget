/*

MIT License

Copyright (c) 2020 PCSX-Redux authors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "common/syscalls/syscalls.h"

#undef unix
#define CESTER_NO_SIGNAL
#define CESTER_NO_TIME
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#include "exotic/cester.h"

CESTER_BODY(
    uint32_t branchbranch1();
    uint32_t branchbranch2();
    uint32_t jumpjump1();
    uint32_t jumpjump2();
    uint32_t cpu_LWR_LWL_half(uint32_t buff[], uint32_t initial);
    uint32_t cpu_LWR_LWL_nodelay(uint32_t buff[], uint32_t initial);
    uint32_t cpu_LWR_LWL_delayed(uint32_t buff[], uint32_t initial);
)

CESTER_TEST(cpu_LWR_LWL_half, test_instance,
    uint32_t buff[2] = {0x11223344, 0x55667788};
    uint32_t out = cpu_LWR_LWL_half(buff, 0xaabbccdd);
    cester_assert_uint_eq(0x88bbccdd, out);
)

CESTER_TEST(cpu_LWR_LWL_nodelay, test_instance,
    uint32_t buff[2] = {0x11223344, 0x55667788};
    uint32_t out = cpu_LWR_LWL_nodelay(buff, 0xaabbccdd);
    cester_assert_uint_eq(0xaabbccdd, out);
)

CESTER_TEST(cpu_LWR_LWL_delayed, test_instance,
    uint32_t buff[2] = {0x11223344, 0x55667788};
    uint32_t out = cpu_LWR_LWL_delayed(buff, 0xaabbccdd);
    cester_assert_uint_eq(0x88112233, out);
)

CESTER_TEST(cpu_BRANCH_BRANCH_slot, test_instance,
    uint32_t out = branchbranch1();
    cester_assert_uint_eq(0x189, out);
    out = branchbranch2();
    cester_assert_uint_eq(2, out);
)

CESTER_TEST(cpu_JUMP_JUMP_slot, test_instance,
    uint32_t out = jumpjump1();
    cester_assert_uint_eq(0x69, out);
    out = jumpjump2();
    cester_assert_uint_eq(3, out);
)
