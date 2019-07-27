#ifndef COLS_ENV
# define COLS_ENV "WINSZ_COLS"
#endif /* COLS_ENV */

#ifndef ROWS_ENV
# define ROWS_ENV "WINSZ_ROWS"
#endif /* ROWS_ENV */

#ifndef TIOCGWINSZ
# define TIOCGWINSZ 21523 /* NOT PORTABLE! USE get-tiocgwinsz */
#endif /* TIOCGWINSZ */

#define _GNU_SOURCE /* RTLD_NEXT */

#include <stdlib.h>
#include <errno.h>
#include <dlfcn.h>
#include <termios.h>

struct winsize
{
  unsigned short ws_row;
  unsigned short ws_col;
  unsigned short ws_xpixel;
  unsigned short ws_ypixel;
};

void setdim(const char *envvar, unsigned short *v)
{
  char *ev = getenv(envvar);
  errno = 0;
  unsigned short arg = ev != NULL ? (unsigned short)strtol(ev, NULL, 0) : 0;

  if(errno)
    arg = 0;

  if(arg > 0 && *v > arg)
    *v = arg;
}

int ioctl(int d, unsigned long rq, char *argp)
{
  static int (*ioctl_real)(int d, unsigned long rq, char *argp) = 0;
  ioctl_real = dlsym(RTLD_NEXT, "ioctl");

  int retcode = ioctl_real(d, rq, argp);

  if(rq == TIOCGWINSZ)
  {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
    // We cannot guarantee that the ioctl receives aligned data, so don't warn.
    setdim(COLS_ENV, &((struct winsize*)argp)->ws_col);
    setdim(ROWS_ENV, &((struct winsize*)argp)->ws_row);
#pragma GCC diagnostic pop
  }

  return retcode;
}
