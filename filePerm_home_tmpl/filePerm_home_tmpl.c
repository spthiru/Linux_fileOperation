/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 21/12/2023                                                                               */
/*   File name      : fileperm_home_tmpl.c                                                                     */
/*   Description    : Required file permission to file and directory in home template                          */
/***************************************************************************************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h> 

#define BUF_SIZE 1000001

int main(int argc, char *argv[])
{
   int ret_dir, i, m, ret, cd_ret, fd_vrc, fd_brc, openfd, openfd1, k, div, mod, octal=0, temp, temp1, l=0;
   ssize_t readbytes, readbytes1, writebytes, writebytes1;
   mode_t old_umask, new_umask;
   char buf[BUF_SIZE];

   ret = EXIT_SUCCESS;
   int arr[8] = {00,01,02,03,04,05,06,07};
    k = atoi(argv[10]);
    m = atoi(argv[11]);
    while(k > 0)
    {
       div = k / 10;
       mod = k % 10;
       k = div;
	  if(mod<=7 && mod>=0)
	  {
	     temp = arr[mod]<<l | octal;
	  }
	  octal = temp;
	  l = l + 3;
    }
    l = 0;
    while(m > 0)
    {
       div = m / 10;
       mod = m % 10;
       m = div;
	  if(mod<=7 && mod>=0)
	  {
	     temp1 = arr[mod]<<l | octal;
	  }
	  octal = temp1;
	  l = l + 3;
    }
    printf("directory permission : %o\n",temp);
    printf("file  permission : %o\n",octal);
   //using loop creating directoy 
   for(i = 1; i < 10 ;i++)
   {
      //int mkdir(const char *pathname, mode_t mode);
      ret_dir = mkdir(argv[i], temp);
      if(ret_dir == -1)
      {
	 ret = errno;
	 perror("mkdir: cannot creat directory:");
	 exit(-1);
      }
      if(i == 1)
      {
	 //int chdir(const char *path);
	 cd_ret = chdir(argv[1]);
	 if(cd_ret == -1)
	 {
	    ret = errno;
	    perror("chdir: cannot change directory:");
	    exit(-ret);
	 }
      }
   }
   // int open(const char *pathname, int flags, mode_t mode);
   fd_vrc = open(".vimrc", O_CREAT | O_RDWR, octal);
   if(fd_vrc == -1)
   {
      ret = errno;
      perror("open:cannot creat a vimrc file");
      exit(-ret);
   }
   // int open(const char *pathname, int flags, mode_t mode);
   fd_brc = open(".bashrc", O_CREAT | O_RDWR, octal);
   if(fd_vrc == -1)
   {
      ret = errno;
      perror("open:cannot creat a bashrc file");
      goto close_fd;
      exit(-ret);
   }
   //int open(const char *pathname, int flags);
   openfd = open("/home/spthiru/.vimrc", O_RDONLY);
   if(openfd == -1)
   {
      ret = errno;
      perror("open : cannot open the vimrc file");
      goto close_fd1;
      exit(-ret);
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes = read(openfd, buf, BUF_SIZE);
   if(readbytes == -1)
   {
      ret = errno;
      perror("read :cannot read vimrc file ");
      goto close_fd2;
      exit(-ret);
   }
   //ssize_t write(int fd, const void *buf, size_t count);
    writebytes = write(fd_vrc, buf, readbytes);
    if(writebytes == -1)
    {
       ret = errno;
       perror("write:canoot write vimrc file");
       goto close_fd2;
       exit(-ret);
    }
   //int open(const char *pathname, int flags);
   openfd1 = open("/home/spthiru/.bashrc", O_RDONLY);
   if(openfd == -1)
   {
      ret = errno;
      perror("open : cannot open the bashrc file");
      goto close_fd2;
      exit(-ret);
   }
   //ssize_t read(int fd, void *buf, size_t count);
   readbytes1 = read(openfd1, buf, BUF_SIZE);
   if(readbytes == -1)
   {
      ret = errno;
      perror("read :cannot read bashrc file ");
      goto close_fd3;
      exit(-ret);
   }
   //ssize_t write(int fd, const void *buf, size_t count);
    writebytes1 = write(fd_brc, buf, readbytes1);
    if(writebytes == -1)
    {
       ret = errno;
       perror("write:canoot write bashrc file");
       goto close_fd3;
       exit(-ret);
    }
close_fd3:
    close(fd_vrc);
    close(fd_brc);
    close(openfd);
    close(openfd1);
close_fd2:
    close(fd_vrc);
    close(fd_brc);
    close(openfd);
close_fd1:
    close(fd_vrc);
    close(fd_brc);
close_fd:
    close(fd_vrc);
}
