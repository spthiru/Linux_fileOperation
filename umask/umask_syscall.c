/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 24/11/2023                                                                               */
/*   File name      : umask_syscall.c                                                                          */
/*   Description    : change file permission in using umask                                                    */
/***************************************************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h> 

int main(int argc, char *argv[])
{
   int fd, ret;
   ret = EXIT_SUCCESS;
   mode_t old_umask, new_umask;

      //mode_t umask(mode_t mask);
      old_umask = umask((0666&(~0444)));
      new_umask = umask((0666&(~0222)));
      if(old_umask == -1)
      {
	 ret = errno;
	 perror("umask:error file permission change:");
	 goto exit_ret;
      }

      //int open(const char *pathname, int flags, mode_t mode);
      fd = open(argv[1], O_CREAT | O_RDWR, new_umask);
      if(fd == -1)
      {
	 ret = errno;
	 perror("open():cannot create file");
	 goto exit_ret;
      }
exit_ret:
      exit(-ret);
}
