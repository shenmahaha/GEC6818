#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h> //mmap
#include <linux/input.h>
#include <string.h>
#include <pthread.h>

int g_fd_ts;

int ts_open(const char *pathname)
{

    g_fd_ts = open(pathname,O_RDONLY);

    if(g_fd_ts < 0)
    {
        perror("open");
        return -1;
    }

    return 0;
}

int ts_close(void)
{
    if(g_fd_ts)
    {
        close(g_fd_ts);
    }

    return 0;
}

int ts_read(int *x,int *y,int *sta)
{
    if(g_fd_ts < 0)
        return -1;

    struct input_event ie;

    while(1)
    {
        read(g_fd_ts,&ie,sizeof(ie));


        //绝对坐标值的事件
        if(ie.type == EV_ABS)
        {
            if(ie.code == ABS_X)
                *x=ie.value ;//黑色边框的触摸屏需要*800/1024，蓝色边框的触摸屏是不需要

            if(ie.code == ABS_Y)
                *y=ie.value;//黑色边框的触摸屏需要*800/1024，蓝色边框的触摸屏是不需要
        }

        //模拟按键的事件
        if(ie.type == EV_KEY && ie.code == BTN_TOUCH)
        {
            *sta=ie.value;

            break;
        }

    }

    return 0;

}