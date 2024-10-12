/*=============================================================================
 
derived_read.inc

#included in test_checkpoint.inc

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 12 August 2023
Last modified on 27 July 2024

=============================================================================*/

std::vector<BaseClass*> dr;

std::tuple<std::vector<BaseClass*>*> tr;
std::get<0>(tr) = &dr;

CheckpointFile fr(checkpoint::name, MAXBYTES, 0, 'r');
checkpoint::read(tr, fr);

//  end derived_read.inc
