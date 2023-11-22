#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
   int chown_ret, gu_id, own_id, ret;
   gu_id = atoi(argv[3]);
   own_id = atoi(argv[2]);
   ret = EXIT_SUCCESS;

   //change the file owner & group id 
   //int chown(const char *pathname, uid_t owner, gid_t group);
   chown_ret = chown(argv[1], own_id, gu_id);
   if(chown_ret == -1)
   {
      ret = errno;
      perror("chown:cannot change own_id");
      exit(-ret);
   }
}
