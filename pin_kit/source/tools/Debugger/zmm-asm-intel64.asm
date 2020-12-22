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

.code

loadYmm0 PROC
    ; This is "VMOVDQU ymm0, YMMWORD PTR [rdi]".  We directly specify the machine code,
    ; so this test runs even when the compiler doesn't support AVX.
    db 0C5h, 0FEh, 06Fh, 007h

    ret
loadYmm0 ENDP

loadZmm0 PROC
    ; This is "VMOVUPD zmm0, ZMMWORD PTR [rdi]".  We directly specify the machine code,
    ; so this test runs even when the compiler doesn't support AVX512.
    db 062h, 0F1h, 0FDh, 048h, 010h, 007h

    ret
loadZmm0 ENDP

loadK0 PROC
    ; This is "KMOVW k0, WORD PTR [rdi]".  We directly specify the machine code,
    ; so this test runs even when the compiler doesn't support AVX512.
    db 0C5h, 0F8h, 090h, 007h

    ret
loadK0 ENDP

end
