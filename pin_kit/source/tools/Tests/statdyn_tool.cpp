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

/*
 * This tool checks that Pin reports static and dynamic symbols correctly. The tool assumes two
 * symbols defined in the application: statdyn_app_staticFunction (static symbol) and
 * statdyn_app_dynamicFunction (dynamic symbol). The tool makes sure that these symbols are
 * found and defined correctly.
 */

#include "pin.H"
#include <cassert>
using std::string;

VOID onImageLoad(IMG img, VOID *data)
{
    SYM sym;

    if (IMG_IsMainExecutable(img))
    {
        bool foundStatic = false;
        bool foundDynamic = false;
        for (sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym))
        {
            if (SYM_Name(sym).find("statdyn_app_staticFunction") != string::npos)
            {
                assert(SYM_Dynamic(sym) == false);
                foundStatic = true;
            }
            if (SYM_Name(sym).find("statdyn_app_dynamicFunction") != string::npos)
            {
                assert(SYM_Dynamic(sym) == true);
                foundDynamic = true;
            }
        }
        assert(foundStatic == true);
        assert(foundDynamic == true);
    }
}


int main(int argc, char** argv)
{
    PIN_InitSymbols();
    
    if (!PIN_Init(argc, argv))
    {

        IMG_AddInstrumentFunction(onImageLoad,  0);

        PIN_StartProgram();
    }

    return(1);
}
