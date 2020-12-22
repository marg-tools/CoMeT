/*
 * Copyright 2002-2019 Intel Corporation.
 * 
 * This software and the related documents are Intel copyrighted materials, and your
 * use of them is governed by the express license under which they were provided to
 * you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related
 * documents without Intel's prior written permission.
 * 
 * This software and the related documents are provided as is, with no express or
 * implied warranties, other than those that are expressly stated in the License.
 */

// <COMPONENT>: os-apis
// <FILE-TYPE>: component public header

/*!
 * @defgroup OS_APIS_PROCESS Process
 * @brief Contains process-related os apis
 */

#ifndef OS_APIS_PROCESS_CORE_H
#define OS_APIS_PROCESS_CORE_H


/*! @ingroup OS_APIS_PROCESS
 * Retrieves the process ID of the current process.
 *
 * @param[out] pid          Process descriptor
 *
 * @return      Operation status code.
 * @retval      OS_RETURN_CODE_NO_ERROR             If the operation succeeded
 * @retval      OS_RETURN_CODE_PROCESS_QUERY_FAILED If the operation Failed
 *
 * @par Availability:
 *   @b O/S:   Windows, Linux & macOS*\n
 *   @b CPU:   All\n
 */
OS_RETURN_CODE OS_GetPid(NATIVE_PID* pid);

#endif // file guard
