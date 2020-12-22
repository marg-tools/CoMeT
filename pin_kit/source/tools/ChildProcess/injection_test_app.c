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

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
 
int
main (int argc, char *argv[])
{
  int fd;
  pid_t pid;
  const char *name = argv[1];
  int status;
 
  fd = creat (name, S_IRWXU|S_IRWXG|S_IRWXO);
  close (fd);
  unlink (name);
  fd = creat (name, S_IRWXU|S_IRWXG|S_IRWXO);
  close (fd);
  if ((pid = fork()) < 0)
  {
      printf("fork failed\n");
      abort ();
  }
  if (pid == 0)
  {
     execl ("/bin/chmod", "chmod", "a-x", name, (char *) NULL);
     printf("Execl exited with error %d\n", errno);
     abort ();
  }
  wait (&status);
  
  if (access (name, F_OK|X_OK) == 0)
  {
      printf("access shows that x-access to file %s is not removed\n", name);
      abort ();
  }
  unlink(name);
  return 0;
} 
                     



