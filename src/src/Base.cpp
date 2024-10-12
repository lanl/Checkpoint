/**
 * @file Base.cpp
 * @brief Example of a base class
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

#include <Base.h>

#include <iomanip>
#include <sstream>

//-----------------------------------------------------------------------------

Base::Base(): i_{0}, _t_{} {init_t_();}

//-----------------------------------------------------------------------------

Base::Base(const int i): i_{i}, _t_{} {init_t_();}

//-----------------------------------------------------------------------------

void Base::init_t_()
{
    std::get<0>(_t_) = &i_;
}

//-----------------------------------------------------------------------------

bool Base::operator==(const Base& d) const
{
    return i_ == d.i_;
}

//-----------------------------------------------------------------------------

std::string Base::to_string() const
{
    std::ostringstream convert;
    convert.str("");
    convert << std::right << std::setw(11) << std::setfill(' ') << i_;
    return convert.str();
}

//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& ost, const Base& o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end Base.cpp
