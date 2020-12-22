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

# 
#  struct FarPointer
#  {
#      unsigned int _farPtr;
#      unsigned int _segVal;
#  };

#  int SetGs(const FarPointer *fp);


.global SetGs
.type SetGs, @function


SetGs:
   push %ebp
   mov %esp, %ebp
   mov 0x8(%ebp), %eax
   lgs (%eax), %eax
   leave
   ret

#  int SetFs(const FarPointer *fp);

.global SetFs
.type SetFs, @function

SetFs:
   push %ebp
   mov %esp, %ebp
   mov 0x8(%ebp), %eax
   lfs (%eax), %eax
   leave
   ret
   
#  unsigned int GetGsBase();
#  unsigned int GetFsBase();

.global GetGsBase
.type GetGsBase, @function


GetGsBase:
   mov %gs:0x0, %eax
   ret
   
.global GetFsBase
.type GetFsBase, @function

GetFsBase:
   mov %fs:0x0, %eax
   ret
   

