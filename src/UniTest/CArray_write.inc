/*=============================================================================
 
CArray_write.inc

#included in test_checkpoint.cpp

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 23 April 2023
Last modified on 27 July 2024

=============================================================================*/

checkpoint::verbose = false;
using U = int;
using T = CArray<U>;
std::string scope = "3";

#include <CArray.inc>
std::tuple<T*> tw;
std::get<0>(tw) = &a;

{
    CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
    checkpoint::write(fw, tw);
}

//  end CArray_write.inc
