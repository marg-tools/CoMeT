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

#ifndef CREATE_AND_EXIT_THREAD_UTILS_H
#define CREATE_AND_EXIT_THREAD_UTILS_H


enum RETVAL
{
    RETVAL_SUCCESS = 0,
    RETVAL_FAILURE_PIN_INIT_FAILED,
    RETVAL_FAILURE_SEMAPHORE_INIT_FAILED,
    RETVAL_FAILURE_TOOL_MAIN_RETURN,
    RETVAL_FAILURE_TEST_TIMEOUT,
    RETVAL_FAILURE_MAX_TRIALS,
    RETVAL_FAILURE_TOOL_FAILED_TO_SPAWN,
    RETVAL_FAILURE_TOOL_FAILED_TO_EXIT,
    RETVAL_FAILURE_TOO_MANY_THREADS,
    RETVAL_FAILURE_START_AFTER_FINI,
    RETVAL_FAILURE_APP_COMPLETED
};

#endif // CREATE_AND_EXIT_THREAD_UTILS_H
