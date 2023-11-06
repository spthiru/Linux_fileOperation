//header file incluction
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//macro
#define BUF_SIZE 50

//main function
int main(int argc, char *argv[])
{
  int fd, openFlag;
  ssize_t numRead;
  ssize_t writeFile;
  ssize_t writeFile1;
  char buf1[BUF_SIZE]="Battery Percentage:";
  char buf[BUF_SIZE];


  openFlag = O_RDONLY; //set openflag for sourcefile

  //open source file
  // int open(const char *pathname, int flags);
  fd = open("/sys/class/power_supply/BAT1/capacity", openFlag);
  if(fd == -1)
  {
    perror("error opening input file");
    exit(-1);
  }

  //ssize_t read(int fd, void *buf, size_t count);
  numRead = read(fd, buf, BUF_SIZE);
  if(numRead == -1)
  {
    perror("error reading input file\n");
    close(fd);
    exit(-2);
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile = write(1, buf1, BUF_SIZE);
  if(writeFile == -1)
  {
    perror("error writing output buffer1\n");
    close(numRead);
    close(fd);
    exit(-3);
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(1, buf, numRead);
  if(writeFile1 == -1)
  {
    perror("error writing input file");
    close(numRead);
    close(writeFile);
    close(fd);
    exit(-5);
  }

  // int close(int fd);
  close(writeFile1);
  close(fd);
  exit(0);
}
