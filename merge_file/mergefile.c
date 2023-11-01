#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 100000
int main(int argc, char *argv[])
{
  int fd, fd1, fd2, openFlag, openFlag1;
  mode_t filePerm;
  ssize_t readbytes;
  ssize_t readbytes1;
  ssize_t writeFile;
  ssize_t writeFile1;
  char buf[BUF_SIZE];
  char buf1[BUF_SIZE];
  off_t setCur;

  openFlag =  O_RDWR;
  openFlag1 =  O_CREAT | O_RDWR;

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

  //int open(const char *pathname, int flags);
  fd = open(argv[1], openFlag);

  //int open(const char *pathname, int flags);
  fd1 = open(argv[2], openFlag);

  //int open(const char *pathname, int flags);
  fd2 = open(argv[3], openFlag1, filePerm);

  //ssize_t read(int fd, void *buf, size_t count);
  readbytes = read(fd, buf, BUF_SIZE);

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile = write(fd2, buf, readbytes);

  //  off_t lseek(int fd, off_t offset, int whence);
  setCur = lseek(fd2, 0, SEEK_END);

  //ssize_t read(int fd, void *buf, size_t count);
  readbytes1 = read(fd1, buf1, BUF_SIZE);

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(fd2, buf1, readbytes1);

  //int close(int fd);
  close(fd);
  close(fd1);
  close(fd2);
}
