/*=============================================================================

test_MDArray.cpp
Definitions for tests for multi-dimensional array class template.

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 29 November 2014
Last modified on 10 April 2025

=============================================================================*/

//  Note: only use trimmed strings for names

#include <Test.h>
#include <MDArray.h>

#include <stdexcept>
#include <vector>

void test_MDArray(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "MDArray";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_7_of_9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        MDIndex dim, indx; // dimension, index
        dim.push_back(9); // dimension #0
        indx.push_back(7);
        size_t expected = 7;
        MDArray<int> a{dim};
        size_t actual = a.many_to_one(indx);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_0000_00", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        size_t expected = 0;
        MDArray<int> a{dim};
        size_t actual = a.many_to_one(MDIndex{0, 0, 0, 0});

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_2001_13", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        size_t expected = 13;
        MDArray<double> a{dim};
        size_t actual(a.many_to_one(MDIndex{2, 0, 0, 1}));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_3102_23", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        size_t expected = 23;
        MDArray<char> a{dim};
        size_t actual(a.many_to_one(MDIndex{3, 1, 0, 2}));

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_3112_out_of_range", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected = "out of range exception";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            MDArray<std::string> a{dim};
            size_t j = a.many_to_one(MDIndex{3, 1, 1, 2});
            std::cout << j << std::endl;
        }
        catch (const std::out_of_range &oor)
        {
            actual = "out of range exception";
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "many_to_one_range_error", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        std::string expected = "Error: many_to_one ranges do not conform:\n";
        expected += "dimensions =          4\nindices =          3";
        std::string actual = UNCAUGHT_EXCEPTION;
        try
        {
            MDArray<float> a{dim};
            size_t j = a.many_to_one(MDIndex{3, 1, 0});
            std::cout << j << std::endl;
        }
        catch (const std::range_error &oor)
        {
            actual = oor.what();
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "initialize_default", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 0;
        MDArray<int> a{dim};
        int actual = a[MDIndex{1, 1, 0, 1}];

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "initialize_42", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 42;
        MDArray<int> a{dim, expected};
        int actual = a[MDIndex{2, 0, 0, 1}];

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "set_get_99", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        MDIndex indx{2, 0, 0, 1};
        int expected = 99;
        MDArray<int> a{dim};
        a[indx] = expected;
        int actual = a[indx];

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "dims", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        MDArray<int> a{dim};
        auto dims = a.dims();
        {
            size_t expected = 4;
            size_t actual = dims[0];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            size_t expected = 2;
            size_t actual = dims[1];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            size_t expected = 1;
            size_t actual = dims[2];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            size_t expected = 3;
            size_t actual = dims[3];
            failed_test_count += t.check_equal(expected, actual);
        }
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_constructor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 42;
        MDArray<int> a{dim, expected};
        MDArray<int> b{a};
        int actual = b[MDIndex{2, 0, 0, 1}];

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_assignment", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 42;
        MDArray<int> a{dim, expected}, b{MDIndex{5}}, c{MDIndex{2, 3}};
        c = b = a;
        int actual = c[MDIndex{2, 0, 0, 1}];

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "copy_assignment_to_self", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 42;
        MDArray<int> a{dim, expected};
        MDArray<int>* b = &a;
        *b = a;
        int actual = b->operator[](MDIndex{2, 0, 0, 1});

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "move_constructor", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 42;
        MDArray<int> a{dim, expected};
        MDArray<int> b{std::move(a)};
        int actual = b[MDIndex{2, 0, 0, 1}];

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "move_assignment", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 42;
        MDArray<int> a{dim, expected}, b{MDIndex{5}};
        b = std::move(a);
        int actual = b[MDIndex{2, 0, 0, 1}];

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "move_assignment_to_self", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        #include <indirect_indexing.inc>
        int expected = 42;
        MDArray<int> a{dim, expected};
        MDArray<int>* b = &a;
        *b = std::move(a);
        int actual = b->operator[](MDIndex{2, 0, 0, 1});

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_MDArray.cpp
