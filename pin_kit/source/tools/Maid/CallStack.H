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

#ifndef _CALLSTACK_H_
#define _CALLSTACK_H_

class Activation {
private:
  int _vector_index;             // index into Activations
  ADDRINT _current_sp;
  ADDRINT _target;
  UINT32 _depth;

public:    
  ADDRINT current_sp() const { return _current_sp; }
  int vector_index() const { return _vector_index; }
    
  Activation(int index, ADDRINT current_sp, ADDRINT target):
    _vector_index(index),
    _current_sp(current_sp),
    _target(target)
  { }

  bool operator==( const Activation& a) const {
    return(current_sp() == a.current_sp());
  }
  
  ADDRINT target() {return _target;}
};

class CallStack {
private:
  UINT64 _stackGeneration;
  UINT64 _main_entry_depth;
  UINT64 _enter_opaque_lib_entry;
  vector<Activation> _activations;
  ADDRINT _stackLastPrint;
  const string& (*_Target2RtnName)(ADDRINT);
  const string& (*_Target2LibName)(ADDRINT);
  VOID CreateActivation(ADDRINT current_sp, ADDRINT target);
  VOID AdjustStack(ADDRINT current_sp);

public:

  CallStack(const string& (*t2r)(ADDRINT), const string& (*t2l)(ADDRINT)) :
    _stackGeneration(0),
    _main_entry_depth(~0x0),
    _enter_opaque_lib_entry(0x0),
    _stackLastPrint(~0x0),
    _Target2RtnName(t2r),
    _Target2LibName(t2l)
  {}
  
  UINT64 Depth() {return _activations.size();}
  VOID ProcessCall(ADDRINT current_sp, ADDRINT target);
  VOID ProcessMainEntry(ADDRINT current_sp, ADDRINT target);
  VOID ProcessReturn(ADDRINT current_sp, bool prevIpDoesPush);
  VOID DumpStack(ostream *o);
};

#endif
