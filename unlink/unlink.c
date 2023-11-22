#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
   int ret_unlink, ret;
   ret = EXIT_SUCCESS;

   //int unlink(const char *pathname);
   ret_unlink = unlink(argv[1]);
   if(ret_unlink == -1)
   {
      ret = errno;
      perror("unlink:cannot unlink a file");
      exit(-ret);
   }
}
