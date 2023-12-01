#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 20
int main(int argc ,char *argv[])
{
   int fd, ret, i, dup_newFd;
   ssize_t readBytes, readBytes1; 
   char buf[BUF_SIZE], buf1[BUF_SIZE];

   ret = EXIT_SUCCESS;

   //int open(const char *pathname, int flags);
   fd = open(argv[1], O_RDONLY);
   if(fd == -1)
   {
      ret = errno;
      perror("open:cannot open a file");
      goto ret_exit;
   }
   printf("oldfd : %d\n",fd);
   //ssize_t read(int fd, void *buf, size_t count);
   readBytes = read(fd, buf, BUF_SIZE);
   if(readBytes == -1)
   {
      ret = errno;
      perror("read:cannot read file");
      goto close_fd;
   }

   for(i = 0; i < readBytes ; i++)
   {
      printf("%c",buf[i]);
   }
   //int dup(int oldfd);
   dup_newFd = dup(fd);
   if(dup_newFd == -1)
   {
      ret = errno;
      perror("dup:cannot duplicate txt fd");
      goto close_fd;
   }
   printf("\nnew fd : %d\n",dup_newFd);
   //ssize_t read(int fd, void *buf, size_t count);
   readBytes1 = read(dup_newFd, buf1, BUF_SIZE);
   if(readBytes1 = -1)
   {
      ret = errno;
      perror("read: cannot read dup_newfd");
      goto close_fd1;
   }
   for( i = 0; i < readBytes1; i++)
   {
      printf("%c",buf1[i]);
   }
ret_exit:
   exit(-ret);
close_fd:
   close(fd);
close_fd1:
   close(fd);
   close(dup_newFd);
}
