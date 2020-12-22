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

#ifndef DEBUGGER_PROTOCOL_EVENT_WINDOWS_HPP
#define DEBUGGER_PROTOCOL_EVENT_WINDOWS_HPP



namespace DEBUGGER_PROTOCOL {

/*!
 * In the future, new fields may be added to the end of the EVENT_INFO_WINDOWS32
 * or EVENT_INFO_WINDOWS64 structures.  If this happens, clients can use the
 * \e _version field to retain backward compatibility.
 *
 * When a client writes information to these structures, it should set \e _version
 * to the latest version that it supports.
 *
 * When a client reads these structures, it should use \e _version to tell which
 * fields are valid.  A client should allow that \e _version may be greater than
 * the newest version it knows about, which happens if an older front-end runs
 * with a newer back-end or vice-versa.
 */
enum EVENT_INFO_WINDOWS_VERSION
{
    EVENT_INFO_WINDOWS_VERSION_0    ///< This is the only defined version currently.
};


static const unsigned MAX_EXCEPTION_PARAMETERS = 15;    ///< Maximum number of exception parameters.

/*!
 * This has the same layout as EXCEPTION_RECORD32.  If you are compiling on Windows,
 * you can safely cast to that type.
 */
struct /*<POD>*/ EXCEPTION32
{
    UINT32 _exceptionCode;
    UINT32 _exceptionFlags;
    UINT32 _exceptionRecord;
    UINT32 _exceptionAddress;
    UINT32 _numberParameters;
    UINT32 _exceptionInformation[MAX_EXCEPTION_PARAMETERS];
};

/*!
 * This has the same layout as EXCEPTION_RECORD64.  If you are compiling on Windows,
 * you can safely cast to that type.
 */
struct /*<POD>*/ EXCEPTION64
{
    UINT32 _exceptionCode;
    UINT32 _exceptionFlags;
    UINT64 _exceptionRecord;
    UINT64 _exceptionAddress;
    UINT32 _numberParameters;
    UINT32 _pad;
    UINT64 _exceptionInformation[MAX_EXCEPTION_PARAMETERS];
};


/*!
 * Information about an exception received on a 32-bit Windows target.
 */
struct /*<POD>*/ EVENT_INFO_WINDOWS32
{
    EVENT_INFO_WINDOWS_VERSION _version;    ///< Tells which fields in this structure are valid.
    bool _firstChance;                      ///< TRUE if this is a first-chance exception.
    EXCEPTION32 _exception;                 ///< Windows exception record.
};

/*!
 * Information about an exception received on a 64-bit Windows target.
 */
struct /*<POD>*/ EVENT_INFO_WINDOWS64
{
    EVENT_INFO_WINDOWS_VERSION _version;    ///< Tells which fields in this structure are valid.
    bool _firstChance;                      ///< TRUE if this is a first-chance exception.
    EXCEPTION64 _exception;                 ///< Windows exception record.
};

} // namespace
#endif // file guard
