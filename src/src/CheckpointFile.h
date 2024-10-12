#ifndef CHECKPOINTFILE_H_
#define CHECKPOINTFILE_H_

/**
 * @file CheckpointFile.h
 * @brief Checkpoint-restart file class
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

#include <fstream>
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

/// Virtual checkpoint file
class CheckpointFile
{
    friend void test_CheckpointFile(int &, int &);

public:

    /// Constructor
    CheckpointFile(const std::string& fname, const size_t maxbytes,
                   const size_t myrank, const char mode);

    /// Copy constructor
    CheckpointFile(const CheckpointFile&) = delete;

    /// Copy assignment
    CheckpointFile& operator=(const CheckpointFile&) = delete;

    /// Move constructor
    CheckpointFile(CheckpointFile&&) = delete;

    /// Move assignment
    CheckpointFile& operator=(CheckpointFile&&) = delete;

    /// Destructor
    ~CheckpointFile();

    /**
     * @brief Write buffer to this
     * @param[in] buffer Data to be written
     * @param[in] nbytes Size of buffer in bytes
     */
    void write_data(const char* buffer, const size_t nbytes);

    /**
     * @brief Read buffer from this
     * @param[in] buffer Data to be read
     * @param[in] nbytes Size of buffer in bytes
     */
    void read_data(char* buffer, const size_t nbytes);

    /**
     * @brief Inspect next char in this
     * @return Next char in this
     */
    char peek();

    /**
      * @brief Number of digits needed to display an integer
      * @param[in] i Integer to be displayed
      * @return Number of digits needed to display i
      */
    static int ndigits(const size_t i);

    
private:

    /**
      * @brief Conversion of an integer to a formatted string (no padding)
      * @param[in] i Integer to be converted
      * @return String version of i, prepended with underscore
      */
    static std::string int2string(const size_t i);

    /// File name root of this checkpoint
    std::string fname_;

    /// Maximum size of physical files
    size_t maxbytes_;

    /// MPI rank
    size_t myrank_;

    /// 'r' for reading; 'w' for writing
    char mode_;

    /// Output stream for writing
    std::ofstream ostr_;

    /// Input stream for reading
    std::ifstream istr_;

    /// Current location within the stream
    size_t cursor_;

    /// Family-file size
    std::vector<size_t> fsize_;

    /// Index of the currently open family-file
    size_t findex_;
};


//-----------------------------------------------------------------------------

#endif  // CHECKPOINTFILE_H_
