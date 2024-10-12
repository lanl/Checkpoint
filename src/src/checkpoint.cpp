/**
 * @file checkpoint.cpp
 * @brief Checkpoint-restart
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

#include <checkpoint.h>

#include <cstdlib>
#include <ctime>

//-----------------------------------------------------------------------------

// Initial values for static variables within the "checkpoint" scope
TimePoint checkpoint::start_time = checkpoint::now();
bool checkpoint::verbose = true;
std::string checkpoint::base_name = "";
size_t checkpoint::index = 0;
std::string checkpoint::name = "";
std::string checkpoint::path = "";
size_t checkpoint::maxbytes = MAXBYTES_DEFAULT;
bool checkpoint::stopflag = false;
size_t checkpoint::myrank = 0;
int checkpoint::trigger_in_seconds = 0;

void checkpoint::reset_defaults()
{
    start_time = now();
    verbose = true;
    base_name = "";
    name = "";
    path = "";
    maxbytes = MAXBYTES_DEFAULT;
    myrank = 0;
    trigger_in_seconds = 0;
}

//-----------------------------------------------------------------------------

TimePoint checkpoint::now()
{
    return Clock::now();
}

//-----------------------------------------------------------------------------

void checkpoint::init(const std::string& name_root, const std::string& dir,
                      const std::string& trigger, const bool stop_flag,
                      const size_t maxsize)
{
    start_time = now();
    base_name = name_root;
    path = dir;
    stopflag = stop_flag;
    maxbytes = maxsize;

    std::vector<std::string> tokenized;
    std::string token = "";
    for (size_t i = 0; i < trigger.size(); ++i)
    {
        char c = trigger[i];
        if (c != ' ')
        {
            if (c == ':')
	        {
                tokenized.push_back(token);
                token = "";
            }
            else token.push_back(c);
        }
    }
    tokenized.push_back(token);

    int h = 0;
    int m = 0;
    int s = 0;
    size_t n = tokenized.size();
    if (n > 0) h = std::stoi(tokenized[0]);
    if (n > 1) m = std::stoi(tokenized[1]);
    if (n > 2) s = std::stoi(tokenized[2]);
    if (verbose) std::cout << "checkpoint::init has been called with trigger: "
                           << trigger << std::endl;
    trigger_in_seconds = h*3600 + m*60 + s;
}


//-----------------------------------------------------------------------------

long int checkpoint::runtime_in_seconds()
{
    auto duration = now() - start_time;
    return std::chrono::duration_cast<std::chrono::seconds>(duration).count();
}

//-----------------------------------------------------------------------------

bool checkpoint::trigger()
{
    return runtime_in_seconds() > trigger_in_seconds;
}

//-----------------------------------------------------------------------------

std::string checkpoint::local_time()
{
    time_t rawtime;
    struct tm * timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    std::string t = int_to_string(timeinfo->tm_year % 100, '0', 2)
                  + int_to_string(timeinfo->tm_mon + 1, '0', 2)
                  + int_to_string(timeinfo->tm_mday, '0', 2) + "_"
                  + int_to_string(timeinfo->tm_hour, '0', 2)
                  + int_to_string(timeinfo->tm_min, '0', 2)
                  + int_to_string(timeinfo->tm_sec, '0', 2);
    return t;
}

//-----------------------------------------------------------------------------

void checkpoint::set_name()
{
    ++index;
    std::string froot = base_name + "_"
                      + int_to_string(index, '0', CheckpointFile::ndigits(index));
    name = path + froot;
    if (verbose) std::cout << "Pausing for checkpoint: " << froot
                           << " in " << path << std::endl;
}

//-----------------------------------------------------------------------------

size_t checkpoint::size_of(const std::string& d)
{
    return d.size() + 1;
}

size_t checkpoint::size_of(const std::vector<std::string>& d)
{
    size_t nbytes = 0;
    size_t n = d.size();
    for (size_t i = 0; i < n; ++i) nbytes += size_of(d[i]);
    return nbytes;
}

//-----------------------------------------------------------------------------

void checkpoint::pack_data(CheckpointFile& f, const int d)
{
    f.write_data(reinterpret_cast<const char*>(&d), sizeof(d));
}

void checkpoint::pack_data(CheckpointFile& f, const size_t d)
{
    f.write_data(reinterpret_cast<const char*>(&d), sizeof(d));
}

void checkpoint::pack_data(CheckpointFile& f, const float d)
{
    f.write_data(reinterpret_cast<const char*>(&d), sizeof(d));
}

void checkpoint::pack_data(CheckpointFile& f, const double d)
{
    f.write_data(reinterpret_cast<const char*>(&d), sizeof(d));
}

void checkpoint::pack_data(CheckpointFile& f, const char d)
{
    f.write_data(reinterpret_cast<const char*>(&d), sizeof(d));
}

void checkpoint::pack_data(CheckpointFile& f, const std::string& d)
{
    for (size_t i = 0; i < d.size(); ++i) f.write_data(&d[i], SIZE_OF_CHAR);
    char c = '\0';
    f.write_data(&c, SIZE_OF_CHAR);
}

void checkpoint::pack_data(CheckpointFile& f,
                           const std::vector<std::string>& d)
{
    size_t n = d.size();
    pack_data(f, n);
    for (size_t i = 0; i < n; ++i)
    {
        pack_data(f, d[i]);
    }
}

//-----------------------------------------------------------------------------

void checkpoint::unpack_data(int& d, CheckpointFile& f)
{
    f.read_data(reinterpret_cast<char*>(&d), sizeof(d));
}

void checkpoint::unpack_data(size_t& d, CheckpointFile& f)
{
    f.read_data(reinterpret_cast<char*>(&d), sizeof(d));
}

void checkpoint::unpack_data(float& d, CheckpointFile& f)
{
    f.read_data(reinterpret_cast<char*>(&d), sizeof(d));
}

void checkpoint::unpack_data(double& d, CheckpointFile& f)
{
    f.read_data(reinterpret_cast<char*>(&d), sizeof(d));
}

void checkpoint::unpack_data(char& d, CheckpointFile& f)
{
    f.read_data(reinterpret_cast<char*>(&d), sizeof(d));
}

void checkpoint::unpack_data(std::string& d, CheckpointFile& f)
{
    d = "";
    char c = '\0';
    while (true)
    {
        f.read_data(&c, SIZE_OF_CHAR);
        if ('\0' == c) break;
        d += c;
    }
}

void checkpoint::unpack_data(std::vector<std::string>& d, CheckpointFile& f)
{
    size_t n = 0;
    unpack_data(n, f);
    d.resize(n, "");
    for (size_t i = 0; i < n; ++i)
    {
        unpack_data(d[i], f);
    }
}

//-----------------------------------------------------------------------------

void checkpoint::print_end_and_stop()
{
    std::cout << "\n\nend" << std::endl;
    exit(EXIT_SUCCESS);
}

//-----------------------------------------------------------------------------

//  end checkpoint.cpp
