#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BACK_LIGHT "/sys/class/backlight/amdgpu_bl0/actual_brightness"
int main()
{
  int fd, openFlag;
  ssize_t numRead;
  ssize_t wt;
  ssize_t wt1;
  char buf1[50]="Brightness : ";
  char buf[255];

  openFlag = O_RDONLY;

  //int open(const char *pathname, int flags);
  fd = open(BACK_LIGHT, openFlag);

  //ssize_t read(int fd, void *buf, size_t count);
  numRead = read(fd, buf, 255);

  //ssize_t write(int fd, const void *buf, size_t count);
  wt = write(1, buf1,50);

  //ssize_t write(int fd, const void *buf, size_t count);
  wt1 = write(1, buf,numRead);

  //int close(int fd);
  close(fd);
  exit(0);
}
