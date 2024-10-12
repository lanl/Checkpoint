#ifndef CHECKPOINT_H_
#define CHECKPOINT_H_

/**
 * @file checkpoint.h
 * @brief Checkpoint-restart
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

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <CheckpointFile.h>
#include <CArray.h>

using Clock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<Clock>;

//-----------------------------------------------------------------------------

/// Checkpoint/restart
struct checkpoint
{
    /// Program's starting time point
    static TimePoint start_time;
    
    /// 1 byte
    static constexpr size_t SIZE_OF_CHAR = sizeof(char);
    
    /// Default maximum checkpoint file size
    static constexpr size_t MAXBYTES_DEFAULT = 2000000000;
    
    /// Print updates
    static bool verbose;
    
    /// Checkpoint base name
    static std::string base_name;

    /// Checkpoint index
    static size_t index;

    /// Path to checkpoint
    static std::string path;
    
    /// Checkpoint name
    static std::string name;
    
    /// Maximum checkpoint file size
    static size_t maxbytes;
    
    /// Flag to stop the program after writing the checkpoint
    static bool stopflag;
    
    /// MPI rank
    static size_t myrank;
    
    /// Time to checkpoint in seconds
    static int trigger_in_seconds;
    
    /// Current time point
    static TimePoint now();
    
    /**
     * @brief Initialize start time and time duration to checkpoint
     * @param[in] name_root Checkpoint root name
     * @param[in] dir Location (directory) of the checkpoint
     * @param[in] trigger Time duration to checkpoint (HH:[MM:[SS]])
     * @param[in] stop_flag Flag to stop the program after writing the checkpoint
     * @param[in] maxsize Maximum checkpoint file size (optional)
     */
    static void init(const std::string& name_root, const std::string& dir,
                     const std::string& trigger, const bool stop_flag,
                     const size_t maxsize = MAXBYTES_DEFAULT);
    
    /// Current runtime in seconds
    static long int runtime_in_seconds();
    
    /// Checkpoint trigger
    static bool trigger();
    
    /// Current local time
    static std::string local_time();
    
    /// Set new checkpoint name
    static void set_name();
    
    /// Reset defaults
    static void reset_defaults();

    /**
     * @brief Conversion of an integer to a formatted string
     * @param[in] i Integer to be converted
     * @param[in] fillchar Character used for (left) padding
     * @param[in] length Number of characters in return value
     * @return String version of i
     */
    template<typename T>
    static std::string int_to_string(const T i, const char fillchar, const int length)
    {
        std::ostringstream convert;
        convert.str("");
        convert << std::right << std::setw(length) << std::setfill(fillchar) << i;
        return convert.str();
    }
    
    /**
     * @brief Data size in bytes
     * @param[in] d Data
     * @return Data size in bytes
     */
    template <typename T>
    static size_t size_of(const T& d)
    {
        return size_of_tuple(d);
    }
    
    template <typename T>
    static typename std::enable_if<std::is_fundamental<T>::value, size_t>::type
    size_of(const T d)
    {
        return sizeof(d);
    }
    
    /**
     * @brief Data size in bytes
     * @param[in] d String data
     * @return Data size in bytes
     */
    static size_t size_of(const std::string& d);
    
    /**
     * @brief Data size in bytes
     * @param[in] d Vector of data
     * @return Data size in bytes
     */
    template <typename T>
    static void size_of(const std::vector<T>& d)
    {
        return d.size() * sizeof(T);
    }
    
    /**
     * @brief Data size in bytes
     * @param[in] d Vector of string data
     * @return Data size in bytes
     */
    static size_t size_of(const std::vector<std::string>& d);
    
    template <typename T>
    static void size_of(const CArray<T>& a)
    {
        return a.n_ * sizeof(T)  +  sizeof(size_t);
    }
    
    //-----------------------------------------------------------------------------
    
    /**
     * @brief Pack data
     * @param[in, out] f CheckpointFile
     * @param[in] d Data
     */
    template <typename T>
    static void pack_data(CheckpointFile& f, const T& d)
    {
        pack_tuple(f, d._t_);
    }
    
    static void pack_data(CheckpointFile& f, const int d);
    
    static void pack_data(CheckpointFile& f, const size_t d);
    
    static void pack_data(CheckpointFile& f, const float d);
    
    static void pack_data(CheckpointFile& f, const double d);
    
    static void pack_data(CheckpointFile& f, const char d);
    
    /**
     * @brief Pack data
     * @param[in, out] f CheckpointFile
     * @param[in] d String data
     */
    static void pack_data(CheckpointFile& f, const std::string& d);
    
    /**
     * @brief Pack data
     * @param[in, out] f CheckpointFile
     * @param[in] d Vector of data
     */
    template <typename T>
    static void pack_data(CheckpointFile& f, const std::vector<T>& d)
    {
        size_t n = d.size();
        pack_data(f, n);
        for (size_t i = 0; i < n; ++i)
        {
            pack_data(f, d[i]);
        }
    }
    
    /**
     * @brief Pack data
     * @param[in, out] f CheckpointFile
     * @param[in] d Vector of string data
     */
    static void pack_data(CheckpointFile& f,
                          const std::vector<std::string>& d);
    
    /**
     * @brief Pack data
     * @param[in, out] f CheckpointFile
     * @param[in] d CArray of data
     */
    template <typename T>
    static void pack_data(CheckpointFile& f, const CArray<T>& a)
    {
        pack_data(f, a.n_);
        for (size_t i = 0; i < a.n_; ++i)
        {
            pack_data(f, a.d_[i]);
        }
    }

    /**
     * @brief Pack data
     * @param[in, out] f CheckpointFile
     * @param[in] d Vector of data pointers
     */
    template <typename T>
    static void pack_data(CheckpointFile& f, const std::vector<T*>& d)
    {
        size_t n = d.size();
        pack_data(f, n);
        for (size_t i = 0; i < n; ++i)
        {
            d[i]->pack(f);
        }
    }
    
    //-----------------------------------------------------------------------------
    
    /**
     * @brief Unpack data
     * @param[out] d Data
     * @param[in, out] f CheckpointFile
     */
    template <typename T>
    static void unpack_data(T& d, CheckpointFile& f)
    {
        unpack_tuple(d._t_, f);
    }
    
    static void unpack_data(int& d, CheckpointFile& f);
    
    static void unpack_data(size_t& d, CheckpointFile& f);
    
    static void unpack_data(float& d, CheckpointFile& f);
    
    static void unpack_data(double& d, CheckpointFile& f);
    
    static void unpack_data(char& d, CheckpointFile& f);
    
    /**
     * @brief Unpack a string
     * @param[out] d Data in a string
     * @param[in, out] f CheckpointFile
     */
    static void unpack_data(std::string& d, CheckpointFile& f);
    
    /**
     * @brief Unpack vector of data
     * @param[out] d Vector of data
     * @param[in, out] f CheckpointFile
     */
    template <typename T>
    static void unpack_data(std::vector<T>& d, CheckpointFile& f)
    {
        size_t n = 0;
        unpack_data(n, f);
        d.resize(n);
        for (size_t i = 0; i < n; ++i)
        {
            unpack_data(d[i], f);
        }
    }
    
    /**
     * @brief Unpack vector of strings
     * @param[out] d Vector of strings
     * @param[in, out] f CheckpointFile
     */
    static void unpack_data(std::vector<std::string>& d, CheckpointFile& f);
    
    /**
     * @brief Unpack CArray of data
     * @param[out] d CArray of data
     * @param[in, out] f CheckpointFile
     */
    
    template <typename T>
    static void unpack_data(CArray<T>& a, CheckpointFile& f)
    {
        size_t n = 0;
        unpack_data(n, f);
        if (a.d_ == nullptr)
        {
            if (n > 0) a.d_ = (T*)malloc(n * sizeof(T));
        }
        else
        {
            if (n == 0)
            {
                free(a.d_);
                a.d_ = nullptr;
            }
            else
            {
                if (a.n_ != n) a.d_ = (T*)realloc(a.d_, n * sizeof(T));
            }
        }
        a.n_ = n;
        for (size_t i = 0; i < n; ++i)
        {
            unpack_data(a.d_[i], f);
        }
    }

    /**
     * @brief Unpack data
     * @param[in, out] f CheckpointFile
     * @param[out] d Vector of data pointers
     */
    template <typename T>
    static void unpack_data(std::vector<T*>& d, CheckpointFile& f)
    {
        size_t n = 0;
        unpack_data(n, f);
        d.resize(n);
        for (size_t i = 0; i < n; ++i)
        {
            char datatype = f.peek();
            d[i] = T::factory(f, datatype);
        }
    }

    //-----------------------------------------------------------------------------
    
    /**
     * @brief Size of a tuple in bytes
     * @param[in] t Tuple of data
     * @return t Size of a tuple in bytes
     */
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I < sizeof...(Ts), int>::type
    size_of_tuple(std::tuple<Ts...> t)
    {
        return size_of(*std::get<I>(t)) + size_of_tuple<I+1>(t);
    }
    
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I == sizeof...(Ts), int>::type
    size_of_tuple(std::tuple<Ts...> t)
    {
        (void)t;
        return 0; // base case (already iterated through all members)
    }
    
    //-----------------------------------------------------------------------------
    
    /**
     * @brief Pack tuple into buffer
     * @param[in, out] f CheckpointFile
     * @param[in] t Tuple of data
     */
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I < sizeof...(Ts)>::type
    pack_tuple(CheckpointFile& f, std::tuple<Ts...> t)
    {
        pack_data(f, *std::get<I>(t));
        pack_tuple<I+1>(f, t);
    }
    
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I == sizeof...(Ts)>::type
    pack_tuple(CheckpointFile& f, std::tuple<Ts...> t) {(void)f;(void)t;}
    
    //-----------------------------------------------------------------------------
    
    /**
     * @brief Unpack tuple from buffer
     * @param[in,out] t Tuple of data
     * @param[in, out] f CheckpointFile
     */
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I < sizeof...(Ts)>::type
    unpack_tuple(std::tuple<Ts...>& t, CheckpointFile& f)
    {
        unpack_data(*std::get<I>(t), f);
        unpack_tuple<I+1>(t, f);
    }
    
    template <size_t I = 0, typename... Ts>
    static typename std::enable_if<I == sizeof...(Ts)>::type
    unpack_tuple(std::tuple<Ts...>& t, CheckpointFile& f) {(void)t;(void)f;}
    
    //-----------------------------------------------------------------------------
    
    /**
     * @brief Write checkpoint at a given scope
     * @param[in, out] f CheckpointFile
     * @param[in] t Data for serialization (std::tuple)
     */
    template <typename... Ts>
    static void write(CheckpointFile& f, const std::tuple<Ts...>& t)
    {
        if (verbose) std::cout << "Writing scope checkpoint ... ";
        pack_tuple(f, t);
        if (verbose) std::cout << "done" << std::endl;
    }
    
    /**
     * @brief Read checkpoint at a given scope
     * @param[out] t Container for deserialized data (std::tuple)
     * @param[in, out] f CheckpointFile
     */
    template <typename... Ts>
    static void read(std::tuple<Ts...>& t, CheckpointFile& f)
    {
        if (verbose) std::cout << "Reading scope checkpoint ... ";
        unpack_tuple(t, f);
        if (verbose) std::cout << "done" << std::endl;
    }
    
    /**
     * @brief Write checkpoint at a given scope
     * @param[in, out] f CheckpointFile
     * @param[in] obj Object for serialization (is not std::tuple;  has ._t_ as std::tuple)
     */
    template <typename T>  // T declaration should "friend" this function
    static void write(CheckpointFile& f, const T& obj)
    {
        write(f, obj._t_);
    }
    
    /**
     * @brief Read checkpoint at a given scope
     * @param[in, out] f CheckpointFile
     * @param[out] obj Object for deserialization (is not std::tuple;  has ._t_ as std::tuple)
     */
    template <typename T>  // T declaration should "friend" this function
    static void read(T& obj, CheckpointFile& f)
    {
        read(obj._t_, f);
    }

//-----------------------------------------------------------------------------

    /// Print 'end' and stop the program
    static void print_end_and_stop();
};

//-----------------------------------------------------------------------------

#endif  // CHECKPOINT_H_
