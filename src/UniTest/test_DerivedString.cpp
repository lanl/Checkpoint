#include <Test.h>
#include <DerivedString.h>

#include <memory>

void test_DerivedString(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "DerivedString";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "equal", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        DerivedString a{"derived_str"};
        DerivedString b{"derived_str"};
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
        DerivedString a{"derived_str"};
        DerivedString b{"other_str"};
        bool expected = false;
        bool actual = a == b;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "type", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        char expected = 's';
        DerivedString a{"derived_str"};
        char actual = *std::get<0>(a._t_);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "my_str";
        DerivedString a{expected};
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
        std::string expected = "to_string_test";
        DerivedString a{expected};
        std::string actual = a.to_string();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "new_to_string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "new_string";
        BaseClass* a = new DerivedString(expected);
        std::string actual = a->to_string();
        delete a;
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "unique_ptr_to_string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "unique_str";
        std::unique_ptr<BaseClass> a = std::unique_ptr<DerivedString>
                                       {new DerivedString(expected)};
        std::string actual = a->to_string();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "shared_ptr_to_string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "shared_str";
        std::shared_ptr<BaseClass> a = std::shared_ptr<DerivedString>
                                       {new DerivedString(expected)};
        std::string actual = a->to_string();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_DerivedString.cpp
