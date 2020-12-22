/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software is provided to you as Sample Source Code as defined in the accompanying
 * End User License Agreement for the Intel(R) Software Development Products ("Agreement")
 * section 1.L.
 * 
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 */

#include "pin.H"
#include "footprint.H"
using std::map;
using std::endl;
using std::string;

#if defined(EMX_INIT)
# include "emx-init.H"
#endif

int usage() {
    cerr << "This pin tool computes memory footprints for loads, stores and code references"
         << endl << endl;
    cerr << KNOB_BASE::StringKnobSummary();
    cerr << endl;
    return -1;
}

footprint_t footprint;

int main(int argc, char** argv) {
    if( PIN_Init(argc,argv) )
        return usage();
    PIN_InitSymbols();
    footprint.activate();
#if defined(EMX_INIT)
    emx_init();
#endif
    PIN_StartProgram();    // Never returns
    return 0;
}
