/***************************************************************************************************************/
/*   Author         : Thirumoorthy P                                                                           */
/*   Date           : 21/12/2023                                                                               */
/*   File name      : own_grp_homeTmpl.c                                                                       */
/*   Description    : change owner and group in home directory template                                        */
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
   int ret_dir, i, ret, cd_ret, fd_vrc, fd_brc, openfd, openfd1, chown_ret, chown_ret1, chown_ret2, own_id, grp_id;
   ssize_t readbytes, readbytes1, writebytes, writebytes1;
   mode_t old_umask, new_umask;
   char buf[BUF_SIZE];

   ret = EXIT_SUCCESS;
   own_id = atoi(argv[10]);//srting to integer convertion of owner id
   grp_id = atoi(argv[11]);//string to integer covertion of group id

   //mode_t umask(mode_t mask);
   old_umask = umask(0777&(~0000));
   new_umask = umask(old_umask);
   //using loop creating directoy 
   for(i = 1; i < 10 ;i++)
   {
      //int mkdir(const char *pathname, mode_t mode);
      ret_dir = mkdir(argv[i], new_umask);
      if(ret_dir == -1)
      {
	 ret = errno;
	 perror("mkdir: cannot creat directory:");
	 exit(-1);
      }
      //int chown(const char *pathname, uid_t owner, gid_t group);
      chown_ret = chown(argv[i], own_id, grp_id);
      if(chown_ret == -1)
      {
	 ret = errno;
	 perror("chown:cannot change owner and group id:");
	 exit(-ret);
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
   fd_vrc = open(".vimrc", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
   if(fd_vrc == -1)
   {
      ret = errno;
      perror("open:cannot creat a vimrc file");
      exit(-ret);
   }
   //int chown(const char *pathname, uid_t owner, gid_t group);
   chown_ret1 = chown(".vimrc", own_id, grp_id);
   if(chown_ret1 == -1)
   {
      ret = errno;
      perror("chown:cannot change owner and group id in vimrc:");
      goto close_fd;
      exit(-ret);
   }
   // int open(const char *pathname, int flags, mode_t mode);
   fd_brc = open(".bashrc", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
   if(fd_vrc == -1)
   {
      ret = errno;
      perror("open:cannot creat a bashrc file");
      goto close_fd;
      exit(-ret);
   }
   //int chown(const char *pathname, uid_t owner, gid_t group);
   chown_ret2 = chown(".bashrc", own_id, grp_id);
   if(chown_ret2 == -1)
   {
      ret = errno;
      perror("chown:cannot change owner and group id in bashrc:");
      goto close_fd1;
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
