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

#ifndef ATOMIC_HPP
#define ATOMIC_HPP

/*! @mainpage ATOMIC library
 *
 * The ATOMIC library provides a variety of non-blocking atomic utility routines, such as thread safe queues
 * and associative maps.  These utilities use hardware primitives such as compare-and-swap to maintain
 * atomicity, not locks, which makes them safe even when used in asynchronous interrupt handlers.
 *
 * All utilities have a C++ template interface, somewhat reminiscent of the STL.  As a result, they should
 * be easy to customize for use with your own data structures.
 *
 * Queues:
 *  - @ref ATOMIC::LIFO_CTR             "LIFO_CTR - Last-in-first-out queue"
 *  - @ref ATOMIC::LIFO_PTR             "LIFO_PTR - Last-in-first-out queue"
 *  - @ref ATOMIC::FIXED_LIFO           "FIXED_LIFO - Last-in-first-out queue with pre-allocated elements"
 *
 * Associative maps and sets:
 *  - @ref ATOMIC::FIXED_MULTIMAP       "FIXED_MULTIMAP - Associative map with pre-allocated elements"
 *  - @ref ATOMIC::FIXED_MULTISET       "FIXED_MULTISET - Unordered set of data with pre-allocated elements"
 *
 * Fundamental operations, utilities:
 *  - @ref ATOMIC::OPS                  "OPS - Fundamental atomic operations"
 *  - @ref ATOMIC::EXPONENTIAL_BACKOFF  "EXPONENTIAL_BACKOFF - Helper object for exponential delays"
 *  - @ref ATOMIC::IDSET                "IDSET - Maintains a set of unique IDs"
 *  - @ref ATOMIC::NULLSTATS            "NULLSTATS - Model for a statistics-gathering object"
 *
 * Configuration:
 *  - @ref CONFIG
 */

/*! @brief The ATOMIC library. */
namespace ATOMIC {}

#include "atomic/ops.hpp"
#include "atomic/lifo-ctr.hpp"
#include "atomic/lifo-ptr.hpp"
#include "atomic/fixed-lifo.hpp"
#include "atomic/fixed-multimap.hpp"
#include "atomic/fixed-multiset.hpp"
#include "atomic/idset.hpp"
#include "atomic/exponential-backoff.hpp"

#endif // file guard
