#ifndef __TS_H__
#define __TS_H__

extern int ts_open(const char *pathname);
extern int ts_close(void);
extern int ts_read(int *x, int *y, int *sta);

extern int g_fd_ts;

#endif