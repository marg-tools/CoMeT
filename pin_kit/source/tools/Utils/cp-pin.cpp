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

#include <stdlib.h>
#include <iostream>
#include <fstream>
using std::endl;
using std::cerr;
using std::ofstream;
using std::ifstream;
using std::ios;

int 
main(int argc, char** argv)
{
    if (argc != 3)
    {
        cerr << "Usage: " 
             << argv[0] << " input-file output-file" << endl;
        exit(1);
    }
    char* ifn = argv[1];
    char* ofn = argv[2];

    ifstream* i = new ifstream(ifn, ios::in|ios::binary);

    if (!i) 
    {
        cerr << "Could not open input file " << ifn << endl;
        exit(1);
    }

    ofstream* o = new ofstream(ofn, ios::out|ios::trunc|ios::binary);
    if (!o)
    {
        cerr << "Could not open output file " << ofn << endl;
        exit(1);
    }
    
    char ch;
    while(i->get(ch))
    {
        *o << ch;
    }
    i->close();
    o->close();
    //cerr << "Exiting..." << endl;
    exit(0);
    //return 0;
}
