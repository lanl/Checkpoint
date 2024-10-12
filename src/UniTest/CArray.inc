/*=============================================================================
 
CArray.inc

#included in test_CArray.cpp, CArray_write.inc

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 23 April 2023
Last modified on 13 May 2023

=============================================================================*/

size_t n = 2;
int* v = (int*)malloc(n * sizeof(int));
v[0] = 5;
v[1] = 7;
CArray<int> a{n, v};

//  end CArray.inc
