/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 7/11/2023                                                                                */
/*   File name      : brightness.c                                                                             */
/*   Description    : find a current brightness in our system                                                  */
/***************************************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//macro
#define BACK_LIGHT "/sys/class/backlight/amdgpu_bl0/actual_brightness"

int main()
{
  int fd, openFlag;
  ssize_t numRead;
  ssize_t wt;
  ssize_t wt1;
  char buf1[50]="Brightness : ";
  char buf[255];
  int ret = EXIT_SUCCESS;

  openFlag = O_RDONLY;

  //open brigtness file 
  //int open(const char *pathname, int flags);
  fd = open(BACK_LIGHT, openFlag);
  if(fd == -1)
  {
     ret = errno;
     perror("error opening brightness file :");
     goto exit_ret;
  }
  //reading brightness %
  //ssize_t read(int fd, void *buf, size_t count);
  numRead = read(fd, buf, 255);
  if(numRead == -1)
  {
     ret =errno;
     perror("error reading brightness file :");
     goto close_fd;
  }
  //writing to STDOUT
  //ssize_t write(int fd, const void *buf, size_t count);
  wt = write(1, buf1,50);
  if(wt == -1)
  {
     ret = errno;
     perror("error writing string to STDOUT");
     goto close_fd;
  }
  //write to STDOUT
  //ssize_t write(int fd, const void *buf, size_t count);
  wt1 = write(1, buf,numRead);
  if(wt1 ==-1)
  {
     ret = errno;
     perror("error writing brightness file percentage:");
     goto close_fd;
  }
exit_ret:
  exit(-ret);
close_fd:
  close(fd);
}
