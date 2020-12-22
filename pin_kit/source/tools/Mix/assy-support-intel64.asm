; Copyright 2002-2019 Intel Corporation.
; 
; This software is provided to you as Sample Source Code as defined in the accompanying
; End User License Agreement for the Intel(R) Software Development Products ("Agreement")
; section 1.L.
; 
; This software and the related documents are provided as is, with no express or implied
; warranties, other than those that are expressly stated in the License.


	.CODE
	ALIGN 4
	mix_fp_save PROC
	fxsave  BYTE PTR [rcx]
	emms
	ret 
	mix_fp_save ENDP

	.CODE
	ALIGN 4
	mix_fp_restore PROC
	fxrstor  BYTE PTR [rcx]
	ret 
	mix_fp_restore ENDP

	END
