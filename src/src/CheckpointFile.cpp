/**
 * @file CheckpointFile.cpp
 * @brief Checkpoint-restart file class
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

#include <CheckpointFile.h>

#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

//-----------------------------------------------------------------------------

CheckpointFile::CheckpointFile(const std::string& fname, const size_t maxbytes,
                               const size_t myrank, const char mode):
    fname_{fname + int2string(myrank)}, maxbytes_{maxbytes}, myrank_{0},
    mode_{mode}, ostr_{}, istr_{}, cursor_{0}, fsize_{}, findex_{0}
{
    if ('w' == mode_)
    {
        ostr_.open((fname_ + "_0.dat").c_str(), std::ios::binary);
        fsize_.push_back(0);
    }
    else if ('r' == mode_)
    {
        istr_.open((fname_ + "_0.dat").c_str(), std::ios::binary);
        std::ifstream fstr((fname_ + ".txt").c_str());
        size_t n = 0;
        fstr >> maxbytes_;
        fstr >> n;
        fsize_.resize(n);
        for (size_t i = 0; i < n; ++i) fstr >> fsize_[i];
        fstr.close();
        fstr.clear();
    }
    else
    {
        std::cerr << "CheckpointFile unknown mode: " << mode_ << std::endl;
        exit(EXIT_FAILURE);
    }
}

//-----------------------------------------------------------------------------

CheckpointFile::~CheckpointFile()
{
    if ('w' == mode_)
    {
        ostr_.close();
        ostr_.clear();
        std::ofstream fstr((fname_ + ".txt").c_str());
        size_t n = fsize_.size();
        fstr << maxbytes_ << '\n' << n << '\n';
        for (size_t i = 0; i < n; ++i) fstr << fsize_[i] << '\n';
        fstr.close();
        fstr.clear();
    }
    else // 'r' == mode_
    {
        istr_.close();
        istr_.clear();
    }
}

//-----------------------------------------------------------------------------

void CheckpointFile::write_data(const char* buffer, const size_t nbytes)
{
    std::streamsize nb = static_cast<std::streamsize>(nbytes);
    if (fsize_[findex_] + nbytes  <=  maxbytes_)
    {
        ostr_.write(buffer, nb);
        fsize_[findex_] += nbytes;
    }
    else
    {
        ostr_.close();
        ostr_.clear();
        ++findex_;
        ostr_.open((fname_ + int2string(findex_) + ".dat").c_str(),
                   std::ios::binary);
        ostr_.write(buffer, nb);
        fsize_.push_back(nbytes);
    }
}

//-----------------------------------------------------------------------------

void CheckpointFile::read_data(char* buffer, const size_t nbytes)
{
    std::streamsize nb = static_cast<std::streamsize>(nbytes);
    if (cursor_ + nbytes  <=  fsize_[findex_])
    {
        istr_.read(buffer, nb);
        cursor_ += nbytes;
    }
    else
    {
        istr_.close();
        istr_.clear();
        ++findex_;
        istr_.open((fname_ + int2string(findex_) + ".dat").c_str(),
                   std::ios::binary);
        istr_.read(buffer, nb);
        cursor_ = nbytes;
    }
}

//-----------------------------------------------------------------------------

char CheckpointFile::peek()
{
    if (cursor_ + sizeof(char)  <=  fsize_[findex_])
    {
        return static_cast<char>(istr_.peek());
    }
    else
    {
        std::ifstream istr;
        istr.open((fname_ + int2string(findex_+1) + ".dat").c_str(),
                   std::ios::binary);
        char c = static_cast<char>(istr.peek());
        istr.close();
        istr.clear();
        return c;
    }
}

//-----------------------------------------------------------------------------

int CheckpointFile::ndigits(const size_t i)
{
    const int INT_WIDTH = 11;
    size_t k = 10;
    for (int j = 1; j <= INT_WIDTH; ++j)
    {
        if (i < k) return j;
        k *= 10;
    }
    return 0;
}

//-----------------------------------------------------------------------------

std::string CheckpointFile::int2string(const size_t i)
{
    std::ostringstream convert;
    convert.str("");
    convert << "_" << std::right << std::setw(ndigits(i)) << i;
    return convert.str();
}

//-----------------------------------------------------------------------------

//  end CheckpointFile.cpp
