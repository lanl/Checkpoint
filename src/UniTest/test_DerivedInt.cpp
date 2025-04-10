#include <Test.h>
#include <DerivedInt.h>

#include <memory>

void test_DerivedInt(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "DerivedInt";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "equal", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        DerivedInt a{42};
        DerivedInt b{42};
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
        DerivedInt a{42};
        DerivedInt b{24};
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
        char expected = 'i';
        DerivedInt a{2};
        char actual = *std::get<0>(a._t_);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "int", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int expected = 12;
        DerivedInt a{expected};
        int actual = *std::get<1>(a._t_);
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "to_string", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        std::string expected = "         52";
        DerivedInt a{52};
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
        std::string expected = "         62";
        BaseClass* a = new DerivedInt(62);
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
        std::string expected = "         72";
        std::unique_ptr<BaseClass> a = std::unique_ptr<DerivedInt>
                                       {new DerivedInt(72)};
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
        std::string expected = "         82";
        std::shared_ptr<BaseClass> a = std::shared_ptr<DerivedInt>
                                       {new DerivedInt(82)};
        std::string actual = a->to_string();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_DerivedInt.cpp
