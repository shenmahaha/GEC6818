#ifndef __WZQ_APP_H__
#define __WZQ_APP_H__

#define SIZE 15

typedef struct wzq
{
    /* data */
    int q_color; // 2 没有棋子 0黑棋  1白棋
    int pos_x;
    int pos_y;
} Wzq;

// 棋盘
extern Wzq gobang[15][15];
extern int ind[2];

// 绘画
extern int icon_app3_func();

// 画直线
extern void LCD_DrawHorizontalLine(int x_start, int x_end, int y, unsigned int color);
// 画实心圆
extern void LCD_DrawFilledCircle(int x_center, int y_center, int radius, unsigned int color);
#endif