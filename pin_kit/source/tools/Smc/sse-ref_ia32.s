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



.text

#ifdef TARGET_MAC
.global _Fld1_a
_Fld1_a:
#else
.global Fld1_a
.type Fld1_a,  @function
Fld1_a:
#endif
    fld1
	fld1
	fld1
    ret


#ifdef TARGET_MAC
.global _Fld1_b
_Fld1_b:
#else
.global Fld1_b
.type Fld1_b,  @function
Fld1_b:
#endif
    fld1
	fld1
	fld1
    ret


#ifdef TARGET_MAC
.global _FldzToTop3_a
_FldzToTop3_a:
#else
.global FldzToTop3_a
.type FldzToTop3_a,  @function
FldzToTop3_a:
#endif
    fstp %st(0)
	fstp %st(0)
	fstp %st(0)
	fldz
	fldz
	fldz
    ret

#ifdef TARGET_MAC
.global _mmx_save
_mmx_save:
#else
.global mmx_save
.type mmx_save,  @function
mmx_save:
#endif
  mov    4(%esp), %eax    
  fxsave (%eax)
  RET


#ifdef TARGET_MAC
.global _mmx_restore
_mmx_restore:
#else
.global mmx_restore
.type mmx_restore,  @function
mmx_restore:
#endif
  mov     4(%esp), %eax
  fxrstor (%eax)
  RET



