/**
 * @file DerivedString.cpp
 * @brief Example of a derived class containing an extra string
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

#include <DerivedString.h>

#include <iomanip>
#include <sstream>

//-----------------------------------------------------------------------------

DerivedString::DerivedString(): s_{""}, _t_{}
{
    d_ = 's';
    init_t_();
}

//-----------------------------------------------------------------------------

DerivedString::DerivedString(const std::string& s): s_{s}, _t_{}
{
    d_ = 's';
    init_t_();
}

//-----------------------------------------------------------------------------

DerivedString::DerivedString(CheckpointFile& f): s_{""}, _t_{}
{
    d_ = 's';
    init_t_();
    checkpoint::unpack_tuple(_t_, f);
}

//-----------------------------------------------------------------------------

void DerivedString::init_t_()
{
    std::get<0>(_t_) = &d_;
    std::get<1>(_t_) = &s_;
}

//-----------------------------------------------------------------------------

bool DerivedString::operator==(const DerivedString& o) const
{
    return s_ == o.s_;
}

//-----------------------------------------------------------------------------

std::string DerivedString::to_string() const
{
    return s_;
}

//-----------------------------------------------------------------------------

void DerivedString::pack(CheckpointFile& f) const
{
    checkpoint::pack_tuple(f, _t_);
}

//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& ost, const DerivedString& o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end DerivedString.cpp
