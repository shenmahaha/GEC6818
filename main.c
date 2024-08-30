#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/mman.h> //mmap
#include <linux/input.h>
#include <string.h>
#include <pthread.h>
#include <dirent.h>
#include <stdlib.h>
#include "lcd.h"
#include "font.h"
#include "ts.h"
#include "app/photo_app.h"
#include "app/draw_app.h"
#include "app/wzq_app.h"

/*菜单结构体*/
typedef struct _menu_t
{
    const char *name;       // 菜单的名字
    int (*fun)(void);       // 菜单执行的功能函数
    struct _menu_t *parent; // 父菜单
    struct _menu_t *child;  // 子菜单

} menu_t;

menu_t menu_startup; // 开机界面
menu_t menu_login;   // 登陆界面
menu_t menu_main;    // 主页面

// 开机界面图片
char *bmpList_startup[21] = {
    "./bmplib/startup_01.bmp",
    "./bmplib/startup_02.bmp",
    "./bmplib/startup_03.bmp",
    "./bmplib/startup_04.bmp",
    "./bmplib/startup_05.bmp",
    "./bmplib/startup_06.bmp",
    "./bmplib/startup_07.bmp",
    "./bmplib/startup_08.bmp",
    "./bmplib/startup_09.bmp",
    "./bmplib/startup_10.bmp",
    "./bmplib/startup_11.bmp",
    "./bmplib/startup_12.bmp",
    "./bmplib/startup_13.bmp",
    "./bmplib/startup_14.bmp",
    "./bmplib/startup_15.bmp",
    "./bmplib/startup_16.bmp",
    "./bmplib/startup_17.bmp",
    "./bmplib/startup_18.bmp",
    "./bmplib/startup_19.bmp",
    "./bmplib/startup_20.bmp",
    "./bmplib/startup_21.bmp"};

// 密码界面图片
char *bmpList_pass[7] = {
    "./bmplib/pass_0.bmp",
    "./bmplib/pass_1.bmp",
    "./bmplib/pass_2.bmp",
    "./bmplib/pass_3.bmp",
    "./bmplib/pass_4.bmp",
    "./bmplib/pass_5.bmp",
    "./bmplib/pass_6.bmp",
};
// 开机界面函数
int menu_startup_func()
{


    for (int i = 0; i < ARRAY_SIZE(bmpList_startup); i++)
    {
        lcd_draw_bmp(bmpList_startup[i], 0, 0);
        usleep(10000);
    }

    return 0;
}
// 登录函数
int menu_login_func()
{
 
    int ts_x, ts_y, ts_sta;
    int rt;
    // 密码
    char pass_correct[6] = {'1', '2', '3', '4', '5', '6'};
    char pass_input[7] = {0};
    int pass_cnt = 0;
    // 显示密码登录界面
    lcd_draw_bmp(bmpList_pass[0], 0, 0);

    while (1)
    {
        rt = ts_read(&ts_x, &ts_y, &ts_sta);
        if (rt < 0)
            continue;
        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
        // 若是按压状态，则重新新的一轮循环
        if (ts_sta)
            continue;
        // printf("pass_cnt:%d\n",pass_cnt);
        if (pass_cnt != 6)
        {
            if (ts_y >= 104 && ts_y <= 174)
            {
                if (ts_x >= 265 && ts_x <= 335)
                {
                    pass_input[pass_cnt] = '1';
                    pass_cnt++;
                }
                else if (ts_x >= 369 && ts_x <= 439)
                {
                    pass_input[pass_cnt] = '2';
                    pass_cnt++;
                }
                else if (ts_x >= 473 && ts_x <= 543)
                {
                    pass_input[pass_cnt] = '3';
                    pass_cnt++;
                }
            }
            else if (ts_y >= 193 && ts_y <= 260)
            {
                if (ts_x >= 265 && ts_x <= 335)
                {
                    pass_input[pass_cnt] = '4';
                    pass_cnt++;
                }
                else if (ts_x >= 369 && ts_x <= 439)
                {
                    pass_input[pass_cnt] = '5';
                    pass_cnt++;
                }
                else if (ts_x >= 473 && ts_x <= 543)
                {
                    pass_input[pass_cnt] = '6';
                    pass_cnt++;
                }
            }
            else if (ts_y >= 300 && ts_y <= 350)
            {
                if (ts_x >= 265 && ts_x <= 335)
                {
                    pass_input[pass_cnt] = '7';
                    pass_cnt++;
                }
                else if (ts_x >= 369 && ts_x <= 439)
                {
                    pass_input[pass_cnt] = '8';
                    pass_cnt++;
                }
                else if (ts_x >= 473 && ts_x <= 543)
                {
                    pass_input[pass_cnt] = '9';
                    pass_cnt++;
                }
            }
        }
        if (ts_y >= 371 && ts_y <= 427)
        {
            if (ts_x >= 265 && ts_x <= 444)
            {
                if (memcmp(pass_correct, pass_input, 6) == 0)
                {
                    printf("密码正确\n");
                    sleep(1);
                    break;
                }
                printf("密码错误\n");
                pass_cnt = 0;
                memset(pass_input, 0, sizeof(pass_input));
                lcd_draw_bmp(bmpList_pass[pass_cnt], 0, 0);
                lcd_draw_string("密码错误，请重新输入...", 290, 80, getColor(255, 0, 0, 255), 22);
                continue;
            }
            else if (ts_x >= 469 && ts_x <= 532)
            {
                // 密码退一位
                if (pass_cnt != 0)
                    pass_cnt--;
                pass_input[pass_cnt] = 0;
                lcd_draw_bmp(bmpList_pass[pass_cnt], 0, 0);
            }
        }

        lcd_draw_bmp(bmpList_pass[pass_cnt], 0, 0);
        printf("pass:%s\n", pass_input);
    };

    return 0;
}

