
//  Note: only use trimmed strings for names

#include <test_CheckpointFile.h>
#include <Test.h>


void test_CheckpointFile(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "CheckpointFile";
const std::string FILEPATH = "./UniTest/wrk/";
const size_t MAXBYTES = 8;

//-----------------------------------------------------------------------------
{
    Test t(GROUP, "ndigits0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 0;
        int expected = 1;
        int actual = CheckpointFile::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 9;
        int expected = 1;
        int actual = CheckpointFile::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits10", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 10;
        int expected = 2;
        int actual = CheckpointFile::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits360", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 360;
        int expected = 3;
        int actual = CheckpointFile::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------
#ifndef WIN
// value-changing conversion from long long int to size_t on Windows
{
    Test t(GROUP, "ndigits2147483647", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 2147483647;
        int expected = 10;
        int actual = CheckpointFile::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits21474836470", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 21474836470;
        int expected = 11;
        int actual = CheckpointFile::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "ndigits_over_limit", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 214748364700;
        int expected = 0;
        int actual = CheckpointFile::ndigits(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}
#endif
//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int2string0", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 0;
        std::string expected = "_0";
        std::string actual = CheckpointFile::int2string(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int2string9", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 9;
        std::string expected = "_9";
        std::string actual = CheckpointFile::int2string(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int2string10", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        size_t i = 10;
        std::string expected = "_10";
        std::string actual = CheckpointFile::int2string(i);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = int;
        size_t n = sizeof(T);

        T expected = -42;
        std::string fname = FILEPATH + GROUP + "-int";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'w');
        f.write_data(reinterpret_cast<const char*>(&expected), n);
        }

        T actual = 0;
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'r');
        f.read_data(reinterpret_cast<char*>(&actual), n);
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "size_t", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = size_t;
        size_t n = sizeof(T);

        T expected = 42;
        std::string fname = FILEPATH + GROUP + "-size_t";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'w');
        f.write_data(reinterpret_cast<const char*>(&expected), n);
        }

        T actual = 0;
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'r');
        f.read_data(reinterpret_cast<char*>(&actual), n);
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "float", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = float;
        size_t n = sizeof(T);

        T expected = -3.14f;
        std::string fname = FILEPATH + GROUP + "-float";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'w');
        f.write_data(reinterpret_cast<const char*>(&expected), n);
        }

        T actual = 0.0f;
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'r');
        f.read_data(reinterpret_cast<char*>(&actual), n);
        }

        failed_test_count += t.check_equal_real_num(expected, actual, 1e-5f);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = double;
        size_t n = sizeof(T);

        T expected = 3.14;
        std::string fname = FILEPATH + GROUP + "-double";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'w');
        f.write_data(reinterpret_cast<const char*>(&expected), n);
        }

        T actual = 0.0;
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'r');
        f.read_data(reinterpret_cast<char*>(&actual), n);
        }

        failed_test_count += t.check_equal_real_num(expected, actual, 1e-5);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "char", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = char;
        size_t n = sizeof(T);

        T expected = 'W';
        std::string fname = FILEPATH + GROUP + "-char";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'w');
        f.write_data(reinterpret_cast<const char*>(&expected), n);
        }

        T actual = '0';
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'r');
        f.read_data(reinterpret_cast<char*>(&actual), n);
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = std::string;

        T expected = "Hello";
        size_t n = expected.size() + 1;  // account for buffer-terminating '\0'
        std::string fname = FILEPATH + GROUP + "-string";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'w');
        f.write_data(expected.c_str(), n);
        }

        char* b = (char*)malloc(n);
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'r');
        f.read_data(b, n);
        }
        T actual(b);
        free(b);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "split_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = std::string;
        const size_t SIZE_OF_CHAR = sizeof(char);

        T expected = "This longer string will be split.";
        size_t n = expected.size();
        std::string fname = FILEPATH + GROUP + "-split_string";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'w');
        for (size_t i = 0; i < n; ++i) f.write_data(&expected[i], SIZE_OF_CHAR);
        char c = '\0';
        f.write_data(&c, SIZE_OF_CHAR);
        }

        T actual = "";
        {
        CheckpointFile f(fname, MAXBYTES, 0, 'r');
        char c = '\0';
        for (;;)
        {
            f.read_data(&c, SIZE_OF_CHAR);
            if ('\0' == c) break;
            actual += c;
        }
        }

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_CheckpointFile.cpp
