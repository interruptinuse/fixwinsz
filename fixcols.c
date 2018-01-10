#ifndef TTY_WIDTH
# define TTY_WIDTH 80
#endif /* TTY_WIDTH */

#ifndef TIOCGWINSZ
# define TIOCGWINSZ 21523 /* NOT PORTABLE! USE get-tiocgwinsz */
#endif /* TIOCGWINSZ */

#define _GNU_SOURCE /* RTLD_NEXT */

#include <dlfcn.h>
#include <termios.h>

struct winsize {
  unsigned short ws_row;
  unsigned short ws_col;
  unsigned short ws_xpixel;
  unsigned short ws_ypixel;
};

int ioctl(int d, unsigned long rq, char *argp) {
  static int (*ioctl_real)(int d, unsigned long rq, char *argp) = 0;
  ioctl_real = dlsym(RTLD_NEXT, "ioctl");

  int retcode = ioctl_real(d, rq, argp);

  if(rq == TIOCGWINSZ) {
    ((struct winsize*)argp)->ws_col = TTY_WIDTH;
  }

  return retcode;
}
