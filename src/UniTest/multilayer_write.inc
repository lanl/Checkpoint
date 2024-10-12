/*=============================================================================
 
multilayer_write.inc

#included in test_checkpoint.inc

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 13 May 2023
Last modified on 27 July 2024

=============================================================================*/

checkpoint::verbose = false;
std::string sw = "mlt";
std::vector<Data> vw{Data{11, "abc"}, Data{13, "xyz"}};
int nw = -35;

std::tuple<std::string*, std::vector<Data>*, int*> tw;
std::get<0>(tw) = &sw;
std::get<1>(tw) = &vw;
std::get<2>(tw) = &nw;

{
    CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
    checkpoint::write(fw, tw);
}

//  end multilayer_write.inc
