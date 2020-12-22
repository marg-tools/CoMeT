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

// <COMPONENT>: debugger-protocol
// <FILE-TYPE>: component public header

#ifndef DEBUGGER_PROTOCOL_THREAD_LINUX_HPP
#define DEBUGGER_PROTOCOL_THREAD_LINUX_HPP

namespace DEBUGGER_PROTOCOL {


/*!
 * In the future, new fields may be added to the end of the THREAD_INFO_LINUX
 * structure.  If this happens, clients can use the \e _version field to retain
 * backward compatibility.
 *
 * When a client writes information to this structure, it should set \e _version
 * to the latest version that it supports.
 *
 * When a client reads this structure, it should use \e _version to tell which
 * fields are valid.  A client should allow that \e _version may be greater than
 * the newest version it knows about, which happens if an older front-end runs
 * with a newer back-end or vice-versa.
 */
enum THREAD_INFO_LINUX_VERSION
{
    THREAD_INFO_LINUX_VERSION_0     ///< This is the only defined version currently.
};


/*!
 * Information about a thread running on a Linux target.
 */
struct /*<POD>*/ THREAD_INFO_LINUX
{
    THREAD_INFO_LINUX_VERSION _version;     ///< Tells which fields in this structure are valid.

    /* There are no fields defined for this version. */
};

} // namespace
#endif // file guard
