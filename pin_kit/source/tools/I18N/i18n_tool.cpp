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

#include <iostream>
#include <fstream>
#include <string>
#include "pin.H"
using std::string;
using std::endl;


/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

KNOB<string> KnobUnicodeExeName(KNOB_MODE_WRITEONCE, "pintool",
    "uni_param", "Default-Name.exe", "unicode param");


/* ===================================================================== */
/* Global Variables and Definitions */
/* ===================================================================== */

std::ofstream outfile;

#if defined(TARGET_WINDOWS)
#define MAINNAME "wmain"
#elif defined(TARGET_LINUX) || defined(TARGET_BSD)
#define MAINNAME "main"
#endif
/* ===================================================================== */

VOID ImageLoad(IMG img, VOID * v)
{
    // Looking for main symbol only in main image
    IMG_TYPE imgType = IMG_Type(img);
    if(imgType ==  IMG_TYPE_STATIC || imgType == IMG_TYPE_SHARED)
    {
        string imagePath = IMG_Name(img);
        string::size_type index1 = imagePath.find("prefix_");
        if(index1 != string::npos)
        {
            string image =  imagePath.substr(index1);
            outfile << "Image: " << image << endl;
        }

        for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec))
        {
            for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn))
            {
                if (RTN_Name(rtn) == MAINNAME)
                {
                    string  filePath;
                    PIN_GetSourceLocation(RTN_Address(rtn), NULL, NULL, &filePath);

                    if (filePath != "")
                    {
                        string::size_type index = filePath.find("prefix_");
                        if(index != string::npos)
                        {
                            string file =  filePath.substr(index);
                            outfile << "File: " << file << endl;
                        }
                    }
                }
            }
        }
    }
}

VOID Fini(INT32 code, VOID *)
{
    outfile.close();
}

int main(INT32 argc, CHAR **argv)
{
    PIN_InitSymbols();
    PIN_Init(argc, argv);

    outfile.open("i18n_tool.out");
    
    IMG img = IMG_Open(KnobUnicodeExeName.Value());
    if (IMG_Valid(img) == TRUE)
    {
    	string exeFullName = KnobUnicodeExeName.Value();
    	
        outfile << exeFullName.substr(exeFullName.rfind("/")+1) << endl;
        IMG_Close(img);     
    }  
     
    IMG_AddInstrumentFunction(ImageLoad, 0);
    PIN_AddFiniFunction(Fini, 0);

    // Never returns
    PIN_StartProgram();

    return 0;
}
