#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
   int ret, s_ret, i;
   ret = EXIT_SUCCESS;
   struct timespec st_mtim;
   struct stat moniter;

   for(i = 1; i < argc; i++)
   { 
      //int stat(const char *pathname, struct stat *statbuf);
      s_ret = stat(argv[i], &moniter);
      if(s_ret == -1)
      {
      	 ret = errno;
   	 perror("stat:error get details about the file");
      	 goto exit_ret;
      }
      printf("file name : %s\n",argv[i]);
      printf("Last file modification time:   %s", ctime(&moniter.st_mtime));
   }
exit_ret:
   exit(-ret);
}

