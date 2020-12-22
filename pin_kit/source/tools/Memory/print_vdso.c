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
#include <errno.h>
#include <unistd.h>
#include <elf.h>

void* findVdso(void* auxv_start)
{
#ifdef TARGET_IA32
   Elf32_auxv_t * auxv = (Elf32_auxv_t *) auxv_start ;
   void* vdso = (void*)0xffffe000;
#else
   Elf64_auxv_t * auxv = (Elf64_auxv_t *) auxv_start ;
   void* vdso = (void*)0xffffffffff600000;
#endif

   for ( ; auxv->a_type != AT_NULL ; auxv++ )
   {
      if ( auxv->a_type == AT_SYSINFO_EHDR )
      {
         return (void*)auxv->a_un.a_val;
      }
   }
   return vdso;
}

int main( int argc, char **argv, char **envp )
{
   while ( *envp++ != NULL );

   void* vdso = findVdso(envp);

   printf("%p:%p\n", vdso, vdso + getpagesize());

   return 0;
}
