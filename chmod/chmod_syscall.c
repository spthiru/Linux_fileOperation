/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 8/11/2023                                                                                */
/*   File name      : chmod_syscall.c                                                                          */
/*   Description    : change the file permission                                                               */
/***************************************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int  ret_chmod, ret;
  mode_t filePerm;

  ret = EXIT_SUCCESS;
  //file permission for input file
  filePerm = S_IRWXU | S_IRWXG | S_IRWXO;

  //change file permission
  //int chmod(const char *pathname, mode_t mode); 
  ret_chmod = chmod(argv[1], filePerm);
  if(ret_chmod == -1)
  {
    ret = errno;
    perror("error changing input file permission:");
    exit(-ret);
  }
}
