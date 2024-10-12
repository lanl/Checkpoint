/*=============================================================================
 
multilayer_read.inc

#included in test_checkpoint.inc

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 13 May 2023
Last modified on 27 July 2024

=============================================================================*/

std::string sr;
std::vector<Data> vr;
int nr;
std::tuple<std::string*, std::vector<Data>*, int*> tr;
std::get<0>(tr) = &sr;
std::get<1>(tr) = &vr;
std::get<2>(tr) = &nr;

CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
checkpoint::read(tr, fr);

checkpoint::reset_defaults();

//  end multilayer_read.inc
