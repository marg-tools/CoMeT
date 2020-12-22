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


#include <sstream> 
#include "controller_events.H"

using namespace CONTROLLER;

/// @cond INTERNAL_DOXYGEN
CONTROLLER_EVENTS::CONTROLLER_EVENTS(){
    _events["invalid"] = EVENT_INVALID;
    _events["precond"] = EVENT_PRECOND;
    _events["start"] = EVENT_START;
    _events["stop"] = EVENT_STOP;
    _events["threadid"] = EVENT_THREADID;
    _events["warmup-start"] = EVENT_WARMUP_START;
    _events["warmup-stop"] = EVENT_WARMUP_STOP;
    _events["prolog-start"] = EVENT_PROLOG_START;
    _events["prolog-stop"] = EVENT_PROLOG_STOP;
    _events["epilog-start"] = EVENT_EPILOG_START;
    _events["epilog-stop"] = EVENT_EPILOG_STOP;
    _events["stats-emit"] = EVENT_STATS_EMIT;
    _events["stats-reset"] = EVENT_STATS_RESET;
    //This event emits the stats for the tid who received the event, and resets
    //the stats immediately.
    _events["stats-emit-reset"] = EVENT_STATS_EMIT_RESET;
}

EVENT_TYPE CONTROLLER_EVENTS::AddEvent(const string& event_name){
    map<string,EVENT_TYPE>::iterator iter = _events.find(event_name);
    if (iter != _events.end()){
        ASSERT(FALSE,"event: " + event_name + " already exists");
    }
    
    ASSERT(_events.size() < _max_user_ev, "not enough events");
    EVENT_TYPE ev = static_cast<EVENT_TYPE>(_events.size());
    _events[event_name] = ev;
    return ev;
 
}

string CONTROLLER_EVENTS::IDToString(EVENT_TYPE id){
    map<string,EVENT_TYPE>::iterator iter = _events.begin();
    for (;iter != _events.end(); iter++){
        if (iter->second == id){
            return iter->first;
        }
    }
    
    return "invalid";
    
}

EVENT_TYPE CONTROLLER_EVENTS::EventStringToType(const string& event_name){
    map<string,EVENT_TYPE>::iterator iter = _events.find(event_name);
    if (iter == _events.end()){
        ASSERT(FALSE,"Unsupported event " + event_name);
    }
    return iter->second;
}
 /// @endcond
