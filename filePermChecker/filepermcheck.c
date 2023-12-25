/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 24/12/2023                                                                               */
/*   File name      : filePermchecker.c                                                                        */
/*   Description    : check the permission of the file                                                         */
/***************************************************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
   int ret_stat, ret, i;
   struct stat fp_checker;
   char buf[11] = "--- --- ---";

   ret = EXIT_SUCCESS;

   for(i = 1; i < argc; i++)
   {
      //int stat(const char *pathname, struct stat *statbuf);
      ret_stat = stat(argv[i],&fp_checker);
      if(ret_stat == -1)
      {
	 ret = errno;
	 perror("stat:cannot get file details");
	 goto exit_ret;
      }
      buf[0] = fp_checker.st_mode & S_IRUSR ? 'r': '-';
      buf[1] = fp_checker.st_mode & S_IWUSR ? 'w': '-';
      buf[2] = fp_checker.st_mode & S_IXUSR ? 'x': '-';
      buf[4] = fp_checker.st_mode & S_IRGRP ? 'r': '-';
      buf[5] = fp_checker.st_mode & S_IWGRP ? 'w': '-';
      buf[6] = fp_checker.st_mode & S_IXGRP ? 'x': '-';
      buf[8] = fp_checker.st_mode & S_IROTH ? 'r': '-';
      buf[9] = fp_checker.st_mode & S_IWOTH ? 'w': '-';
      buf[10] = fp_checker.st_mode & S_IXOTH ? 'x': '-';
      
      printf("File Name       : %s\n",argv[i]);
      printf("File Permission : %s\n",buf);
      printf("Total Size      : %ld\n\n",fp_checker.st_size);
   }
exit_ret:                                                                                                                                         
   exit(-ret);
}
