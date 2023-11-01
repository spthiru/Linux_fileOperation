#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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

  openFlag = O_RDONLY;
  openFlag1 = O_CREAT | O_WRONLY;

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; 

  //int open(const char *pathname, int flags);
  fd = open(argv[1], openFlag);

  //int open(const char *pathname, int flags);
  fd1 = open(argv[2], openFlag1, filePerm);
  if(fd == -1)
  {
  perror("open()");
  close(fd);
  }

  //ssize_t read(int fd, void *buf, size_t count);
  readBytes = read(fd, buf, BUF_SIZE);
  if(readBytes == -1)
  {
    perror("read()");
    close(fd);
    close(fd1);
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
      //off_t lseek(int fd, off_t offset, int whence);
      curSet = lseek(fd, bytes, SEEK_SET);

      //ssize_t read(int fd, void *buf, size_t count);
      readBytes1 = read(fd, buf1, BUF_SIZE);

      for(int j=0; j < readBytes1; j++)
      {
	bytes2++;
	if(buf1[j] == 10)
	{
	  break;
	}
      }

      //ssize_t write(int fd, const void *buf, size_t count);
      writebytes = write(fd1, buf1, bytes2);

      bytesAdd = bytesAdd + bytes2;

      //off_t lseek(int fd, off_t offset, int whence);
      curSet1 = lseek(fd1, bytesAdd, SEEK_SET);

      bytes2 = 0;
      //lineNum =(10*inc_val)-1;
      inc_val++;
    }
  }

  // int close(int fd);
  close(fd);
  close(fd1);
}
