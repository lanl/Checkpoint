#ifndef CARRAY_H_
#define CARRAY_H_

/**
 * @file CArray.h
 * @brief Class to encapsulate 1-D C-style array
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

#include <cstdlib>

//-----------------------------------------------------------------------------

/// Wrapper for 1-D C-style arrays
template <typename T>
struct CArray
{
    /// Array size
    size_t n_;
    
    /// 1-D C-style array
    T*& d_;
    
    /**
     * @brief Constructor initializing with a C-style 1-D array
     * @param[in] n Array size
     * @param[in] d Array data
     */
    CArray(const size_t n, T*& d): n_{n}, d_{d} {}

    /**
     * @brief Copy constructor
     * @param[in] a Original object
     */
    CArray(const CArray& a) = delete;

    /**
     * @brief Copy assignment
     * @param[in] a Original object
     */
    CArray& operator=(const CArray& a) = delete;

    /**
     * @brief Move constructor
     * @param[in] a Original object
     */
    CArray(CArray&& a) = delete;

    /**
     * @brief Move assignment
     * @param[in] a Original object
     */
    CArray& operator=(CArray&& a) = delete;

    /// Destructor
    ~CArray() = default;
};

//-----------------------------------------------------------------------------

#endif  // CARRAY_H_
