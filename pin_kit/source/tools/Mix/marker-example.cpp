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
using std::cout;
using std::endl;
extern "C" {
void marker_start_counting()
{
}
void marker_stop_counting()
{
}

void marker_emit_stats()
{
}

void marker_zero_stats()
{
}

} // end of extern "C"

int main(int argc, char** argv)
{

    for (int i=0;i<3;i++)
    {
        marker_zero_stats();
        marker_start_counting();
        cout << "Hello" << endl;
        marker_stop_counting();
        marker_emit_stats();
    }
    marker_zero_stats();
    return 0;
}
