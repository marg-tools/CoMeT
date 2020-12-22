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

//
//  This tool tests the functionality of PIN_DisableSmcSupport
//

#include <cstdio>
#include "pin.H"


/* ================================================================== */
/* Global Variables                                                   */
/* ================================================================== */

/* ===================================================================== */
/* Commandline Switches */
/* ===================================================================== */

/* ================================================================== */



/* ================================================================== */
/*
 Initialize and begin program execution under the control of Pin
*/
int main(INT32 argc, CHAR **argv)
{
    if (PIN_Init(argc, argv) ) return 1;

    PIN_SetSmcSupport(SMC_DISABLE);

    PIN_StartProgram();  // Never returns

    return 0;
}
