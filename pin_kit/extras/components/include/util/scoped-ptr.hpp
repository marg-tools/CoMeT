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

#ifndef UTIL_SCOPED_PTR_HPP
#define UTIL_SCOPED_PTR_HPP

#include <assert.h>


namespace UTIL {


/*!
 * A simple smart pointer, inspired by boost::scoped_ptr.  Pointers managed by
 * SCOPED_PTR cannot be shared, and there is no reference counting overhead.  A
 * scoped pointer is simply deleted at the end of the enclosing scope.  Since
 * these pointers can't be shared, SCOPED_PTR disallows assignment from one
 * SCOPED_PTR to another.
 */
template<typename T> class /*<UTILITY>*/ SCOPED_PTR
{
public:
    /*!
     * Create a smart pointer wrapper for \a p.
     *
     *  @param[in] p     A pointer from "new", or NULL.
     */
    explicit SCOPED_PTR(T *p = 0) : _ptr(p) {}

    /*!
     * The destructor automatically calls delete on the pointer.
     */
    ~SCOPED_PTR()
    {
        delete _ptr;    // Note, delete of NULL is defined to do nothing.
    }

    /*!
     * Deletes the underlying pointer, then assigns a new pointer.
     *
     *  @param[in] p    A pointer from "new", or NULL.
     */
    void Reset(T *p = 0)
    {
        delete _ptr;
        _ptr = p;
    }

    /*!
     * @return A reference to the underlying pointer, which must not be NULL.
     */
    T & operator*() const
    {
        assert(_ptr != 0);
        return *_ptr;
    }

    /*!
     * @return The underlying pointer, which must not be NULL.
     */
    T * operator->() const
    {
        assert(_ptr != 0);
        return _ptr;
    }

    /*!
     * @return The underlying pointer.
     */
    T * Get() const
    {
        return _ptr;
    }

    /*!
     * Exchange the contents of two smart pointers.
     *
     *  @param[in] other    The other pointer that is exchanged.
     */
    void Swap(SCOPED_PTR &other)
    {
        T *t = other._ptr;
        other._ptr = _ptr;
        _ptr = t;
    }

    /*!
     * Conversion to bool.
     *
     * @return  TRUE if the underlying pointer is not NULL.
     */
    operator bool () const
    {
        return (_ptr != 0);
    }

    /*!
     * @return  TRUE if the underlying pointer is NULL.
     */
    bool operator! () const
    {
        return (_ptr == 0);
    }

private:
    T *_ptr;

    SCOPED_PTR(SCOPED_PTR const &);
    SCOPED_PTR & operator=(SCOPED_PTR const &);
};

} // namespace
#endif // file guard
