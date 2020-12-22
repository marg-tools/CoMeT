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
 * @defgroup OS_APIS_TIME Time
 * @brief Contains time related os apis
 */

#ifndef OS_APIS_TIME_H
#define OS_APIS_TIME_H

/*! @ingroup OS_APIS_TIME
 * Retrieves current time in 1us ticks since 1970.
 *
 * @param[out] CurrentTime               Current time
 *
 * @retval      OS_RETURN_CODE_NO_ERROR              If the operation succeeded
 * @retval      OS_RETURN_CODE_TIME_QUERY_FAILED     If the operation failed
 * @return      Operation status code.
 *
 * @par Availability:
 *   @b O/S:   Windows, Linux & macOS*\n
 *   @b CPU:   All\n
 */
OS_RETURN_CODE OS_Time(UINT64* CurrentTime);

/*! @ingroup OS_APIS_TIME
 * Retrieves a string containing the default timezone for the current host.
 *
 * @param[out] tzname                    Points to a buffer that will be filled with the timezone string.
 * @param[in]  buflen                    Size in bytes of the buffer provided for the 'tzname' argument.
 *
 * @retval      OS_RETURN_CODE_NO_ERROR              If the operation succeeded
 * @retval      OS_RETURN_CODE_TIME_QUERY_FAILED     If the operation failed
 * @return      Operation status code.
 *
 * @par Availability:
 *   @b O/S:   Windows, Linux & macOS*\n
 *   @b CPU:   All\n
 */
OS_RETURN_CODE OS_GetDefaultTimeZone(CHAR* tzname, USIZE buflen);

#endif // file guard
