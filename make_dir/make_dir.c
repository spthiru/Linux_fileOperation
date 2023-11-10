/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 8/11/2023                                                                                */
/*   File name      : make_direct.c                                                                            */
/*   Description    : create a new directory                                                                   */
/***************************************************************************************************************/

//header file inclution
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char *argv[])
{
  int mk_direct, ret;
  mode_t dirPerm;

  ret = EXIT_SUCCESS;
  dirPerm = S_IRWXU | S_IRWXG | S_IRWXO;

   //create new directory
  // int mkdir(const char *pathname, mode_t mode);
  mk_direct = mkdir(argv[1], dirPerm);
  if(mk_direct == -1)
  {
    ret = errno;
    perror("error created new directory:");
    exit(-ret);
  }
}
