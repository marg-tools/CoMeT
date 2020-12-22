; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.

include asm_macros.inc

PROLOGUE

.data

extern funcPtr:ADDRINT_TYPE

.code

; void ClFlushFunc();
; This function calls clflush
ClFlushFunc PROC

    mov       GCX_REG ,funcPtr
    ;clflush (GCX_REG)
    db 00Fh, 0AEh, 039h

    ret
ClFlushFunc ENDP

; void ClFlushOptFunc();
; This function calls clflushopt
ClFlushOptFunc PROC

    mov       GCX_REG ,funcPtr
    ;clflushopt (GCX_REG)
    db 066h, 00Fh, 0AEh, 039h

    ret
ClFlushOptFunc ENDP

; void ClwbFunc();
; This function calls clwb
ClwbFunc PROC

    mov       GCX_REG ,funcPtr
    ;clwb (GCX_REG)
    db 066h, 00Fh, 0AEh, 031h

    ret
ClwbFunc ENDP

end
