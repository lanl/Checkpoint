// Driver to demo Checkpoint-restart

/**
 * @file chkpt\_main.cpp
 * @brief Checkpoint-restart demo driver
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

#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

#include <checkpoint.h>
#include <checkpoint_reg.h>
#include <CheckpointFile.h>
#include <fact.h>
#include <MDArray.h>

#include <ctime>

#ifdef MPI
#include <mpi.h>
#endif

//-----------------------------------------------------------------------------

const std::string main_name = "chkpt";

//-----------------------------------------------------------------------------

void print_usage()
{
    std::cout << "Usage: ./" << main_name << " <options_file> [checkpoint_name]";
    #ifdef _OPENMP
    std::cout << " [nthreads=1]";
    #endif
    std::cout << std::endl;
}

//-----------------------------------------------------------------------------

int main(int argc, char **argv)
{
    if (argc < 2  ||  argc > 3)
    {
        print_usage();
        return EXIT_FAILURE;
    }

    std::ifstream options_file(argv[1]);
    std::string x;

    std::string name_of_run;
    options_file >> x >> name_of_run;
    std::cout << x << " " << name_of_run << std::endl;

    int n = 0;
    options_file >> x >> n;
    std::cout << x << " " << n << std::endl;

    std::string dir;
    options_file >> x >> dir;
//    std::cout << x << " " << dir << std::endl;

    size_t maxsize = 0;
    options_file >> x >> maxsize;
//    std::cout << x << " " << maxsize << std::endl;

    options_file >> x >> fact::trigger;
//    std::cout << x << " " << fact::trigger << std::endl;

    std::string stopstr;
    options_file >> x >> stopstr;
    std::cout << x << " " << stopstr << std::endl;

    checkpoint::init(name_of_run, dir, fact::trigger, stopstr=="true", maxsize);
    if (argc == 3)
    {
        checkpoint::index = static_cast<size_t>(std::stoi(argv[2]));
        checkpoint::name = checkpoint::path + name_of_run + '_' + argv[2];
        checkpoint_reg::restart = new CheckpointFile(checkpoint::name,
                                                     checkpoint::maxbytes,
                                                     checkpoint::myrank, 'r');
    }
    checkpoint::verbose = true;

    fact::verbose = true;
    int f = fact::factorial(n, main_name);
    std::cout << "result: " << f << std::endl;

    checkpoint::print_end_and_stop();
    return EXIT_SUCCESS;
}

//-----------------------------------------------------------------------------

//  end chkpt_main.cpp
