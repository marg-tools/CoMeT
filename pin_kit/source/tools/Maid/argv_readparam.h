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

#ifndef _ARGV_READPARAM_H_
#define _ARGV_READPARAM_H_

int argv_hasFlag(int argc, char *argv[], char param);
int argv_hasLongFlag(int argc, char *argv[], char *param);
int argv_getInt(int argc, char *argv[], char *param, int *ret);
int argv_getLong(int argc, char** argv, char *param, long *ret);
char *argv_getString(int argc, char * argv[], char const * param, char **mem);

#endif
