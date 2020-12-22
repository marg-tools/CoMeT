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

#include <sstream>
#include <cstdlib>
using std::ostringstream;
#if defined (TARGET_LINUX)
# include <unistd.h>
# include <sys/types.h>
#elif defined(TARGET_MAC)
# include <unistd.h>
#endif //TARGET_LINUX

/*
 * This application prints its memory map to stdout
 */

int main()
{
    ostringstream os;

#if defined(TARGET_LINUX)
    os << "/bin/cat /proc/" << getpid() << "/maps";
#elif defined(TARGET_MAC)
    os << "/usr/bin/vmmap " << getpid();
#endif
    system(os.str().c_str());

    return 0;
}