// 相册
int icon_app1_func();
// 绘制桌面
void lcd_draw_home()
{
    lcd_draw_bmp("./bmplib/home.bmp", 0, 0);
    lcd_draw_icon("./bmplib/album.bmp", 40, 40);
    lcd_draw_string("相册", 69, 145, getColor(255, 255, 255, 255), 23);
    lcd_draw_icon("./bmplib/draw.bmp", 180, 40);
    lcd_draw_string("绘画", 207, 145, getColor(255, 255, 255, 255), 23);
    lcd_draw_bmp("./bmplib/wzq.bmp", 325, 45);
    lcd_draw_string("五子棋", 338, 145, getColor(255, 255, 255, 255), 23);
}
// 主菜单函数
int menu_main_func()
{
    lcd_draw_home();
    while (1)
    {
        int ts_x, ts_y, ts_sta;
        int rt;
        rt = ts_read(&ts_x, &ts_y, &ts_sta);
        if (rt < 0)
            continue;
        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
        if (ts_sta)
            continue;
        if (ts_y >= 45 && ts_y <= 135)
        {
            if (ts_x >= 45 && ts_x <= 135)
            {
                printf("启动相册\n");
                icon_app1_func();
                lcd_draw_home();
            }
            else if (ts_x >= 185 && ts_x <= 275)
            {
                printf("启动绘画\n");
                icon_app2_func();
                lcd_draw_home();
            }
            else if (ts_x >= 338 && ts_x <= 434)
            {
                printf("启动五子棋\n");
                icon_app3_func();
                lcd_draw_home();
            }
        }
    }
    return 0;
}


menu_t menu_startup = {
    .name = "开机界面",
    .fun = menu_startup_func,
    .parent = NULL,
    .child = &menu_login,
};

menu_t menu_login = {
    .name = "登录界面",
    .fun = menu_login_func,
    .parent = &menu_startup,
    .child = &menu_main,
};

menu_t menu_main = {
    .name = "主界面",
    .fun = menu_main_func,
    .parent = &menu_login,
    .child = NULL,
};
int main()
{
    menu_t *pmenu = &menu_startup;
    lcd_open("/dev/fb0");
    ts_open("/dev/input/event0");
    lcd_font_select("/usr/share/fonts/simkai.ttf");

    while (1)
    {
        if (pmenu->fun)
        {
            printf("执行%s\n", pmenu->name);

            // 如果函数运行完毕，返回值为1，则进入父菜单
            if (pmenu->fun())
            {
                pmenu = pmenu->parent;

                continue;
            }
        }

        if (pmenu->child == NULL)
        {
            printf("没有子菜单\n");
            printf("重新进入开机界面\n");
            pmenu = &menu_startup;
            continue;
        }
        // 得到子菜单
        pmenu = pmenu->child;
    }
    // 关闭LCD
    lcd_close();

    // 关闭触摸屏
    ts_close();

    return 0;
}