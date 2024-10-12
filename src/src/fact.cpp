/**
 * @file fact.cpp
 * @brief Checkpoint demo using factorial
 * @author Peter Hakel
 * @version 0.0
 * @date Created in 2023\n
 * Last modified on 10 October 2024
 * @copyright (c) 2024, Triad National Security, LLC.
 * All rights reserved.\n
 * Use of this source code is governed by the BSD 3-Clause License.
 * See top-level license.txt file for full license text.
 */

/*
Copyright 2024. Triad National Security, LLC. All rights reserved.
This program was produced under U.S. Government contract 89233218CNA000001
for Los Alamos National Laboratory (LANL), which is operated by Triad National Security, LLC
for the U.S. Department of Energy/National Nuclear Security Administration.
All rights in the program are reserved by Triad National Security, LLC, and
the U.S. Department of Energy/National Nuclear Security Administration.
The Government is granted for itself and others acting on its behalf a nonexclusive, paid-up,
irrevocable worldwide license in this material to reproduce, prepare derivative works,
distribute copies to the public, perform publicly and display publicly,
and to permit others to do so.
*/

#include <fact.h>
#include <checkpoint.h>
#include <checkpoint_reg.h>

#include <iostream>
#include <fstream>
#include <tuple>

#include <unistd.h>

#ifdef WIN
#include <windows.h>
#endif

//-----------------------------------------------------------------------------

std::string fact::trigger = "1000";
bool fact::verbose = fact::verbose_default;
std::string fact::fname = "";

//-----------------------------------------------------------------------------

int fact::factorial(const int n, const std::string& run_name)
{
    int i0 = 1;
    int f = 1;
    std::string filename = "./UniTest/wrk/" + run_name + "_"
                         + checkpoint::local_time() + ".txt";

    // register state of local scope
    std::get<0>(checkpoint_reg::t_fact) = &i0;
    std::get<1>(checkpoint_reg::t_fact) = &f;
    std::get<2>(checkpoint_reg::t_fact) = &filename;

    // body
    if (n < 0) return 0;
    if (n == 0) return 1;
    
    std::string c = "0123456789a"; // for writing progress to file

    if (checkpoint::name == "")
    {   // normal path (no checkpoint)
        f = 1;
        i0 = 1;
        filename = "./UniTest/wrk/" + run_name + "_"
                 + checkpoint::local_time() + ".txt";
        fname = filename;
    }
    else
    {   // reload checkpoint
        checkpoint::read(checkpoint_reg::t_fact, *checkpoint_reg::restart);
        delete checkpoint_reg::restart; // after the last read
        fname = filename;
        if (verbose)
        {
            std::cout << "i0: " << i0 << std::endl;
            std::cout << "f: " << f << std::endl;
            std::cout << "trigger: " << trigger << std::endl;
            std::cout << "name: " << checkpoint::name << std::endl;
            std::cout << "fname: " << fname << std::endl;
        }
    }

    std::ofstream os(fname.c_str(), std::ofstream::app);
    for (int i = i0; i <= n; ++i)
    {
        if (checkpoint::trigger())
        {   // launch checkpoint-writing procedure
            checkpoint::set_name();
            i0 = i;
            os.close();
            os.clear();
            checkpoint_reg::write();
            if (checkpoint::stopflag) checkpoint::print_end_and_stop();
            if (verbose) std::cout << "Continuing after checkpoint: "
                                   << checkpoint::name << std::endl;
        }

#ifdef WIN
        Sleep(1000);
#else
        sleep(1);
#endif

        f *= i;
        if (verbose) std::cout << i << ": " << f << std::endl;
        os << c[static_cast<size_t>(i)];
    }
    os.close();
    os.clear();

    // restore static defaults
    trigger = "1000";
    verbose = verbose_default;

    return f;
}

//-----------------------------------------------------------------------------

//  end file fact.cpp
