#include <test_fact.h>
#include <Test.h>

#include <checkpoint.h>
#include <checkpoint_reg.h>

void test_fact(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "fact";

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "factorial10_no_checkpoint", "slow");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::reset_defaults();
        fact::trigger = "0:0:20";
        fact::verbose = false;
        checkpoint::verbose = false;
        std::string name = "factorial10_no_checkpoint6";
        std::string dir = "./UniTest/wrk/";
        checkpoint::init(name, dir, fact::trigger, true);
        int expected = 3628800;
        int actual = fact::factorial(10, name);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "factorial10_with_checkpoint6", "slow");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int n = 10;
        int expected = 3628800;

        // run up to checkpoint and pause
        fact::trigger = "0:0:6";
        fact::verbose = false;
        checkpoint::verbose = false;
        std::string name = "factorial10_with_checkpoint6";
        std::string dir = "./UniTest/wrk/";
        checkpoint::init(name, dir, fact::trigger, false);
        checkpoint::name = "";
        int f = fact::factorial(n, name);
        (void)(f);
        
        // restart from checkpoint
        checkpoint::init(fact::trigger, dir, fact::trigger, true);
        checkpoint_reg::restart = new CheckpointFile(checkpoint::name,
                                                     checkpoint::maxbytes,
                                                     checkpoint::myrank, 'r');
        fact::trigger = "0:0:6";
        fact::verbose = false;
        int actual = fact::factorial(n, name);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "factorial10_with_checkpoint6_split", "slow");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int n = 10;
        int expected = 3628800;

        // run up to checkpoint and pause
        fact::trigger = "0:0:6";
        fact::verbose = false;
        checkpoint::verbose = false;
        std::string name = "factorial10_with_checkpoint6_split";
        std::string dir = "./UniTest/wrk/";
        checkpoint::init(name, dir, fact::trigger, false, 4);
        checkpoint::verbose = false;
        checkpoint::name = "";
        int f = fact::factorial(n, name);
        (void)(f);
        
        // restart from checkpoint
        checkpoint::init(name, dir, fact::trigger, false, 4);
        checkpoint_reg::restart = new CheckpointFile(checkpoint::name,
                                                     checkpoint::maxbytes,
                                                     checkpoint::myrank, 'r');
        fact::trigger = "0:0:6";
        fact::verbose = false;
        int actual = fact::factorial(n, name);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "factorial10_with_checkpoint6_file", "slow");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        int n = 10;

        // run up to checkpoint and pause
        fact::trigger = "0:0:6";
        fact::verbose = false;
        checkpoint::verbose = false;
        std::string name = "factorial10_with_checkpoint6_file";
        std::string dir = "./UniTest/wrk/";
        checkpoint::init(name, dir, fact::trigger, false);
        checkpoint::name = "";
        int f = fact::factorial(n, name);
        
        // restart from checkpoint
        checkpoint::init(fact::trigger, dir, fact::trigger, false);
        checkpoint_reg::restart = new CheckpointFile(checkpoint::name,
                                                     checkpoint::maxbytes,
                                                     checkpoint::myrank, 'r');
        fact::trigger = "0:0:6";
        fact::verbose = false;
        f = fact::factorial(n, name);
        (void)(f); // throw away this result

        std::string expected = "123456789a";
        std::ifstream istr(fact::fname.c_str());
        std::string actual;
        istr >> actual;
        istr.close();
        istr.clear();
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//  end test_fact.cpp
