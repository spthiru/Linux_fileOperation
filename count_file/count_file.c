#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 1000000
int main(int argc, char *argv[])
{
   int fd, ret, count, n_line_count = 0, wrd_count = 0;
   ssize_t readbytes;
   char buf[BUF_SIZE];
   ret = EXIT_SUCCESS;

   //int open(const char *pathname, int flags);
   fd = open(argv[1], O_RDWR);
   if(fd == -1)
   {
      ret = errno;
      perror("open:cannot open source file");
      goto ret_exit;
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes = read(fd, buf, BUF_SIZE);
   if(readbytes == -1)
   {
      ret = errno;
      perror("read:cannot the source file");
      goto close_fd;
   }
      for(count = 0;count < readbytes; count++)
      {
	 wrd_count++;
	 if(buf[count] == 10)
	 {
	    n_line_count++;
	 }
      }
      printf("Word Count : %d\n",wrd_count);
      printf("NewLine Count : %d\n",n_line_count);
ret_exit:
   exit(-ret);
close_fd:
   close(fd);
}
