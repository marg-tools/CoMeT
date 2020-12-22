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

// <COMPONENT>: atomic
// <FILE-TYPE>: component public header

#ifndef ATOMIC_NULLSTATS_HPP
#define ATOMIC_NULLSTATS_HPP



namespace ATOMIC {


/*! @brief  Model for a statistics-gathering object.
 *
 * A dummy type to use when you don't want to keep track of statistics on atomic operations.
 * To actually gather statistics, implement your own class with the same methods.
 */
class /*<UTILITY>*/ NULLSTATS
{
  public:
    /*!
     * This is called at the end of each compare-and-swap loop, and whenever the
     * EXPONENTIAL_BACKOFF object's Reset() method is called.
     *
     *  @param[in] iterations   The number of failed CAS iterations, each requiring an
     *                           exponential backoff delay.
     */
    void Backoff(UINT32 iterations) {}
};

} // namespace
#endif // file guard
