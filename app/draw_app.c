#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <math.h>
#include "../lcd.h"
#include "../font.h"
#include "../ts.h"
#include "wzq_app.h"
// 直线
void LCD_DrawLine(int x0, int y0, int x1, int y1, unsigned int color, int thickness)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1)
    {
        // 检查是否在屏幕范围内
        if (x0 >= 0 && x0 < LCD_WIDTH && y0 >= 0 && y0 < LCD_HEIGHT)
        {
            LCD_DrawFilledCircle(x0, y0, thickness, color);
        }

        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

int icon_app2_func()
{
    // 色块
    lcd_fill(0, 0, 80, 80, RGB(0, 0, 0));        // 黑
    lcd_fill(0, 80, 80, 80, RGB(255, 255, 255)); // 白
    lcd_fill(0, 160, 80, 80, RGB(255, 0, 0));    // 红
    lcd_fill(0, 240, 80, 80, RGB(0, 255, 0));    // 绿
    lcd_fill(0, 320, 80, 80, RGB(0, 0, 255));    // 蓝
    lcd_fill(0, 400, 80, 80, RGB(255, 255, 0));  // 黄
    lcd_fill(80, 0, 4, 480, RGB(75, 75, 75));    // 边框
    // 画板
    lcd_fill(84, 0, 632, 480, getColor(255, 255, 255, 255));
    lcd_fill(716, 0, 4, 480, RGB(75, 75, 75)); // 边框
    // 工具
    lcd_draw_icon("./bmplib/eraser.bmp", 720, 32);
    lcd_draw_icon("./bmplib/empty.bmp", 720, 144);
    lcd_draw_icon("./bmplib/save.bmp", 720, 256);
    lcd_draw_icon("./bmplib/back_draw.bmp", 720, 368);
    unsigned int pen_color = RGB(0, 0, 0);
    int rt;
    struct input_event ie;
    int ts_x, ts_y, ts_sta;
    int pen_ridus = 7;
    int prev_x = -1, prev_y = -1;
    while (1)
    {
        rt = read(g_fd_ts, &ie, sizeof(ie));

        if (rt < 0)
            continue;

        // 绝对坐标值的事件
        if (ie.type == EV_ABS)
        {
            if (ie.code == ABS_X)
                ts_x = ie.value;

            if (ie.code == ABS_Y)
                ts_y = ie.value;
        }

        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
        if (ie.type == EV_KEY && ie.code == BTN_TOUCH)
        {
            ts_sta = ie.value;

            // 触摸屏点击后的释放状态
            // 色块
            if (ts_sta == 0 && ts_x >= 0 && ts_x <= 80)
            {
                pen_ridus = 7;
                if (ts_y >= 0 && ts_y < 80)
                {
                    pen_color = RGB(0, 0, 0);
                }
                if (ts_y >= 80 && ts_y < 160)
                {
                    pen_color = RGB(255, 255, 255);
                }
                if (ts_y >= 160 && ts_y < 240)
                {
                    pen_color = RGB(255, 0, 0);
                }
                if (ts_y >= 240 && ts_y < 320)
                {
                    pen_color = RGB(0, 255, 0);
                }
                if (ts_y >= 320 && ts_y < 400)
                {
                    pen_color = RGB(0, 0, 255);
                }
                if (ts_y >= 400 && ts_y < 480)
                {
                    pen_color = RGB(255, 255, 0);
                }
                continue;
            }
            // 工具栏
            if (ts_x >= 720 && ts_sta == 0)
            {
                // 橡皮差
                if (ts_y >= 32 && ts_y <= 112)
                {
                    printf("橡皮擦\n");
                    pen_color = RGB(255, 255, 255);
                    pen_ridus = 20;
                }
                // 清除
                else if (ts_y >= 144 && ts_y <= 224)
                {
                    printf("清除\n");
                    lcd_fill(84, 0, 632, 480, getColor(255, 255, 255, 255));
                }
                // 保存
                else if (ts_y >= 256 && ts_y <= 336)
                {
                    printf("保存\n");
                    if (lcd_screenshot() == 0)
                    {
                        // 保存好背景色
                        int x, y, i = 0;

                        unsigned int p[300 * 170] = {0};

                        for (y = 155; y < 325; y++)
                        {
                            for (x = 250; x < 550; x++)
                            {
                                p[i] = lcd_read_point(x, y);
                                i++;
                            }
                        }
                        lcd_fill(250, 155, 300, 170, RGB(191, 191, 191));
                        lcd_draw_string("保存成功", 296, 215, RGB(0, 0, 0), 50);
                        lcd_draw_icon("./bmplib/cancellation.bmp", 500, 155);
                        while (1)
                        {
                            rt = read(g_fd_ts, &ie, sizeof(ie));

                            if (rt < 0)
                                continue;
                            // 绝对坐标值的事件
                            if (ie.type == EV_ABS)
                            {
                                if (ie.code == ABS_X)
                                    ts_x = ie.value;

                                if (ie.code == ABS_Y)
                                    ts_y = ie.value;
                            }

                            printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
                            if (ie.type == EV_KEY && ie.code == BTN_TOUCH)
                            {
                                ts_sta = ie.value;

                                if (ts_x >= 500 && ts_x <= 548 && ts_y >= 155 && ts_y <= 203 && ts_sta == 0)
                                {
                                    // 恢复背景色
                                    int i = 0;
                                    for (y = 155; y < 325; y++)
                                    {
                                        for (x = 250; x < 550; x++)
                                        {
                                            lcd_draw_point(x, y, p[i]);
                                            i++;
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
                else if (ts_y >= 368 && ts_y <= 480)
                {
                    return 0;
                }
            }
        }

        if (ts_x >= (84 + pen_ridus) && ts_x <= (716 - pen_ridus) && ts_y > 0 && ts_y < 480 && ts_sta)
        {
            // 如果存在前一个坐标，绘制线段
            if (prev_x != -1 && prev_y != -1)
            {
                LCD_DrawLine(prev_x, prev_y, ts_x, ts_y, pen_color, pen_ridus);
            }

            // 绘制当前的点
            LCD_DrawFilledCircle(ts_x, ts_y, pen_ridus, pen_color);

            // 更新前一个坐标为当前坐标
            prev_x = ts_x;
            prev_y = ts_y;
        }
        else if (ts_sta == 0) // 手指离开屏幕时，重置前一个坐标
        {
            prev_x = -1;
            prev_y = -1;
        }
    }
}