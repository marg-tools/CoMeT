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

#ifndef _PARSE_CONTROL_H
#define _PARSE_CONTROL_H

#include <map>
#include <iostream>
#include "control_manager.H"
#include "ialarm.H"

namespace CONTROLLER 
{
class CONTROL_CHAIN;

//this class exposes general utility functions
class PARSER
{
public:
    //convert an array of str to array of char    
    static VOID str2hex(const char* in, unsigned char* out, size_t len);
    
    //convert string to UINT32
    static UINT32 StringToUint32(const string& s);
    
    //convert string to UINT64
    static UINT64 StringToUint64(const string& s);
    
    //split string to vector, use sep as the seperator
    static unsigned int SplitArgs(const string sep, 
                                  const string& input, 
                                  vector<string>& output_array);
    
    //parse the tid token - die on fail 
    static UINT32 GetTIDToken(const string& token);
    
    //parse the tid token
    static BOOL ParseTIDToken(const string& token, UINT32* tid);
    
    //parse the bcast token
    static BOOL ParseBcastToken(const string& token, BOOL * bcast);
    
    //parse the count token
    static BOOL ParseCountToken(const string& token, UINT64 *count);

    //parse the global token
    static BOOL ParseGlobalToken(const string& token, BOOL * global_count);
   
    // parse the repeat token
    static BOOL ParseRepeatToken(const string& token);

    //return True whether the token is a config token(repeat, name, waitfor)
    static BOOL ConfigToken(const string& control_str);
    
    //return True if the token is "uniform"
    static BOOL UniformToken(vector<string>& tokens);
    
    //parse the config tokens and set the control chain accordingly
    static VOID ParseConfigTokens(const string& control_str, 
                                 CONTROL_CHAIN* chain);  

    static VOID ParseOldConfigTokens(const string& str, string& value, 
                                     string& count, string& tid, BOOL& repeat);


private:
    
    
}; //class
}; //namespace 


#endif
