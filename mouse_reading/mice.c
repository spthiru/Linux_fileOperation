#include <sys/types.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MOUSEFILE "/dev/input/event11" 
int main()
{
  int fd,openFlag;
  ssize_t readFile;
  ssize_t writeFile;
  struct input_event event ;

  openFlag = O_RDONLY; 

  //int open(const char *pathname, int flags);
  fd = open(MOUSEFILE, openFlag);
  if(fd == -1)
  {
    perror("open()");
  }
  else
  {
    while(1)
    {
      //ssize_t read(int fd, void *buf, size_t count);
      readFile = read (fd, &event, sizeof(event));
      if(readFile == -1)
      {
	perror("read()");
      }
      else
      {
	//ssize_t write(int fd, const void *buf, size_t count);
	writeFile = write(1, &event, readFile);

	if(event.code == 272)
	{
	  printf("left Button\n");
	}
	printf("%x %x %x %x\n",event.value,event.code,event.time,event.type);
	if(event.code == 273)
	{
	  printf("Right Button\n");
	}
      }
    }
  }
}
