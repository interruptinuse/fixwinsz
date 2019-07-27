#include <stdio.h>
#include <sys/ioctl.h>

int main()
{
  printf("%d\n", TIOCGWINSZ);
}
