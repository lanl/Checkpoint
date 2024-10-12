/**
 * @file DerivedInt.cpp
 * @brief Example of a derived class containing an extra int
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

#include <DerivedInt.h>

#include <iomanip>
#include <sstream>

//-----------------------------------------------------------------------------

DerivedInt::DerivedInt(): i_{0}, _t_{}
{
    d_ = 'i';
    init_t_();
}

//-----------------------------------------------------------------------------

DerivedInt::DerivedInt(const int i): i_{i}, _t_{}
{
    d_ = 'i';
    init_t_();
}

//-----------------------------------------------------------------------------

DerivedInt::DerivedInt(CheckpointFile& f): i_{0}, _t_{}
{
    d_ = 'i';
    init_t_();
    checkpoint::unpack_tuple(_t_, f);
}

//-----------------------------------------------------------------------------

void DerivedInt::init_t_()
{
    std::get<0>(_t_) = &d_;
    std::get<1>(_t_) = &i_;
}

//-----------------------------------------------------------------------------

bool DerivedInt::operator==(const DerivedInt& o) const
{
    return i_ == o.i_;
}

//-----------------------------------------------------------------------------

std::string DerivedInt::to_string() const
{
    std::ostringstream convert;
    convert.str("");
    convert << std::right << std::setw(11) << std::setfill(' ') << i_;
    return convert.str();
}

//-----------------------------------------------------------------------------

void DerivedInt::pack(CheckpointFile& f) const
{
    checkpoint::pack_tuple(f, _t_);
}

//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& ost, const DerivedInt& o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end DerivedInt.cpp
