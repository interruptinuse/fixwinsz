#include <stdio.h>
#include <sys/ioctl.h>

int main(int argc, char **argv)
{
  printf("%d\n", TIOCGWINSZ);
}
