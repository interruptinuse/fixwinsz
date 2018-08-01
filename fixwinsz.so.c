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

int ioctl(int d, unsigned long rq, char *argp)
{
  static int (*ioctl_real)(int d, unsigned long rq, char *argp) = 0;
  ioctl_real = dlsym(RTLD_NEXT, "ioctl");

  int retcode = ioctl_real(d, rq, argp);

  if(rq == TIOCGWINSZ)
  {
#define WS(x) (((struct winsize*)argp)->x)
#define SET(ev,es,v,w) do                       \
{                                               \
  char *ev = getenv(es);                        \
  errno = 0;                                    \
  int v = ev != NULL ? strtol(ev, NULL, 0) : 0; \
  if(errno) v = 0;                              \
  if(v > 0 && WS(w) > v)                        \
  {                                             \
    WS(w) = v;                                  \
  }                                             \
}while(0)
    SET(cols_env, COLS_ENV, cols, ws_col);
    SET(rows_env, ROWS_ENV, rows, ws_row);
  }

  return retcode;
}
