/* 
 * (C) 2001 Uwe Ohse, <uwe@ohse.de>.
 * Placed in the public domain.
 */
/* @(#) $Id$ */
int chdir(const char *path);
int chmod(const char *, mode_t mode);
int dup2(int oldfd, int newfd);
int fchdir(int fd);
int fchmod(int fd, mode_t mode);
int fork(void);
int fsync(int fd);
int link(const char *oldpath, const char *newpath);
int pipe(int fildes[2]);
int rename(const char *oldpath, const char *newpath);
int rmdir(const char *pathname);
int send(int s, const char *msg, unsigned int len, int flags);
int symlink(const char *name1, const char *name2);
int unlink(const char *pathname);
unsigned int alarm(unsigned int seconds);
unsigned int sleep(unsigned int seconds);
