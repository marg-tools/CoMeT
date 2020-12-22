; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

PUBLIC main_asm


.686
.model flat, c

.code
main_asm PROC
    std
COMMENT    // in the next two insts, the tool analysis functions (in df_test_tool1.cpp, df_test_tool2.cpp and df_test_tool3.cpp)
COMMENT     // , which is called for every inst in this app, may find the DF set if there is a pin bug 
COMMENT    // that does not clear the DF before invoking the non-inlined analysis function, 
COMMENT     // or there is a register allocation bug in the processing of the inlined analysis
    mov eax, 0
    cld
    ret

main_asm ENDP

end