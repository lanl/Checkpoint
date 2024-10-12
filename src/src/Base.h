#ifndef BASE_H_
#define BASE_H_

/**
 * @file Base.h
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

#include <tuple>
#include <checkpoint.h>

//-----------------------------------------------------------------------------

class Base
{
    friend void test_Base(int&, int&);
    #include <friend_checkpoint.inc>

public:

    Base();

    Base(const int i);
    
    bool operator==(const Base& b) const;

    virtual std::string to_string() const;

    virtual ~Base() noexcept = default;

protected:

    int i_;

    std::tuple<int*> _t_;

    /// Point tuple to members (called by every constructor)
    void init_t_();
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Base to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Base object
 * @return Reference to output stream
 */
std::ostream& operator<<(std::ostream& ost, const Base& o);

//-----------------------------------------------------------------------------

#endif  // BASE_H_
