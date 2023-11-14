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
  int  ret_chmod, ret, deci, div, mod, octal, temp=0, l=0;
  int arr[8]={00,01,02,03,04,05,06,07};
  //string to decimal converting
  deci = atoi(argv[2]);
  //decimal to octal converting
  while(deci > 0)
  {
     div = deci / 10;
     mod = deci % 10;
     deci = div;
     if(mod<=7 && mod>=0)
     {
	octal = arr[mod]<<l | temp;
     }
     else 
     {
	printf("Enter the vaild octal number\n");
	exit(-1);
     }
     temp = octal;
     l = l + 3;
  }
  ret = EXIT_SUCCESS;

  //change the file permission 
  //int chmod(const char *pathname, mode_t mode); 
  ret_chmod = chmod(argv[1], octal);
  if(ret_chmod == -1)
  {
    ret = errno;
    perror("chmod: cannot change file permission");
    exit(-ret);
  }
}
