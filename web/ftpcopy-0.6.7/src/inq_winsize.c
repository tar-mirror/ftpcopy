#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sig.h"
#include "ftpcopy.h"

unsigned int window_x=80;
unsigned int window_y=24;

int 
inquire_window_size(void)
{
  const int fd=2;
#ifdef TIOCGSIZE
  struct ttysize win;
#elif defined(TIOCGWINSZ)
  struct winsize win;
#endif
#ifdef TIOCGSIZE
  if (ioctl (fd, TIOCGSIZE, &win))
    return -1;
  window_y=win.ts_lines;
  window_x=win.ts_cols;
#elif defined TIOCGWINSZ
  if (ioctl (fd, TIOCGWINSZ, &win))
    return -1;
  window_y=win.ws_row;
  window_x=win.ws_col;
#endif
  return 0;
}

static void
winch_handler(int sig)
{
  (void) sig;
  inquire_window_size();
} 

int
setup_window_size(void)
{
  if (isatty(0) && sig_winch) {
    sig_catch(sig_winch,winch_handler);
    winch_handler(27);
  } 
  return 0;
}

