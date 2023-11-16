/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 15/11/2023                                                                                */
/*   File name      : remove_dir.c                                                                             */
/*   Description    : delete the directory                                                                     */
/***************************************************************************************************************/

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
   int ret_removedir, ret;
   ret = EXIT_SUCCESS;

   //int rmdir(const char *pathname);
   ret_removedir = rmdir(argv[1]);
   if(ret_removedir == -1)
   {
      ret = errno;
      perror("rmdir:cannot remove the directory");
      exit(-ret);
   }
}
