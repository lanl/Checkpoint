#ifndef DERIVEDINT_H_
#define DERIVEDINT_H_

/**
 * @file DerivedInt.h
 * @brief Example of a derived class containing an extra int
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

#include <BaseClass.h>

#include <string>
#include <tuple>
#include <checkpoint.h>

//-----------------------------------------------------------------------------

class DerivedInt : public BaseClass
{
    friend void test_DerivedInt(int&, int&);
    #include <friend_checkpoint.inc>

public:

    DerivedInt();

    explicit DerivedInt(const int i);

    explicit DerivedInt(CheckpointFile& f);

    DerivedInt(const DerivedInt& o);

    bool operator==(const DerivedInt& o) const;

    std::string to_string() const override;

    ~DerivedInt() noexcept = default;

    void pack(CheckpointFile& f) const override;

private:

    int i_;

    std::tuple<char*, int*> _t_;

    /// Point tuple to members (called by every constructor)
    void init_t_() override;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of DerivedInt to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o DerivedInt object
 * @return Reference to output stream
 */
std::ostream& operator<<(std::ostream& ost, const DerivedInt& o);

//-----------------------------------------------------------------------------

#endif  // DERIVEDINT_H_
