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

// <COMPONENT>: util
// <FILE-TYPE>: component public header

#ifndef UTIL_RANGE_HPP
#define UTIL_RANGE_HPP

#include "util/round.hpp"


namespace UTIL {

/*!
 * Utility that holds and manipulates an address range.
 */
template<typename ADDRTYPE> class /*<UTILITY>*/ RANGE
{
public:
    RANGE() : _base(0), _size(0) {}     ///< Create an empty address range.

    /*!
     * Create an address range.
     *
     *  @param[in] base     Start of the range.
     *  @param[in] size     Size (bytes) of the range.
     */
    RANGE(ADDRTYPE base, size_t size) : _base(base), _size(size) {}

    /*!
     * Create an address range.
     *
     *  @param[in] base     Start of the range.
     *  @param[in] size     Size (bytes) of the range.
     */
    RANGE(void *base, size_t size) : _base(reinterpret_cast<PTRINT>(base)), _size(size) {}

    /*!
     * Assigns a new value to the range.
     *
     *  @param[in] base     Start of the range.
     *  @param[in] size     Size (bytes) of the range.
     */
    void Assign(ADDRTYPE base, size_t size)
    {
        _base = base;
        _size = size;
    }

    /*!
     * Assigns a new value to the range.
     *
     *  @param[in] base     Start of the range.
     *  @param[in] size     Size (bytes) of the range.
     */
    void Assign(void *base, size_t size)
    {
        _base = reinterpret_cast<PTRINT>(base);
        _size = size;
    }

    ADDRTYPE GetBase() const    { return _base; }           ///< @return Start of the range.
    size_t GetSize() const      { return _size; }           ///< @return Size of the range.
    ADDRTYPE GetEnd() const     { return _base + _size; }   ///< @return Address 1 byte beyond range end.
    void Clear()                { _base = 0;  _size = 0; }  ///< Makes the range empty.

    /*!
     * Aligns the starting and ending addresses of the range.  Afterwards, the
     * original range is contained by the new one, and the start and end are aligned.
     *
     *  @param[in] alignment    Desired alignement (bytes).
     */
    void AlignEndpoints(size_t alignment)
    {
        ADDRTYPE end = RoundUp(GetEnd(), alignment);
        _base = RoundDown(_base, alignment);
        _size = end - _base;
    }

    /*!
     * Tells if the range contains an address.
     *
     *  @param[in] addr     Address to test.
     *
     * @return  TRUE if range contains the address.
     */
    bool Contains(ADDRTYPE addr) const
    {
        return ((addr - _base) < _size);
    }

    /*!
     * Tells if the range contains all addresses in another range.
     *
     *  @param[in] range    Range to test.
     *
     * @return  TRUE if range contains \a range.
     */
    bool Contains(const RANGE &range) const
    {
        return (Contains(range.m_base) && !range.Contains(GetEnd()));
    }

private:
    ADDRTYPE _base;
    size_t _size;
};

typedef RANGE<ADDRINT> ARANGE;    ///< A range of target addresses.
typedef RANGE<ANYADDR> ANYRANGE;  ///< A range of ANYADDR's.
typedef RANGE<PTRINT> PRANGE;     ///< A range of host addresses.

} // namespace
#endif // file guard
