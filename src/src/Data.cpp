/**
 * @file Data.cpp
 * @brief Example of a data structure
 * @author Peter Hakel
 * @version 0.0
 * @date Created in 2023\n
 * Last modified on 16 January 2025
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

#include <Data.h>

#include <iomanip>
#include <sstream>

//-----------------------------------------------------------------------------

Data::Data(): i_{0}, s_{""}, _t_{} {init_t_();}

//-----------------------------------------------------------------------------

Data::Data(const int i, const std::string& s): i_{i}, s_{s}, _t_{} {init_t_();}

//-----------------------------------------------------------------------------

Data::Data(const Data& d): i_{d.i_}, s_{d.s_}, _t_{} {init_t_();}

//-----------------------------------------------------------------------------

void Data::init_t_()
{
    std::get<0>(_t_) = &i_;
    std::get<1>(_t_) = &s_;
}

//-----------------------------------------------------------------------------

bool Data::operator==(const Data& d) const
{
    return i_ == d.i_  &&  s_ == d.s_;
}

//-----------------------------------------------------------------------------

std::string Data::to_string() const
{
    std::ostringstream convert;
    convert.str("");
    convert << std::right << std::setw(11) << std::setfill(' ') << i_;
    return convert.str() + s_;
}

//-----------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& ost, const Data& o)
{
    ost << o.to_string();
    return ost;
}

//-----------------------------------------------------------------------------

//  end Data.cpp
