/*=============================================================================

test_CArray.cpp
Definitions for tests for one-dimensional C-style array class template.

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 23 April 2023
Last modified on 27 July 2024

=============================================================================*/

//  Note: only use trimmed strings for names

#include <test_CArray.h>
#include <Test.h>

#include <cstdlib>

void test_CArray(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "CArray";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <CArray.inc>
        size_t expected = 2;
        size_t actual = a.n_;
        free(v);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "elements", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <CArray.inc>
        {
            int expected = 5;
            int actual = a.d_[0];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            int expected = 7;
            int actual = a.d_[1];
            failed_test_count += t.check_equal(expected, actual);
        }
        free(v);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_CArray.cpp
