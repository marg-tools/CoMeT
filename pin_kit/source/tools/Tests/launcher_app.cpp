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
 * runpin_app.cpp
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

bool check_var_value(const char* var, const char * value) {
    std::string var_str(getenv(var));
    if (var_str == value) {
        return true;
    }
    return false;
}

int main(int argc, char *argv[]) {
#if defined(TARGET_LINUX)
    // Extract the kernel version
    // 
    FILE* pipe = popen("uname -r", "r");
    if (!pipe) 
    {
        std::cerr << "Failed to get kernel version!" << std::endl;
        exit(1);
    }

    char buffer[128];
    std::string kernel_ver = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            kernel_ver += buffer;
    }
    pclose(pipe);

    if (!(std::string(getenv("LD_LIBRARY_PATH")).find("/usr/lib") != std::string::npos))
    {
        std::cout << "Failed in application, while testing LD_LIBRARY_PATH!" << std::endl;
        exit(1);
    }

    if (!(std::string(getenv("LD_ASSUME_KERNEL")).substr(0, 10) == kernel_ver.substr(0, 10)))
    {
        std::cout << "Failed in application, while testing LD_ASSUME_KERNEL!" << std::endl;
        exit(1);
    }

    if (!check_var_value("LD_BIND_NOW", "1"))
    {
        std::cout << "Failed in application, while testing LD_BIND_NOW!" << std::endl;
        exit(1);
    }
    
    if (!check_var_value("LD_PRELOAD", "libm.so")) 
    {
        std::cout << "Failed in application, while testing LD_PRELOAD!" << std::endl;
        exit(1);
    }
#elif defined(TARGET_MAC)
    if (!(std::string(getenv("DYLD_LIBRARY_PATH")).find("/usr/lib") != std::string::npos)) {
        std::cout << "Failed in application!" << std::endl;
        exit(1);
    }
#endif
    std::cout << "Application got env vars successfully!" << std::endl;
    return 0;
}
