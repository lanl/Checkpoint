/*=============================================================================
 
CArray_read.inc

#included in test_checkpoint.cpp

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 23 April 2023
Last modified on 27 July 2024

=============================================================================*/

U* r = nullptr;
T b{0, r};
std::tuple<T*> tr;
std::get<0>(tr) = &b;

CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
checkpoint::read(tr, fr);

r = b.d_;

//  end CArray_read.inc
