
//  Note: only use trimmed strings for names

#include <Test.h>
#include <checkpoint.h>

#include <CheckpointFile.h>
#include <Data.h>
#include <Derived.h>
#include <MDArray.h>
#include <derived_factory.h>

#include <memory>

void test_checkpoint(int &failed_test_count, int &disabled_test_count)
{
const std::string GROUP = "checkpoint";
const std::string FILEPATH = "./UniTest/wrk/";
const size_t MAXBYTES = 8;

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "trigger_h", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::verbose = false;
        checkpoint::init("trigger_h", "./UniTest/wrk/", "03", true);
        int expected = 10800;
        int actual = checkpoint::trigger_in_seconds;
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "trigger_hm", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::verbose = false;
        checkpoint::init("trigger_hm", "./UniTest/wrk/", "003:2", true);
        int expected = 10920;
        int actual = checkpoint::trigger_in_seconds;
        checkpoint::reset_defaults();
        
        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "trigger_hms", "fast");
    
    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::verbose = false;
        checkpoint::init("trigger_hms", "./UniTest/wrk/", "03:02:01", true);
        int expected = 10921;
        int actual = checkpoint::trigger_in_seconds;
        checkpoint::reset_defaults();
        
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
        checkpoint::name = FILEPATH + GROUP + "-int";
        checkpoint::verbose = false;

        T expected = -4242;
        std::tuple<T*> te;
        std::get<0>(te) = &expected;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, te);
        }

        T actual = 0;
        std::tuple<T*> ta;
        std::get<0>(ta) = &actual;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(ta, fr);
        checkpoint::reset_defaults();

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
        checkpoint::name = FILEPATH + GROUP + "-size_t";
        checkpoint::verbose = false;

        T expected = 424242;
        std::tuple<T*> te;
        std::get<0>(te) = &expected;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, te);
        }

        T actual = 0;
        std::tuple<T*> ta;
        std::get<0>(ta) = &actual;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(ta, fr);
        checkpoint::reset_defaults();

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
        checkpoint::name = FILEPATH + GROUP + "-float";
        checkpoint::verbose = false;

        T expected = -2.71f;
        std::tuple<T*> te;
        std::get<0>(te) = &expected;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, te);
        }

        T actual = 0.0f;
        std::tuple<T*> ta;
        std::get<0>(ta) = &actual;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(ta, fr);
        checkpoint::reset_defaults();

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
        checkpoint::name = FILEPATH + GROUP + "-double";
        checkpoint::verbose = false;

        T expected = 2.71;
        std::tuple<T*> te;
        std::get<0>(te) = &expected;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, te);
        }

        T actual = 0.0;
        std::tuple<T*> ta;
        std::get<0>(ta) = &actual;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(ta, fr);
        checkpoint::reset_defaults();

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
        checkpoint::name = FILEPATH + GROUP + "-char";
        checkpoint::verbose = false;

        T expected = 'R';
        std::tuple<T*> te;
        std::get<0>(te) = &expected;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, te);
        }

        T actual = 'W';
        std::tuple<T*> ta;
        std::get<0>(ta) = &actual;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(ta, fr);
        checkpoint::reset_defaults();

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
        checkpoint::name = FILEPATH + GROUP + "-string";
        checkpoint::verbose = false;

        T expected = "Hello World!";
        std::tuple<T*> te;
        std::get<0>(te) = &expected;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, te);
        }

        T actual = "Wrong string";
        std::tuple<T*> ta;
        std::get<0>(ta) = &actual;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(ta, fr);
        checkpoint::reset_defaults();

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
        checkpoint::name = FILEPATH + GROUP + "-split_string";
        checkpoint::verbose = false;
        checkpoint::maxbytes = 6;

        T expected = "This string is split into several files";
        std::tuple<T*> te;
        std::get<0>(te) = &expected;
        {
            CheckpointFile fw(checkpoint::name, checkpoint::maxbytes, 0, 'w');
            checkpoint::write(fw, te);
        }

        T actual = "Wrong string";
        std::tuple<T*> ta;
        std::get<0>(ta) = &actual;
        CheckpointFile fr(checkpoint::name, checkpoint::maxbytes, 0, 'r');
        checkpoint::read(ta, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vector_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using U = int;
        using T = std::vector<U>;
        checkpoint::name = FILEPATH + GROUP + "-vector_int";
        checkpoint::verbose = false;

        T w{-42, 4242};
        std::tuple<T*> tw;
        std::get<0>(tw) = &w;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        T r{0, 0};
        std::tuple<T*> tr;
        std::get<0>(tr) = &r;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        {
            U expected = w[0];
            U actual = r[0];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            U expected = w[1];
            U actual = r[1];
            failed_test_count += t.check_equal(expected, actual);
        }
        checkpoint::reset_defaults();
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vector_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using U = double;
        using T = std::vector<U>;
        checkpoint::name = FILEPATH + GROUP + "-vector_double";
        checkpoint::verbose = false;

        T w{-3.14, 6.28};
        std::tuple<T*> tw;
        std::get<0>(tw) = &w;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        T r{0.0, 0.0};
        std::tuple<T*> tr;
        std::get<0>(tr) = &r;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        {
            U expected = w[0];
            U actual = r[0];
            failed_test_count += t.check_equal_real_num(expected, actual, 1e-9);
        }
        {
            U expected = w[1];
            U actual = r[1];
            failed_test_count += t.check_equal_real_num(expected, actual, 1e-9);
        }
        checkpoint::reset_defaults();
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vector_char", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using U = char;
        using T = std::vector<U>;
        checkpoint::name = FILEPATH + GROUP + "-vector_char";
        checkpoint::verbose = false;

        T w{'c', 'h'};
        std::tuple<T*> tw;
        std::get<0>(tw) = &w;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        T r{'X', 'Y'};
        std::tuple<T*> tr;
        std::get<0>(tr) = &r;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        {
            U expected = w[0];
            U actual = r[0];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            U expected = w[1];
            U actual = r[1];
            failed_test_count += t.check_equal(expected, actual);
        }
        checkpoint::reset_defaults();
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "vector_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using U = std::string;
        using T = std::vector<U>;
        checkpoint::name = FILEPATH + GROUP + "-vector_string";
        checkpoint::verbose = false;

        T w{" This is ", "a string"};
        std::tuple<T*> tw;
        std::get<0>(tw) = &w;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        T r{"Wrong string", "Wrong string"};
        std::tuple<T*> tr;
        std::get<0>(tr) = &r;
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        {
            U expected = w[0];
            U actual = r[0];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            U expected = w[1];
            U actual = r[1];
            failed_test_count += t.check_equal(expected, actual);
        }
        checkpoint::reset_defaults();
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "split_vector_double", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using U = double;
        using T = std::vector<U>;
        checkpoint::name = FILEPATH + GROUP + "-split_vector_double";
        checkpoint::verbose = false;
        checkpoint::maxbytes = 8;

        T w{-3.14, 6.28};
        std::tuple<T*> tw;
        std::get<0>(tw) = &w;
        {
            CheckpointFile fw(checkpoint::name, checkpoint::maxbytes, 0, 'w');
            checkpoint::write(fw, tw);
        }

        T r{0.0, 0.0};
        std::tuple<T*> tr;
        std::get<0>(tr) = &r;
        CheckpointFile fr(checkpoint::name, checkpoint::maxbytes, 0, 'r');
        checkpoint::read(tr, fr);
        {
            U expected = w[0];
            U actual = r[0];
            failed_test_count += t.check_equal_real_num(expected, actual, 1e-9);
        }
        {
            U expected = w[1];
            U actual = r[1];
            failed_test_count += t.check_equal_real_num(expected, actual, 1e-9);
        }
        checkpoint::reset_defaults();
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Data", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = Data;
        checkpoint::name = FILEPATH + GROUP + "-Data";
        checkpoint::verbose = false;

        T expected{42, "Hello"};
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, expected);
        }

        T actual{0, "Wrong string"};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(actual, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Data_tuple", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = Data;
        checkpoint::name = FILEPATH + GROUP + "-Data";
        checkpoint::verbose = false;

        T expected{42, "Hello"};
        std::tuple<T*> tw{&expected};
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        T actual{0, "Wrong string"};
        std::tuple<T*> tr{&actual};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Derived", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = Derived;
        checkpoint::name = FILEPATH + GROUP + "-Derived";
        checkpoint::verbose = false;

        T expected{42, "Hello"};
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, expected);
        }

        T actual{0, "Wrong string"};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(actual, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Derived_tuple", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = Derived;
        checkpoint::name = FILEPATH + GROUP + "-Derived_tuple";
        checkpoint::verbose = false;

        T expected{42, "Hello"};
        std::tuple<T*> tw{&expected};
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        T actual{0, "Wrong string"};
        std::tuple<T*> tr{&actual};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Derived_tuple_new", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = Derived;
        checkpoint::name = FILEPATH + GROUP + "-Derived_tuple_new";
        checkpoint::verbose = false;

        Base* expected_ptr = new T{42, "Hello: new pointer"};
        std::tuple<Base*> tw{expected_ptr};
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        Base* actual_ptr = new T{0, "Wrong string"};
        std::tuple<Base*> tr{actual_ptr};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(*expected_ptr, *actual_ptr);
        delete actual_ptr;
        delete expected_ptr;
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Derived_tuple_shared_ptr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = Derived;
        checkpoint::name = FILEPATH + GROUP + "-Derived_tuple_shared_ptr";
        checkpoint::verbose = false;

        std::shared_ptr<Base> expected_ptr = std::shared_ptr<Base>
                                             {new T{42, "HelloSharedPointer"}};
        std::tuple<Base*> tw{&*expected_ptr};
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        std::shared_ptr<Base> actual_ptr = std::shared_ptr<Base>
                                           {new T{0, "Wrong string"}};
        std::tuple<Base*> tr{&*actual_ptr};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(*expected_ptr, *actual_ptr);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "Derived_tuple_unique_ptr", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        using T = Derived;
        checkpoint::name = FILEPATH + GROUP + "-Derived_tuple_unique_ptr";
        checkpoint::verbose = false;

        std::unique_ptr<Base> expected_ptr = std::unique_ptr<Base>
                                             {new T{42, "HelloUniquePointer"}};
        std::tuple<Base*> tw{&*expected_ptr};
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, tw);
        }

        std::unique_ptr<Base> actual_ptr = std::unique_ptr<Base>
                                           {new T{0, "Wrong string"}};
        std::tuple<Base*> tr{&*actual_ptr};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(tr, fr);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(*expected_ptr, *actual_ptr);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "MDArray_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::name = FILEPATH + GROUP + "-MDArray_int";
        checkpoint::verbose = false;

        std::string expected = " 11 12 13 14 15 16";
        std::vector<size_t> dim{2, 3};
        MDArray<int> a{dim};
        a[std::vector<size_t>{0, 0}] = 11;
        a[std::vector<size_t>{0, 1}] = 12;
        a[std::vector<size_t>{0, 2}] = 13;
        a[std::vector<size_t>{1, 0}] = 14;
        a[std::vector<size_t>{1, 1}] = 15;
        a[std::vector<size_t>{1, 2}] = 16;
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, a);
        }

        MDArray<int> b{dim};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(b, fr);
        std::string actual =
            b.int_to_string(b[std::vector<size_t>{0, 0}], ' ', 3)
          + b.int_to_string(b[std::vector<size_t>{0, 1}], ' ', 3)
          + b.int_to_string(b[std::vector<size_t>{0, 2}], ' ', 3)
          + b.int_to_string(b[std::vector<size_t>{1, 0}], ' ', 3)
          + b.int_to_string(b[std::vector<size_t>{1, 1}], ' ', 3)
          + b.int_to_string(b[std::vector<size_t>{1, 2}], ' ', 3);
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "MDArray_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::name = FILEPATH + GROUP + "-MDArray_string";
        checkpoint::verbose = false;

        std::vector<size_t> dim{2, 3};
        MDArray<std::string> a{dim};
        a[std::vector<size_t>{0, 0}] = "Mary";
        a[std::vector<size_t>{0, 1}] = "had";
        a[std::vector<size_t>{0, 2}] = "a";
        a[std::vector<size_t>{1, 0}] = "little";
        a[std::vector<size_t>{1, 1}] = "lamb";
        a[std::vector<size_t>{1, 2}] = ".";
        std::string expected = a[std::vector<size_t>{0, 0}] + " "
                             + a[std::vector<size_t>{0, 1}] + " "
                             + a[std::vector<size_t>{0, 2}] + " "
                             + a[std::vector<size_t>{1, 0}] + " "
                             + a[std::vector<size_t>{1, 1}] + " "
                             + a[std::vector<size_t>{1, 2}];
        {
            CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
            checkpoint::write(fw, a);
        }

        MDArray<std::string> b{dim};
        CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
        checkpoint::read(b, fr);
        std::string actual = b[std::vector<size_t>{0, 0}] + " "
                           + b[std::vector<size_t>{0, 1}] + " "
                           + b[std::vector<size_t>{0, 2}] + " "
                           + b[std::vector<size_t>{1, 0}] + " "
                           + b[std::vector<size_t>{1, 1}] + " "
                           + b[std::vector<size_t>{1, 2}];
        checkpoint::reset_defaults();

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "CArray_size", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::name = FILEPATH + GROUP + "-CArray_size";
        #include <CArray_write.inc>
        size_t expected = n;

        #include <CArray_read.inc>
        size_t actual = b.n_;
        checkpoint::reset_defaults();
        free(v);
        free(r);

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "CArray_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::name = FILEPATH + GROUP + "-CArray_int";
        #include <CArray_write.inc>
        #include <CArray_read.inc>
        {
            U expected = v[0];
            U actual = r[0];
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            U expected = v[1];
            U actual = r[1];
            failed_test_count += t.check_equal(expected, actual);
        }
        checkpoint::reset_defaults();
        free(v);
        free(r);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "multilayer_string", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::reset_defaults();
        checkpoint::name = FILEPATH + GROUP + "-multilayer_string";
        #include <multilayer_write.inc>
        #include <multilayer_read.inc>
        std::string expected = sw;
        std::string actual = sr;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "multilayer_Data", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::reset_defaults();
        checkpoint::name = FILEPATH + GROUP + "-multilayer_Data";
        #include <multilayer_write.inc>
        #include <multilayer_read.inc>
        {
            Data expected = vw.at(0);
            Data actual = vr.at(0);
            failed_test_count += t.check_equal(expected, actual);
        }
        {
            Data expected = vw.at(1);
            Data actual = vr.at(1);
            failed_test_count += t.check_equal(expected, actual);
        }
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "multilayer_int", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::reset_defaults();
        checkpoint::name = FILEPATH + GROUP + "-multilayer_int";
        #include <multilayer_write.inc>
        #include <multilayer_read.inc>
        int expected = nw;
        int actual = nr;

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "DerivedInt", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::reset_defaults();
        checkpoint::name = FILEPATH + GROUP + "-derived_int";
        #include <derived_write.inc>
        #include <derived_read.inc>
        std::string expected = dw[0]->to_string();
        std::string actual = dr[0]->to_string();
        #include <derived_delete.inc>

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

{
    Test t(GROUP, "DerivedString", "fast");

    t.check_to_disable_test(disabled_test_count);
    if (t.is_enabled())
    {
        checkpoint::reset_defaults();
        checkpoint::name = FILEPATH + GROUP + "-derived_string";
        #include <derived_write.inc>
        #include <derived_read.inc>
        std::string expected = dw[1]->to_string();
        std::string actual = dr[1]->to_string();
        #include <derived_delete.inc>

        failed_test_count += t.check_equal(expected, actual);
    }
}

//-----------------------------------------------------------------------------

}

//-----------------------------------------------------------------------------

//  end test_checkpoint.cpp
