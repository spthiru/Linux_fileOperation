/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 14/12/2023                                                                               */
/*   File name      : dup2_read_write.c                                                                        */
/*   Description    : understanding about dup2 								       */ 
/***************************************************************************************************************/
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 21
#define BUF_SIZE1 11

int main(int argc, char *argv[])
{
   int fd, ret,dup2_nfd, inc_val =1;
   ssize_t writebytes, writebytes1, readbytes, readbytes1, readbytes2, readbytes3;
   off_t ret_lseek;

   char buf[BUF_SIZE] = "GOOD MORNING TO ALL\n";
   char buf1[BUF_SIZE] = "good morning to all\n";
   char buf2[BUF_SIZE1];
   char buf3[BUF_SIZE1];
   char buf4[BUF_SIZE1];
   char buf5[BUF_SIZE1];
   ret = EXIT_SUCCESS;

   //Step1 - open a text file (read and write)
   //int open(const char *pathname, int flags);
   fd = open(argv[1], O_RDWR);
   if(fd == -1)
   {
      ret = errno;
      perror("open: cannot open file");
      goto exit_ret;
   }

    //Step2 - call dup2() by passing fd from step 1 as old fd (fd1) and any unused fd as new fd (fd2)
   //int dup2(int oldfd, int newfd);
   dup2_nfd = dup2(fd, 1023);
   if(dup2_nfd == -1)
   {
      ret = errno;
      perror("dup2:error creating newfd");
      goto close_fd;
   }

   //Step3 - write 20 bytes of string to fd1 
   //ssize_t write(int fd, const void *buf, size_t count);
   writebytes = write(fd, buf, BUF_SIZE-1);
   if(writebytes == -1)
   {
      ret = errno;
      perror("write:error writing buf string");
      goto close_fd1;
   }

   //Step4 - write 20 bytes of string to fd2
   //ssize_t write(int fd, const void *buf, size_t count);
   writebytes1 = write(dup2_nfd, buf1, BUF_SIZE-1);
   if(writebytes1 == -1)
   {
      ret = errno;
      perror("write:error writing buf1 string");
      goto close_fd1;
   }

   //Step5 - use lseek() to move the file position of fd1 to 0
   //off_t lseek(int fd, off_t offset, int whence);
   ret_lseek = lseek(fd, 0, SEEK_SET);
   if(ret_lseek == -1)
   {
      ret = errno;
      perror("lseek:cannot set cursur to 0 in fd");
      goto close_fd1;
   }

   //Step6 - read and print 10 bytes from fd1
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes = read(fd, buf2, BUF_SIZE1-1);
   if(readbytes == -1)
   {
      ret = errno;
      perror("read:error reading fd");
      goto close_fd1;
   }
   printf("%s\n",buf2);

   //Step7 - read and print 10 bytes from fd2
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes1 = read(dup2_nfd, buf3, BUF_SIZE1-1);
   if(readbytes1 == -1)
   {
      ret = errno;
      perror("read: error reading dup2_nfd");
      goto close_fd1;
   }
   printf("%s\n",buf3);

   //Step8 - do step6
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes2 = read(fd, buf4, BUF_SIZE1-1);
   if(readbytes == -1)
   {
      ret = errno;
      perror("read:error reading fd");
      goto close_fd1;
   }
   printf("%s\n",buf4);

   //Step9 - do step7
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes3 = read(dup2_nfd, buf5, BUF_SIZE1-1);
   if(readbytes3 == -1)
   {
      ret = errno;
      perror("read: error reading dup2_nfd");
      goto close_fd1;
   }
   printf("%s\n",buf5);
   goto close_fd1;

//Step10 - close fd1 and fd2
close_fd1:
   close(fd);
   close(dup2_nfd);
close_fd:
   close(fd);
exit_ret:
   exit(-ret);
}
