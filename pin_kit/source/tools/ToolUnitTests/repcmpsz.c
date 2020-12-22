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

#include <stdio.h>

extern __declspec(dllexport) int main(int argc, char ** argv)
{
    char stringOne[] = "IAMHEREE";
    char stringTwo[] = "IWASHERE";
#define length 9

    printf ("Starting...\n");
    __asm {
        fnop                                      
	cld
        xor     ebx, ebx                      ; ebx holds test number (used as exit code on failure)
        
; Test different string comparison
        inc     ebx
	lea	esi, stringOne
	lea	edi, stringTwo
	mov     ecx, length
	repe cmpsb
        cmp     ecx,(length-2)                ; Should fail at second byte
        jne     l2

; Test same string comparison
        inc     ebx
	lea	esi, stringOne
	lea	edi, stringOne
	mov     ecx, length
	repe cmpsb 
        test    ecx,ecx                       ; Should run full length
        jne     l2

; Test same string comparison, but with no count...
        inc     ebx
	lea	esi, stringOne
	lea	edi, stringOne
        xor     ecx,ecx
	repe cmpsb 
        test    ecx,ecx                       ; Should still be zero
        jne     l2

; Test scasd
        inc     ebx
	lea	eax, stringOne
	lea	edi, stringTwo
	scasw
	mov     eax,ecx
	
; and return

	mov	ebx,0		; first argument: result from main
l2:
	mov	ebx,eax
        fnop                                      
    }
    
    printf ("Ending...\n");
    return 0;
}
