#include <test_Data.h>
#include <Test.h>

void test_Data(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Data";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "equal", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Data a{42, "Hello"};
        Data b{42, "Hello"};
        bool expected = true;
        bool actual = a == b;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_equal_int", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Data a{42, "Hello"};
        Data b{24, "Hello"};
        bool expected = false;
        bool actual = a == b;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_equal_string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Data a{42, "Hello"};
        Data b{42, "World"};
        bool expected = false;
        bool actual = a == b;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 42;
        Data a{expected, "Hello"};
        int actual = *std::get<0>(a._t_);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "Hello";
        Data a{42, expected};
        std::string actual = *std::get<1>(a._t_);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "         42Hello";
        Data a{42, "Hello"};
        std::string actual = a.to_string();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Data.cpp
