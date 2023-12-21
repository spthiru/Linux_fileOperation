#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 10001
int main(int argc, char *argv[])
{
   int ret, fd, fd1, fd2, fd3, fd4, c_fd;
   ssize_t readbytes, readbytes1, readbytes2, readbytes3, readbytes4, pwritev_bytes;
   char buf[BUF_SIZE], buf1[BUF_SIZE], buf2[BUF_SIZE], buf3[BUF_SIZE], buf4[BUF_SIZE];
   struct iovec gather[5];
   off_t cur_pos, cur_pos1, cur_pos2, cur_pos3, cur_pos4, cur_pos5;

   ret = EXIT_SUCCESS;
   
   //int open(const char *pathname, int flags);
   c_fd = open(argv[6], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
   if(c_fd == -1)
   {
      ret = errno;
      perror("open: cannot create a file");
      exit(-ret);
   }
   //int open(const char *pathname, int flags);
   fd = open(argv[1], O_RDONLY);
   if(fd == -1)
   {
      ret = errno;
      perror("open: cannot open linux file");
      goto exit_ret;
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes = read(fd, buf, BUF_SIZE);
   if(readbytes == -1)
   {
      ret = errno;
      perror("read:cannot read linux file");
      goto close_fd;
   }
   //off_t lseek(int fd, off_t offset, int whence);
   cur_pos1 = lseek(fd, 0, SEEK_CUR);
   if(cur_pos1 == -1)
   {
      ret = errno;
      perror("lseek:cannnot find a cursur file1");
      goto close_fd;
   }
   printf("cursur position file1: %ld\n",cur_pos1);
   //int open(const char *pathname, int flags);
   fd1 = open(argv[2], O_RDONLY);
   if(fd1 == -1)
   {
      ret = errno;
      perror("open:cannot open linux1 file");
      goto close_fd;
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes1 = read(fd1, buf1, BUF_SIZE);
   if(readbytes1 == -1)
   {
      ret = errno;
      perror("read:cannot read linux1 file ");
      goto close_fd1;
   }
   //off_t lseek(int fd, off_t offset, int whence);
   cur_pos2 = lseek(fd1, cur_pos1, SEEK_CUR);
   if(cur_pos2 == -1)
   {
      ret = errno;
      perror("lseek:cannnot find a cursur file2");
      goto close_fd1;
   }
   printf("cursur position file2 : %ld\n",cur_pos2);
   //int open(const char *pathname, int flags);
   fd2 = open(argv[3], O_RDONLY);
   if(fd2 == -1)
   {
      ret = errno;
      perror("open:cannot open linux2 file");
      goto close_fd1;
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes2 = read(fd2, buf2, BUF_SIZE);
   if(readbytes2 == -1)
   {
      ret = errno;
      perror("read:cannot read linux2 file ");
      goto close_fd2;
   }
   //off_t lseek(int fd, off_t offset, int whence);
   cur_pos3 = lseek(fd1, cur_pos2, SEEK_CUR);
   if(cur_pos2 == -1)
   {
      ret = errno;
      perror("lseek:cannnot find a cursur file3");
      goto close_fd2;
   }
   printf("cursur position file3 : %ld\n",cur_pos3);
   //int open(const char *pathname, int flags);
   fd3 = open(argv[4], O_RDONLY);
   if(fd3 == -1)
   {
      ret = errno;
      perror("open:cannot open linux3 file");
      goto close_fd3;
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes3 = read(fd3, buf3, BUF_SIZE);
   if(readbytes3 == -1)
   {
      ret = errno;
      perror("read:cannot read linux3 file ");
      goto close_fd3;
   }
   //off_t lseek(int fd, off_t offset, int whence);
   cur_pos4 = lseek(fd1, cur_pos3, SEEK_CUR);
   if(cur_pos2 == -1)
   {
      ret = errno;
      perror("lseek:cannnot find a cursur file4");
      goto close_fd3;
   }
   printf("cursur position file4 : %ld\n",cur_pos4);
   //int open(const char *pathname, int flags);
   fd4 = open(argv[5], O_RDONLY);
   if(fd4 == -1)
   {
      ret = errno;
      perror("open:cannot open linux4 file");
      goto close_fd4;
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes4 = read(fd4, buf4, BUF_SIZE);
   if(readbytes4 == -1)
   {
      ret = errno;
      perror("read:cannot read linux4 file ");
      goto close_fd4;
   }
   //off_t lseek(int fd, off_t offset, int whence);
   cur_pos5 = lseek(fd1, cur_pos4, SEEK_CUR);
   if(cur_pos2 == -1)
   {
      ret = errno;
      perror("lseek:cannnot find a cursur file5");
      goto close_fd4;
   }
   printf("cursur position file5: %ld\n",cur_pos5);

   gather[0].iov_base = buf;
   gather[0].iov_len = readbytes;
   gather[1].iov_base = buf1;
   gather[1].iov_len = readbytes1;
   gather[2].iov_base = buf2;
   gather[2].iov_len = readbytes2;
   gather[3].iov_base = buf3;
   gather[3].iov_len = readbytes3;
   gather[4].iov_base = buf4;
   gather[4].iov_len = readbytes4;

   //ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt,off_t offset);
   pwritev_bytes = pwritev(c_fd, gather, 5, 0);
   if(pwritev_bytes == -1)
   {
      ret = errno;
      perror("pwritev: error writing bytes");
      goto close_fd4;
   }
   //off_t lseek(int fd, off_t offset, int whence);
   cur_pos = lseek(c_fd, 0, SEEK_CUR);
   if(cur_pos == -1)
   {
      ret = errno;
      perror("lseek:cannnot set cursur");
      goto close_fd4;
   }
   printf("cursur position output file : %ld\n",cur_pos);
close_fd4:
   close(fd);
   close(fd1);
   close(fd2);
   close(fd3);
   close(fd4);
close_fd3:
   close(fd);
   close(fd1);
   close(fd2);
   close(fd3);
close_fd2:
   close(fd);
   close(fd1);
   close(fd2);
close_fd1:
   close(fd);
   close(fd1);
close_fd:
   close(fd);
exit_ret:
   exit(-ret);
}

