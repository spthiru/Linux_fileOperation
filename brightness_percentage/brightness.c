//header file incuction
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// macro
#define BACK_LIGHT "/sys/class/backlight/amdgpu_bl0/actual_brightness"

//main function
int main()
{
  int fd, openFlag;
  ssize_t numRead;
  ssize_t wt;
  ssize_t wt1;
  char buf1[50]="Brightness : ";
  char buf[255];

  openFlag = O_RDONLY;//open flag for source file

  //open source file
  //int open(const char *pathname, int flags);
  fd = open(BACK_LIGHT, openFlag);
  if(fd == -1)
  {
    perror("error opening file");
    exit(-1);
  } 
  //ssize_t read(int fd, void *buf, size_t count);
  numRead = read(fd, buf, 255);
  if(numRead == -1)
  {
    perror("error reading file");
    close(fd);
    exit(-2);
  }
  //ssize_t write(int fd, const void *buf, size_t count);
  wt = write(1, buf1,50);
  if(wt == -1)
  {
    perror("error writing a file");
    close(numRead);
    close(fd);
    exit(-3);
  }

  //ssize_t write(int fd, const void *buf, size_t count);
  wt1 = write(1, buf,numRead);
  if(wt1 == -1)
  {
    perror("error writing a file");
    close(wt);
    close(numRead);
    close(fd);
    exit(-4);
  }

  //int close(int fd);
  close(fd);
  close(wt1);
  exit(0);
}
