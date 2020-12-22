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

#ifndef UTIL_SINGLETON_HPP
#define UTIL_SINGLETON_HPP



namespace UTIL {

/*!
 * Template of a singleton class <T> with the following properties:
 *  - The single instance of the class <T> is created during static initialization of the 
 *    module.
 *  - The instance of the class <T> is never destroyed.
 *  _ The instance of the class <T> can be accessed at any time: during static initialization 
 *    or anytime after.
 *  - The class is thread-safe, assuming the module's static initialization is thread-safe 
 *    (normally performed in a single thread).
 *
 *  @param T        type of the singleton's instance. The class <T> should have a default 
 *                  constructor accessible from this tempalte.
 */
template <typename T> class /*<UTILITY>*/ STATIC_SINGLETON
{
public:
    /*!
     * Get the single instance of class <T>.
     */
    static T * GetInstance() 
    {
        if (m_pInstance == 0) 
        {
            m_pInstance = Create();
        }
        return m_pInstance;
    }

private:
    /*!
     * Create an instance of class <T>.
     */
    static T * Create()
    {
        // We use placement new() for two reasons:
        // -  To create a never-destructed instance of <T>. This allows using this instance 
        //    at any time, even during the module's destruction.
        // -  We could use the regular "new" operator here instead, but placement new is advantageous
        //    because some clients limit the amount of memory that can be dynamically allocated at
        //    static initialization time (e.g. clients that replace the "malloc" implementation).
        //    Allocating the data statically like this for a singleton class has no real disadvantage.

        static UINT8 storage[sizeof(T) + ALIGNMENT_OF(T)];
        return new((void *)RoundUp(&(storage[0]), ALIGNMENT_OF(T))) T();
    }

private:
    static T * m_pInstance;
};

/*!
 * Static member of the STATIC_SINGLETON template: pointer to the single instance
 * of the class <T>.
 */
template<typename T> T * STATIC_SINGLETON<T>::m_pInstance = STATIC_SINGLETON<T>::GetInstance();

} // namespace
#endif // file guard
