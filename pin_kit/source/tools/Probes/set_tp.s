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


/*
 * void set_tp( ADDRINT )
 */
    .text
    .align 16
    .global set_tp
    .proc set_tp
set_tp:
    .prologue
    .body
    mov r13=r32;;
    br.ret.sptk.many b0;;    
    .endp set_tp


/*
 * ADDRINT get_tp()
 */
    .text
    .align 16
    .global get_tp
    .proc get_tp
get_tp:
    .prologue
    .body
    mov r8=r13;;
    br.ret.sptk.many b0;;    
    .endp get_tp
