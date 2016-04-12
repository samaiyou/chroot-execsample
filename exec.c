#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define ENVDIR "/opt/env/101013"
#define PHP "/usr/php54/bin/php-cgi"
#define EXECNAME "php5_env"

#define MINUID 98

int main()
{
   if ( getuid() < MINUID)
   {
      fprintf(stderr, "Can't execute binary UID smaller than %d\n", MINUID);
      return 1;
   }
   if (chdir(ENVDIR) < 0)
   {
      printf("Can't chdir errno=%d\n", errno);
      return 1;
   }
   if (chroot(ENVDIR) < 0)
   {
      printf("Can't chroot errno=%d\n", errno);
      return 1;
   }
   setuid(getuid());
   setgid(getgid());
   if (execl(PHP, EXECNAME, NULL) < 0)
   {
      printf("can not execute errorno=%d\n", errno);
      return 1;
   }
   return 0;
}
