#ifndef DERIVEDFACTORY_H_
#define DERIVEDFACTORY_H_

/**
 * @file derived\_factory.h
 * @brief Example of a factory of derived data types
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
#include <DerivedString.h>

//-----------------------------------------------------------------------------

BaseClass* BaseClass::factory(CheckpointFile& f, char d)
{
    if (d == 'i') return new DerivedInt(f);
    if (d == 's') return new DerivedString(f);
    return nullptr;
}

//-----------------------------------------------------------------------------

#endif  // DERIVEDFACTORY_H_
