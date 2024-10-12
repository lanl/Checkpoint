#ifndef MDARRAY_H_
#define MDARRAY_H_

/**
 * @file MDArray.h
 * @brief Wrapper class for multi-dimensional arrays
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

#include <iomanip>
#include <numeric>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#include <checkpoint.h>

//-----------------------------------------------------------------------------

using MDIndex = std::vector<size_t>;

template <typename VT>
class MDArray
{
    friend void test_MDArray(int&, int&);
    friend void test_checkpoint(int&, int&);
    #include <friend_checkpoint.inc>

public:

    /**
     * @brief Constructor with default VT initialization
     * @param[in] dim Sizes of individual dimensions
     */
    explicit MDArray(const MDIndex& dim): dim_{}, v_{}, _t_{}
    {
        dim_ = dim;
        v_.resize(static_cast<size_t>(std::accumulate(dim.begin(), dim.end(), 1,
                  std::multiplies<size_t>())));
        init_t_();
    }

    /**
     * @brief Constructor
     * @param[in] dim Sizes of individual dimensions
     * @param[in] v Initialization value
     */
    MDArray(const MDIndex& dim, const VT& v): dim_{dim}, v_{}, _t_{}
    {
        v_.resize(static_cast<size_t>(std::accumulate(dim.begin(), dim.end(), 1,
                  std::multiplies<size_t>())), v);
        init_t_();
    }

    /**
     * @brief Copy constructor
     * @param[in] a Original object
     */
    MDArray(const MDArray& a): dim_{a.dim_}, v_{a.v_}, _t_{}
    {
        init_t_();
    }

    /**
     * @brief Copy assignment
     * @param[in] a Original object
     */
    MDArray& operator=(const MDArray& a)
    {
        if (this != &a)
        {
            dim_ = a.dim_;
            v_ = a.v_;
            init_t_();
        }
        return *this;
    }

    /**
     * @brief Move constructor
     * @param[in] a Original object
     */
    MDArray(MDArray&& a) noexcept: dim_{std::move(a.dim_)}, v_{std::move(a.v_)}, _t_{}
    {
        init_t_();
        std::get<0>(a._t_) = nullptr;
    }

    /**
     * @brief Move assignment
     * @param[in] a Original object
     */
    MDArray& operator=(MDArray&& a) noexcept
    {
        if (this != &a)
        {
            dim_ = std::move(a.dim_);
            v_ = std::move(a.v_);
            init_t_();
            std::get<0>(a._t_) = nullptr;
        }
        return *this;
    }

    /// Destructor
    ~MDArray() = default;

    /**
     * @brief Assign array element
     * @param[in] indx Multi-dimensional index
     * @return Assignable l-value
     */
    VT& operator[](const MDIndex& indx)
    {
        return v_[many_to_one(indx)];
    }

    /**
     * @brief Return array element
     * @param[in] indx Multi-dimensional index
     * @return Returned r-value
     */
    VT operator[](const MDIndex& indx) const
    {
        return v_[many_to_one(indx)];
    }

    /**
     * @brief Sizes of individual dimensions
     * @return Sizes of individual dimensions
     */
    MDIndex dims() const
    {
        return dim_;
    }

private:

    /// Point tuple to members (called by every constructor)
    void init_t_()
    {
        std::get<0>(_t_) = &v_;
    }

    /// Sizes of individual dimensions
    MDIndex dim_;

    /// Underlying 1-D array of data
    std::vector<VT> v_;

    /// Serialization/deserialization
    std::tuple<std::vector<VT>*> _t_;

    /**
     * @brief Conversion of an integer to a formatted string
     * @param[in] i Integer to be converted
     * @param[in] fillchar Character used for (left) padding
     * @param[in] length Number of characters in return value
     * @return String version of i
     */
    template<typename IT>
    static std::string int_to_string(const IT i, const char fillchar,
                                     const int length)
    {
        std::ostringstream convert;
        convert.str("");
        convert << std::right << std::setw(length) << std::setfill(fillchar) << i;
        return convert.str();
    }

    /**
     * @brief Indirect indexing: an array of indices -> a single index
     * @param[in] indx Array of indices
     * @return Single product index, throws an exception for invalid input
     */
    size_t many_to_one(const MDIndex& indx)
    {
        size_t ndim = dim_.size();
        size_t n = indx.size();
        if (n != ndim)
        {
            std::string message = "Error: many_to_one ranges do not conform:\n";
            message += "dimensions = " + int_to_string(ndim, ' ', 10) + "\n";
            message += "indices = " + int_to_string(n, ' ', 10);
            throw std::range_error(message);
        }

        size_t j = indx[0];
        for (size_t i = 1; i < n; ++i)
        {
            if (indx[i] >= dim_[i])
                throw std::out_of_range("out of range exception");

            j = j * dim_[i]  +  indx[i];
        }
        return j;
    }
};

//-----------------------------------------------------------------------------

#endif  // MDARRAY_H_
