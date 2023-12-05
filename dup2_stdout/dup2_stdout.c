/***************************************************************************************************************/
/*   Author         : Thirumoorthy P									       */
/*   Date           : 05/12/2023                                                                               */
/*   File name      : dup2_pread.c                                                                             */
/*   Description    : passing stdout as old fd and an unused fd as new fd                                      */
/***************************************************************************************************************/

#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 27	

int  main()
{
   int ret_d2newfd, n_fd, ret;
   ssize_t writebytes;

   ret = EXIT_SUCCESS;
   char buf[BUF_SIZE] = "SCHOOL OF LINUX DHARMAPURI\n"; 
   n_fd = 5;

   //int dup2(int oldfd, int newfd);
   ret_d2newfd = dup2(1, n_fd); //set a oldfd as stdout
   if(ret_d2newfd == -1)
   {
      ret = errno;
      perror("dup2:cannot change old fd");
      goto exit_ret;
   }

   //ssize_t write(int fd, const void *buf, size_t count);
   writebytes = write(ret_d2newfd, buf, BUF_SIZE); //write string using dup2 return newfd
   if(writebytes == -1)
   {
      ret = errno;
      perror("write: Error writing string:");
      goto exit_ret;
   }

exit_ret:
   exit(-ret);;
}
