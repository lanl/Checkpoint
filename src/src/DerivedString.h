#ifndef DERIVEDSTRING_H_
#define DERIVEDSTRING_H_

/**
 * @file DerivedString.h
 * @brief Example of a derived class containing an extra string
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

class DerivedString : public BaseClass
{
    friend void test_DerivedString(int&, int&);
    #include <friend_checkpoint.inc>

public:

    DerivedString();

    explicit DerivedString(const std::string& i);

    explicit DerivedString(CheckpointFile& f);

    DerivedString(const DerivedString& o);

    bool operator==(const DerivedString& o) const;

    std::string to_string() const override;

    ~DerivedString() noexcept = default;

    void pack(CheckpointFile& f) const override;

private:

    std::string s_;

    std::tuple<char*, std::string*> _t_;

    /// Point tuple to members (called by every constructor)
    void init_t_() override;
};

//-----------------------------------------------------------------------------

/**
 * @brief Send string version of DerivedString to an output stream
 * @param[in,out] ost Output stream
 * @param[in] o DerivedString object
 * @return Reference to output stream
 */
std::ostream& operator<<(std::ostream& ost, const DerivedString& o);

//-----------------------------------------------------------------------------

#endif  // DERIVEDSTRING_H_
