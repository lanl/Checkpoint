#ifndef BASECLASS_H_
#define BASECLASS_H_

/**
 * @file BaseClass.h
 * @brief Another example of a base class
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

#include <tuple>
#include <checkpoint.h>

//-----------------------------------------------------------------------------

class BaseClass
{
public:

    BaseClass(): d_{'\0'} {};

    virtual std::string to_string() const = 0;

    virtual ~BaseClass() noexcept = default;

    virtual void pack(CheckpointFile& f) const = 0;

    static BaseClass* factory(CheckpointFile& f, char d);

protected:

    /// Derived type ID
    char d_;

    /// Point tuple to members (called by every constructor)
    virtual void init_t_() = 0;
};

//-----------------------------------------------------------------------------

#endif  // BASECLASS_H_
