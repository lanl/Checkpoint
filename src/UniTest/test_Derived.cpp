#include <test_Derived.h>
#include <Test.h>

#include <memory>

void test_Derived(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "Derived";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "equal", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        Derived a{42, "Hello"};
        Derived b{42, "Hello"};
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
        Derived a{42, "Hello"};
        Derived b{24, "Hello"};
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
        Derived a{42, "Hello"};
        Derived b{42, "World"};
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
        Derived a{expected, "Hello"};
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
        Derived a{42, expected};
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
        Derived a{42, "Hello"};
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
        std::string expected = "         42Hello";
        Base* a = new Derived(42, "Hello");
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
        std::string expected = "         42Hello";
        std::unique_ptr<Base> a = std::unique_ptr<Derived>
                                  {new Derived(42, "Hello")};
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
        std::string expected = "         42Hello";
        std::shared_ptr<Base> a = std::shared_ptr<Derived>
                                  {new Derived(42, "Hello")};
        std::string actual = a->to_string();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_Derived.cpp
