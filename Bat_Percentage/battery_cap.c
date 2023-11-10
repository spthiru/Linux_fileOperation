/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 7/11/2023                                                                                */
/*   File name      : bat_per.c                                                                                */
/*   Description    : find a current battery percentage                                                        */
/***************************************************************************************************************/
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
#define BAT_CAP_FILE_PATH "/sys/class/power_supply/BAT1/capacity"

//main function
int main(int argc, char *argv[])
{
  int fd, openFlag;
  ssize_t numRead;
  ssize_t writeFile;
  ssize_t writeFile1;
  char buf1[BUF_SIZE]="Battery Percentage:";
  char buf[BUF_SIZE];
  int ret = EXIT_SUCCESS;


  openFlag = O_RDONLY; //set openflag for battery capacity file

  //open the battery capacity file
  // int open(const char *pathname, int flags);
  fd = open(BAT_CAP_FILE_PATH, openFlag);
  if(fd == -1)
  {
     ret = errno;
    perror("error opening battery capacity file:");
    goto exit_ret;
  }

  //reading the battery capacity percentage
  //ssize_t read(int fd, void *buf, size_t count);
  numRead = read(fd, buf, BUF_SIZE);
  if(numRead == -1)
  {
     ret = errno;
    perror("error reading battery capcity file:");
    goto close_fd;
  }

  //writing to STDOUT
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile = write(1, buf1, BUF_SIZE);
  if(writeFile == -1)
  {
    ret = errno;
    perror("error writing to STDOUT:");
    goto close_fd;
  }

  //writing to STDOUT
  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(1, buf, numRead);
  if(writeFile1 == -1)
  {
     ret = errno; 
    perror("error writing battery capacity percentage:");
  }

close_fd:
  close(fd);
exit_ret:
  exit(-ret);
}
