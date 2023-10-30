#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 100000
int main(int argc, char *argv[])
{
  int fd, fd1, fd2, openFlag, openFlag1, openFlag2, n_line, n_line1, divide, bytes;
  mode_t filePerm;
  ssize_t readFile;
  ssize_t readFile1;
  ssize_t writeFile;
  ssize_t writeFile1;
  char buf[BUF_SIZE];
  char buf1[BUF_SIZE];
  off_t setcur;

  n_line = 0;
  n_line1 = 0;
  bytes = 0;

  openFlag = O_RDWR;
  openFlag1 = O_CREAT | O_WRONLY;  //openflag of splitfile1
  openFlag2 = O_CREAT | O_WRONLY;  //openflag of splitfile2

  filePerm =  S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;

  //int open(const char *pathname, int flags);
  fd = open(argv[1], openFlag);

  //ssize_t read(int fd, void *buf, size_t count);
  readFile = read(fd, buf,BUF_SIZE);

  for(int i = 0; i<readFile; i++)
  {
    if(buf[i] == 10)
    {
      n_line++;		//finding how many lines there in mainfile 
    }
  }

  divide = n_line/2;	

  for(int i = 0; i < readFile; i++)
  {
    bytes++;		//finding how many bytes want in splitfile1
    if(buf[i] == 10 )
    {
      n_line1++;
    }
    if(n_line1 == divide)
    {
      break;
    }
  }

 // int open(const char *pathname, int flags, mode_t mode);
  fd1 = open(argv[2], openFlag1, filePerm);

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile = write(fd1, buf, bytes);

  //off_t lseek(int fd, off_t offset, int whence);
  setcur = lseek(fd, bytes, SEEK_SET);

  //ssize_t write(int fd, const void *buf, size_t count);
  readFile1 = read(fd, buf1,BUF_SIZE);

  // int open(const char *pathname, int flags, mode_t mode);
  fd2 = open(argv[3], openFlag2, filePerm);

  //ssize_t write(int fd, const void *buf, size_t count);
  writeFile1 = write(fd2, buf1,readFile1);

  //int close(int fd);
  close(fd);
  close(fd1);
  close(fd2);
  exit(0);
}
