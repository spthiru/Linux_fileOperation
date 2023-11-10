/***************************************************************************************************************/
/*   Author         : Thirumoorthy P									       */
/*   Date           : 7/11/2023                                                                                */
/*   File name      : lineofmultiply.c                                                                         */
/*   Description    : read the multiply of 10 line write output file                                           */
/***************************************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//macro
#define BUF_SIZE 100000
int main(int argc, char *argv[])
{
  int fd , fd1, openFlag,openFlag1, newLine=0, lineNum, bytes=0, bytes2=0, inc_val=1, bytesAdd=0;
  mode_t filePerm;
  ssize_t readBytes;
  ssize_t readBytes1;
  ssize_t writebytes;
  off_t curSet;
  off_t curSet1;
  char buf[BUF_SIZE];
  char buf1[BUF_SIZE];
  int ret = EXIT_SUCCESS;

  openFlag = O_RDONLY;
  openFlag1 = O_CREAT | O_WRONLY;

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; 

  //open a content file
  //int open(const char *pathname, int flags);
  fd = open(argv[1], openFlag);
  if(fd == -1)
  {
     ret = errno;
     perror("error opening input file");
     goto exit_ret;
  }

  //creating new file in output
  //int open(const char *pathname, int flags);
  fd1 = open(argv[2], openFlag1, filePerm);
  if(fd1 == -1)
  {
     ret = errno;
     perror("Error cannot create newFile");
     goto close_fd;
  }
  //Reading input file
  //ssize_t read(int fd, void *buf, size_t count);
  readBytes = read(fd, buf, BUF_SIZE);
  if(readBytes == -1)
  {
    ret = errno;
    perror("Error cannot read input file:");
    goto close_fd1;
  }

  for(int i=0; i<readBytes; i++ )
  {
    bytes++;
    if(buf[i] == 10)
    {
      newLine++;
    }

    lineNum =(10*inc_val)-1;

    if(newLine == lineNum )
    {
      //set cursur to 10th line in input file
      //off_t lseek(int fd, off_t offset, int whence);
      curSet = lseek(fd, bytes, SEEK_SET);
      if(curSet == -1)
      {
	 ret = errno;
	 perror("cannot set a cursur in input file:");
	 goto close_fd1;
      }
      //reading output file for set cursur
      //ssize_t read(int fd, void *buf, size_t count);
      readBytes1 = read(fd, buf1, BUF_SIZE);
      if(readBytes1 == -1)
      {
	 ret = errno;
	 perror("Error reading output file");
	 goto close_fd1;
      }

      for(int j=0; j < readBytes1; j++)
      {
	bytes2++;
	if(buf1[j] == 10)
	{
	  break;
	}
      }
      //write a data to output file
      //ssize_t write(int fd, const void *buf, size_t count);
      writebytes = write(fd1, buf1, bytes2);
      if(writeBytes == -1)
      {
	 ret = errno;
	 perror("error writing to output file");
	 goto close_fd1;
      }

      bytesAdd = bytesAdd + bytes2;

      //set cursur output file
      //off_t lseek(int fd, off_t offset, int whence);
      curSet1 = lseek(fd1, bytesAdd, SEEK_SET);
      if(curSet1 == -1)
      {
	 ret = errno;
	 perror("Error setcur for ouput file");
	 goto close_fd1;
      }

      bytes2 = 0;
      //lineNum =(10*inc_val)-1;
      inc_val++;
    }
  }
exit_ret:
  	exit(-ret);
close_fd:
	close(fd);
close_fd1:
	close(fd);
	close(fd1);
}
