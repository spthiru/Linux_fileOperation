/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 16/11/2023                                                                               */
/*   File name      : mkdir_rmdir_10.c                                                                         */
/*   Description    : create a 10 directory per secound & delete the directory one by one                      */
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
  int mk_direct, rm_direct, ret;
  mode_t dirPerm;

  ret = EXIT_SUCCESS;
  dirPerm = S_IRWXU | S_IRWXG | S_IRWXO;

  //create new directory
  for(int i=1;i<argc;i++)
  {
     // int mkdir(const char *pathname, mode_t mode);
     mk_direct = mkdir(argv[i], dirPerm);
     if(mk_direct == -1)
     {
	ret = errno;
	perror("mkdir: cannot create directory");
	exit(-ret);
     }
     else
     {
	perror("mkdir()");
	printf("%s\n",argv[i]);
     }
     sleep(1);
  }
  //delete the  directory

  for(int i=1;i<argc;i++)
  {
     // int mkdir(const char *pathname, mode_t mode);
     rm_direct = rmdir(argv[i]);
     if(rm_direct == -1)
     {
	ret = errno;
	perror("rmdir:cannot delete the directory");
	exit(-ret);
     }
     else
     {
	perror("rmdir()");
	printf("%s\n",argv[i]);
     }
     sleep(1);
  }
}
