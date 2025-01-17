#ifndef DERIVED_H_
#define DERIVED_H_

/**
 * @file Derived.h
 * @brief Example of a derived class
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

#include <Base.h>

#include <string>
#include <tuple>
#include <checkpoint.h>

//-----------------------------------------------------------------------------

class Derived : public Base
{
    friend void test_Derived(int&, int&);
    #include <friend_checkpoint.inc>

public:

    Derived();

    Derived(const int i, const std::string& s);

    Derived(const Derived& d);
    
    bool operator==(const Derived& d) const;

    std::string to_string() const override;

    ~Derived() noexcept = default;

private:

    std::string s_;

    std::tuple<int*, std::string*> _t_;

    /// Point tuple to members (called by every constructor)
    void init_t_();
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of Derived to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o Derived object
 * @return Reference to output stream
 */
std::ostream& operator<<(std::ostream& ost, const Derived& o);

//-----------------------------------------------------------------------------

#endif  // DERIVED_H_
