#include <Test.h>
#include <Base.h>

void test_Base(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Base";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "equal", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Base a{42};
        Base b{42};
        bool expected = true;
        bool actual = a == b;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "not_equal", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Base a{42};
        Base b{24};
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
        Base a{expected};
        int actual = *std::get<0>(a._t_);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "         42";
        Base a{42};
        std::string actual = a.to_string();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Base.cpp
