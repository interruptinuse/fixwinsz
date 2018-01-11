#ifndef DEFAULT_COLS
# define DEFAULT_COLS 80
#endif /* DEFAULT_COLS */

#ifndef DEFAULT_ROWS
# define DEFAULT_ROWS 25
#endif /* DEFAULT_ROWS */

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
#define WS_COL (((struct winsize*)argp)->ws_col)
#define WS_ROW (((struct winsize*)argp)->ws_row)

    char *cols_env = getenv(COLS_ENV);
    errno = 0;
    int cols = cols_env != NULL ? strtol(cols_env, NULL, 0) : 0;
    if(errno) cols = 0;

    char *rows_env = getenv(ROWS_ENV);
    errno = 0;
    int rows = rows_env != NULL ? strtol(rows_env, NULL, 0) : 0;
    if(errno) cols = 0;

    if(cols > 0 && WS_COL > cols) {
      WS_COL = cols;
    }

    if(rows > 0 && WS_ROW > rows) {
      WS_ROW = rows;
    }
  }

  return retcode;
}
