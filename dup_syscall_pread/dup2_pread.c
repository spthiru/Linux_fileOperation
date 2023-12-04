/***************************************************************************************************************/
/*   Author         : Thirumoorthy P									       */
/*   Date           : 03/12/2023                                                                               */
/*   File name      : dup2_pread.c                                                                             */
/*   Description    : understading dup2,pread system call                                                      */
/***************************************************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 20

int main(int argc, char *argv[])
{
   int fd, ret, newfd_dup2;
   ssize_t preadbytes, preadbytes1;
   off_t ret_lseek, ret_lseek1;
   char buf[BUF_SIZE], buf1[BUF_SIZE];

   ret = EXIT_SUCCESS;
   //int open(const char *pathname, int flags);
   fd = open(argv[1], O_RDONLY);
   if(fd == -1)
   {
      ret = errno;
      perror("open:cannot open input file");
      goto exit_ret;
   }
   printf("old fd : %d\n", fd);

   //off_t lseek(int fd, off_t offset, int whence);
   ret_lseek = lseek(fd, 20, SEEK_SET); //set cursur position 20
   if(ret_lseek == -1)
   {
      ret = errno;
      perror("lseek:cursur not set");
      goto close_fd; 
   }
   printf("file pointer position : %ld\n",ret_lseek);

   //ssize_t pread(int fd, void *buf, size_t count, off_t offset);
   preadbytes = pread(fd, buf, 20, 0); //read the input file and store in buf
   if(preadbytes == -1)
   {
      ret = errno;
      perror("pread:cannot read input file");
      goto close_fd;
   }
   printf("%s\n",buf);


   //int dup2(int oldfd, int newfd);
   newfd_dup2 = dup2(fd, 4);
   if(newfd_dup2 == -1)
   {
      ret = errno;
      perror("dup2:cannot change old fd");
      goto close_fd;
   }
   printf("newfd : %d\n", newfd_dup2);

   //off_t lseek(int fd, off_t offset, int whence);
   ret_lseek1 = lseek(newfd_dup2, 20, SEEK_CUR);
   if(ret_lseek == -1)
   {
      ret = errno;
      perror("lseek:cannot set cursur");
      goto close_fd1;
   }
   printf("file pointer position : %ld\n",ret_lseek1);

   //ssize_t pread(int fd, void *buf, size_t count, off_t offset);
   preadbytes1 = pread(newfd_dup2, buf1, 20, 0);
   if(preadbytes == -1)
   {
      ret = errno;
      perror("pread:cannot read input file");
      goto close_fd1;
   }
   printf("%s\n", buf1);


exit_ret:
   exit(-ret);
close_fd:
   close(fd);
close_fd1:
   close(fd);
   close(newfd_dup2);
}
