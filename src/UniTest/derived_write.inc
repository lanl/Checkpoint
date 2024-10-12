/*=============================================================================
 
derived_write.inc

#included in test_checkpoint.inc

Peter Hakel
Los Alamos National Laboratory
WRS-SNA group

Created on 12 August 2023
Last modified on 27 July 2024

=============================================================================*/

checkpoint::verbose = false;
std::vector<BaseClass*> dw;
dw.emplace_back(new DerivedInt{18});
dw.emplace_back(new DerivedString{"test_str"});

std::tuple<std::vector<BaseClass*>*> tw;
std::get<0>(tw) = &dw;

{
    CheckpointFile fw(checkpoint::name, MAXBYTES, 0, 'w');
    checkpoint::write(fw, tw);
}

//  end derived_write.inc
