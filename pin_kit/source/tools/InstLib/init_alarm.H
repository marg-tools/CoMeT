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

#ifndef _INIT_ALARM_H_
#define _INIT_ALARM_H_

#include "pin.H"
#include <set>

namespace CONTROLLER{
class CONTROL_MANAGER;

class INIT_ALARM{
public:
    INIT_ALARM() : _manager(NULL), _disabled(FALSE) {}
    VOID Activate(CONTROL_MANAGER* manager);
    VOID Disable() {_disabled = TRUE;}

private:
    CONTROL_MANAGER* _manager;
    ADDRINT _start_thread[PIN_MAX_THREADS];
    std::set<ADDRINT> _thread_first_ip;
    volatile BOOL _disabled;

    static VOID OnTrace(TRACE trace, VOID *vthis);
    static VOID ThreadStart(THREADID tid, CONTEXT *ctxt, INT32 flags, VOID *v);
    static inline ADDRINT ShouldStart(INIT_ALARM* init_alarm, THREADID tid){
        return init_alarm->_start_thread[tid] & !init_alarm->_disabled;
    }
    static VOID Start(CONTEXT *ctxt, ADDRINT ip, THREADID tid, VOID *vthis);
};

} //namespace
#endif
