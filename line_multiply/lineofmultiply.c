//header file incluction
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

//macro
#define BUF_SIZE 100000

//main function
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

  openFlag = O_RDONLY;//openflag for source file opening
  openFlag1 = O_CREAT | O_WRONLY; //open flag for output creat file

  filePerm = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; //file permission of output fle creating

  //int open(const char *pathname, int flags);
  fd = open(argv[1], openFlag);
  if(fd == -1)
  {
     perror("error opening source_file");
     exit(-1);
  }

  //int open(const char *pathname, int flags);
  fd1 = open(argv[2], openFlag1, filePerm);
  if(fd1 == -1)
  {
     perror("error opening creating output file");
     close(fd);
     exit(-2);
  }

  //ssize_t read(int fd, void *buf, size_t count);
  readBytes = read(fd, buf, BUF_SIZE);
  if(readBytes == -1)
  { 
     perror("error reading source file");
     close(fd);
     close(fd1);
     exit(-3);
  }

  for(int i=0; i<readBytes; i++ )
  {
    bytes++; //calculating bytes
    if(buf[i] == 10)
    {
      newLine++; //calculating new lines
    }

    lineNum =(10*inc_val)-1; //calculation which line  multiply writng in output file

    if(newLine == lineNum )
    {
      //off_t lseek(int fd, off_t offset, int whence);
      curSet = lseek(fd, bytes, SEEK_SET);
      if(curSet == -1)
      {
	perror("error set curser of source file");
	close(readBytes);
        close(fd1);
        close(fd);
        exit(-4);
      }

      //ssize_t read(int fd, void *buf, size_t count);
      readBytes1 = read(fd, buf1, BUF_SIZE);
      if(readBytes1 == -1)
      {
	perror("error reading source file");
	close(curSet);
	close(readBytes);
	close(fd1);
	close(fd);
	exit(-5);
      }

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
      if(writebytes == -1)
      {
	perror("error writing a output file");
	close(readBytes1);
	close(curSet);
	close(readBytes);
	close(fd1);
	close(fd);
	exit(-5);
	      
      }
      bytesAdd = bytesAdd + bytes2;

      //off_t lseek(int fd, off_t offset, int whence);
      curSet1 = lseek(fd1, bytesAdd, SEEK_SET);
      if(curSet1 == -1)
      {
	perror("error set curser a output file");
	close(writeBytes);
	close(readBytes1);
	close(curSet);
	close(readBytes);
	close(fd1);
	close(fd);
	exit(-6);
      }

      bytes2 = 0;
      //lineNum =(10*inc_val)-1;
      inc_val++;
    }
  }

  // int close(int fd);
  close(fd);
  close(fd1);
}
