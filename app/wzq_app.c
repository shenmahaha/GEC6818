#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>

#include "../lcd.h"
#include "../font.h"
#include "../ts.h"
#include "wzq_app.h"
#include "AI.h"
// 棋盘
Wzq gobang[15][15];
int ind[2] = {0};

void LCD_DrawFilledCircle(int x_center, int y_center, int radius, unsigned int color);
// 通过触摸点坐标转换成特定棋点
int get_ind_by_pos(int pos_x, int pos_y)
{

    if (pos_x >= 12 && pos_x < 50)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 0, gobang[ind[0]][ind[1]].pos_x = 29, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 50 && pos_x < 88)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 1, gobang[ind[0]][ind[1]].pos_x = 69, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 88 && pos_x < 126)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 2, gobang[ind[0]][ind[1]].pos_x = 106, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 126 && pos_x < 166)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 3, gobang[ind[0]][ind[1]].pos_x = 146, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 166 && pos_x < 207)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 4, gobang[ind[0]][ind[1]].pos_x = 186, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 207 && pos_x < 246)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 5, gobang[ind[0]][ind[1]].pos_x = 227, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 246 && pos_x < 286)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 6, gobang[ind[0]][ind[1]].pos_x = 266, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 286 && pos_x < 327)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 7, gobang[ind[0]][ind[1]].pos_x = 306, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 327 && pos_x < 365)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 8, gobang[ind[0]][ind[1]].pos_x = 347, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 365 && pos_x < 403)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 9, gobang[ind[0]][ind[1]].pos_x = 383, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 403 && pos_x < 443)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 10, gobang[ind[0]][ind[1]].pos_x = 422, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 443 && pos_x < 484)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 11, gobang[ind[0]][ind[1]].pos_x = 463, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 484 && pos_x < 524)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 12, gobang[ind[0]][ind[1]].pos_x = 504, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 524 && pos_x < 564)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 13, gobang[ind[0]][ind[1]].pos_x = 544, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else if (pos_x >= 564 && pos_x < 600)
    {
        if (pos_y >= 10 && pos_y < 40)
            ind[0] = 0, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 25;
        if (pos_y >= 40 && pos_y < 70)
            ind[0] = 1, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 55;
        if (pos_y >= 70 && pos_y < 100)
            ind[0] = 2, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 84;
        if (pos_y >= 100 && pos_y < 131)
            ind[0] = 3, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 116;
        if (pos_y >= 131 && pos_y < 161)
            ind[0] = 4, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 146;
        if (pos_y >= 161 && pos_y < 192)
            ind[0] = 5, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 176;
        if (pos_y >= 192 && pos_y < 224)
            ind[0] = 6, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 208;
        if (pos_y >= 224 && pos_y < 255)
            ind[0] = 7, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 239;
        if (pos_y >= 255 && pos_y < 284)
            ind[0] = 8, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 270;
        if (pos_y >= 284 && pos_y < 315)
            ind[0] = 9, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 299;
        if (pos_y >= 315 && pos_y < 347)
            ind[0] = 10, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 331;
        if (pos_y >= 347 && pos_y < 377)
            ind[0] = 11, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 363;
        if (pos_y >= 377 && pos_y < 407)
            ind[0] = 12, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 392;
        if (pos_y >= 407 && pos_y < 438)
            ind[0] = 13, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 422;
        if (pos_y >= 438 && pos_y < 467)
            ind[0] = 14, ind[1] = 14, gobang[ind[0]][ind[1]].pos_x = 584, gobang[ind[0]][ind[1]].pos_y = 454;
    }
    else
    {
        return -1;
    }
    return 0;
}
// 通过坐标判断落子在图中的定位
void get_pos_by_ind(int ind_x, int ind_y, int *pos_x, int *pos_y)
{
    // 定义 pos_x 对应 ind_y 的映射
    int pos_x_map[] = {29, 69, 106, 146, 186, 227, 266, 306, 347, 383, 422, 463, 504, 544, 584};
    // 定义 pos_y 对应 ind_x 的映射
    int pos_y_map[] = {25, 55, 84, 116, 146, 176, 208, 239, 270, 299, 331, 363, 392, 422, 454};

    // 根据 ind_y 获取对应的 pos_x
    if (ind_y >= 0 && ind_y < 15)
        *pos_x = pos_x_map[ind_y];
    else
        *pos_x = -1; // 如果 ind_y 超出范围，返回 -1 表示错误

    // 根据 ind_x 获取对应的 pos_y
    if (ind_x >= 0 && ind_x < 15)
        *pos_y = pos_y_map[ind_x];
    else
        *pos_y = -1; // 如果 ind_x 超出范围，返回 -1 表示错误
}
// 落子刷图 //color:0 是黑子 ，1是白子
int play_point(int pos_x, int pos_y, int color)
{
    if (get_ind_by_pos(pos_x, pos_y) != -1)
    {
        if (gobang[ind[0]][ind[1]].q_color == BLANK)
        {
            gobang[ind[0]][ind[1]].q_color = color;
            int x = gobang[ind[0]][ind[1]].pos_x;
            int y = gobang[ind[0]][ind[1]].pos_y;
            // printf("%d,%d\n",x,y);
            if (color == BLACK)
                LCD_DrawFilledCircle(x, y, 10, RGB(0, 0, 0));
            else if (color == WHITE)
                LCD_DrawFilledCircle(x, y, 10, RGB(255, 255, 255));
            return 0;
        }
        else
        {
            printf("此处已有子\n");
            return -1;
        }
    }
    else
    {
        return -1;
    }
}

// 实心圆
void LCD_DrawFilledCircle(int x, int y, int radius, unsigned int color)
{
    int i, j;
    for (i = -radius; i <= radius; i++)
    {
        for (j = -radius; j <= radius; j++)
        {
            if (i * i + j * j <= radius * radius)
            {
                int draw_x = x + i;
                int draw_y = y + j;

                // 检查是否在屏幕范围内
                if (draw_x >= 0 && draw_x < LCD_WIDTH && draw_y >= 0 && draw_y < LCD_HEIGHT)
                {
                    lcd_draw_point(draw_x, draw_y, color);
                }
            }
        }
    }
}
// 正方形边框
void LCD_Square(int x, int y, int l, unsigned int color)
{
    // 左
    for (int i = y - l; i <= y + l; i++)
    {
        lcd_draw_point(x - l, i, color);
        lcd_draw_point(x + l, i, color);
    }
    for (int i = x - l; i <= x + l; i++)
    {
        lcd_draw_point(i, y + l, color);
        lcd_draw_point(i, y - l, color);
    }
}
// 判断输赢 1:赢了  0:没赢
int is_win()
{
    int y = 0, x = 0, fs = 0, bs = 0;
    int color = gobang[ind[0]][ind[1]].q_color;
    // 往上检索
    for (int i = ind[0]; i >= 0; i--)
    {
        if (gobang[i][ind[1]].q_color == color)
            y++;
        else
            break;
    }
    // 往下检索
    for (int i = ind[0]; i < 14; i++)
    {
        if (gobang[i][ind[1]].q_color == color)

            y++;

        else
            break;
    }
    if (y > 5)
    {
        return 1;
    }
    // 往左检索
    for (int i = ind[1]; i >= 0; i--)
    {
        if (gobang[ind[0]][i].q_color == color)
            x++;
        else
            break;
    }
    // 往右检索
    for (int i = ind[1]; i < 14; i++)
    {
        if (gobang[ind[0]][i].q_color == color)
            x++;
        else
            break;
    }
    if (x > 5)
    {
        return 1;
    }
    // 往左上检索
    for (int i = ind[0], j = ind[1]; i >= 0 && j >= 0; i--, j--)
    {
        if (gobang[i][j].q_color == color)
            fs++;
        else
            break;
    }
    // 往右下检索
    for (int i = ind[0], j = ind[1]; i < 14 && j < 14; i++, j++)
    {
        if (gobang[i][j].q_color == color)
            fs++;
        else
            break;
    }
    if (fs > 5)
    {
        return 1;
    }
    // 往右上检索
    for (int i = ind[0], j = ind[1]; i >= 0 && j < 14; i--, j++)
    {
        if (gobang[i][j].q_color == color)
            bs++;
        else
            break;
    }
    // 往左下检索
    for (int i = ind[0], j = ind[1]; i < 14 && j >= 0; i++, j--)
    {
        if (gobang[i][j].q_color == color)
            bs++;
        else
            break;
    }
    if (bs > 5)
    {
        return 1;
    }
    return 0;
}
// 选择模式  0:退出  1：人机对战  2：玩家对战
int select_mode()
{
    lcd_draw_bmp("./bmplib/mode_select.bmp", 0, 0);
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
        if (ts_x >= 129 && ts_x <= 288)
        {
            if (ts_y >= 151 && ts_y <= 208)
            {
                printf("人机对战\n");
                return 1;
            }
            if (ts_y >= 251 && ts_y <= 307)
            {
                printf("玩家对战\n");
                return 2;
            }
            if (ts_y >= 345 && ts_y <= 403)
            {
                printf("退出\n");
                return 0;
            }
        }
    }
}
// 重置棋盘
void init_gobang()
{
    lcd_draw_bmp("./bmplib/gobang.bmp", 0, 0);
    memset(gobang, 0, sizeof(gobang));
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            gobang[i][j].q_color = 2;
    memset(ind, 0, sizeof(ind));
}

// 玩家对战
int wzq_pvp()
{

    unsigned int buf[800 * 480] = {0};
    int count = 0;
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
        if (count % 2 == 0)
        {
            if (count != 0)
            {
                // 还原
                int n = 0;
                for (int i = 0; i < 800; i++)
                {
                    for (int j = 0; j < 480; j++)
                    {
                        lcd_draw_point(i, j, buf[n]);
                        n++;
                    }
                }
            }

            if (play_point(ts_x, ts_y, BLACK) == 0)
            {

                // 保存
                int n = 0;
                for (int i = 0; i < 800; i++)
                {
                    for (int j = 0; j < 480; j++)
                    {
                        buf[n] = lcd_read_point(i, j);
                        n++;
                    }
                }

                LCD_Square(gobang[ind[0]][ind[1]].pos_x, gobang[ind[0]][ind[1]].pos_y, 12, RGB(255, 0, 0));
                count++;
                if (is_win())
                {
                    lcd_fill(250, 155, 300, 170, RGB(191, 191, 191));
                    lcd_draw_string("黑棋赢了", 296, 215, RGB(0, 0, 0), 50);
                    lcd_draw_icon("./bmplib/cancellation.bmp", 500, 155);
                    while (1)
                    {
                        rt = ts_read(&ts_x, &ts_y, &ts_sta);
                        if (rt < 0)
                            continue;
                        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
                        if (ts_sta)
                            continue;
                        if (ts_x >= 500 && ts_x <= 548 && ts_y >= 155 && ts_y <= 203)
                        {
                            count = 0;
                            init_gobang();
                            break;
                        }
                    }
                }
            }
        }
        else
        {
            // 还原
            int n = 0;
            for (int i = 0; i < 800; i++)
            {
                for (int j = 0; j < 480; j++)
                {
                    lcd_draw_point(i, j, buf[n]);
                    n++;
                }
            }
            if (play_point(ts_x, ts_y, WHITE) == 0)
            {

                // 保存状态

                int n = 0;
                for (int i = 0; i < 800; i++)
                {
                    for (int j = 0; j < 480; j++)
                    {
                        buf[n] = lcd_read_point(i, j);
                        n++;
                    }
                }
                LCD_Square(gobang[ind[0]][ind[1]].pos_x, gobang[ind[0]][ind[1]].pos_y, 12, RGB(255, 0, 0));
                count++;
                printf("%d\n", is_win());
                if (is_win())
                {
                    lcd_fill(250, 155, 300, 170, RGB(191, 191, 191));
                    lcd_draw_string("白棋赢了", 296, 215, RGB(0, 0, 0), 50);
                    lcd_draw_icon("./bmplib/cancellation.bmp", 500, 155);
                    while (1)
                    {
                        rt = ts_read(&ts_x, &ts_y, &ts_sta);
                        if (rt < 0)
                            continue;
                        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
                        if (ts_sta)
                            continue;
                        if (ts_x >= 500 && ts_x <= 548 && ts_y >= 155 && ts_y <= 203)
                        {
                            count = 0;
                            init_gobang();
                            break;
                        }
                    }
                }
            }
        }
        if (ts_x >= 636 && ts_x <= 774 && ts_y >= 120 && ts_y <= 180)
        {
            init_gobang();
            count = 0;
        }
        if (ts_x >= 638 && ts_x <= 774 && ts_y >= 301 && ts_y <= 361)
        {
            return 0;
        }
    }
}
// 人机对战
int wzq_pve()
{
    unsigned int buf[800 * 480] = {0};
    int count = 0;
    init_AI(); // 初始化
    while (1)
    {

        printf("第%d手\n", count + 1);

        if (count % 2 == 0)
        {

            lcd_fill(640, 390, 160, 50, RGB(255, 255, 255));
            LCD_DrawFilledCircle(645, 410, 10, RGB(0, 255, 0));
            lcd_draw_string("轮到你出棋了...", 664, 402, RGB(0, 0, 0), 20);

            int ts_x, ts_y, ts_sta;
            int rt;
            rt = ts_read(&ts_x, &ts_y, &ts_sta);
            if (rt < 0)
                continue;
            printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
            if (ts_sta)
                continue;

            if (count != 0)
            {
                // 还原
                int n = 0;
                for (int i = 0; i < 800; i++)
                {
                    for (int j = 0; j < 480; j++)
                    {
                        lcd_draw_point(i, j, buf[n]);
                        n++;
                    }
                }
            }
            if (play_point(ts_x, ts_y, BLACK) == 0)
            {
                // 保存
                int n = 0;
                for (int i = 0; i < 800; i++)
                {
                    for (int j = 0; j < 480; j++)
                    {
                        buf[n] = lcd_read_point(i, j);
                        n++;
                    }
                }
                LCD_Square(gobang[ind[0]][ind[1]].pos_x, gobang[ind[0]][ind[1]].pos_y, 12, RGB(255, 0, 0));

                count++;
                if (is_win())
                {
                    lcd_fill(620, 390, 160, 50, RGB(255, 255, 255));
                    lcd_fill(250, 155, 300, 170, RGB(191, 191, 191));
                    lcd_draw_string("你赢了", 296, 215, RGB(0, 0, 0), 50);
                    lcd_draw_icon("./bmplib/cancellation.bmp", 500, 155);
                    while (1)
                    {
                        rt = ts_read(&ts_x, &ts_y, &ts_sta);
                        if (rt < 0)
                            continue;
                        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
                        if (ts_sta)
                            continue;
                        if (ts_x >= 500 && ts_x <= 548 && ts_y >= 155 && ts_y <= 203)
                        {
                            init_gobang();
                            count = 0;
                            break;
                        }
                    }
                }
            }
            if (ts_x >= 636 && ts_x <= 774 && ts_y >= 120 && ts_y <= 180)
            {
                init_gobang();
                count = 0;
            }
            if (ts_x >= 638 && ts_x <= 774 && ts_y >= 301 && ts_y <= 361)
            {
                return 0;
            }
        }
        else
        {
            lcd_fill(640, 390, 160, 50, RGB(255, 255, 255));
            LCD_DrawFilledCircle(645, 410, 10, RGB(255, 0, 0));
            lcd_draw_string("等待电脑出棋...", 664, 402, RGB(0, 0, 0), 20);
            int x, y, pos_x, pos_y;
            // 模拟AI走一步
            negmax(WHITE, (pos){}, DEPTH, -1e9, 1e9);
            x = nxt_step.x;
            y = nxt_step.y;
            printf("AI should move to: %d, %d\n", x, y);
            // 还原
            int n = 0;
            for (int i = 0; i < 800; i++)
            {
                for (int j = 0; j < 480; j++)
                {
                    lcd_draw_point(i, j, buf[n]);
                    n++;
                }
            }
            get_pos_by_ind(x, y, &pos_x, &pos_y);

            if (pos_x != -1 && pos_y != -1)
            {
                printf("pos_x: %d, pos_y: %d\n", pos_x, pos_y);
                ind[0] = x;
                ind[1] = y;
                gobang[x][y].pos_x = pos_x;
                gobang[x][y].pos_y = pos_y;
                gobang[x][y].q_color = WHITE;
                LCD_DrawFilledCircle(pos_x, pos_y, 10, RGB(255, 255, 255));
                // 保存状态

                int n = 0;
                for (int i = 0; i < 800; i++)
                {
                    for (int j = 0; j < 480; j++)
                    {
                        buf[n] = lcd_read_point(i, j);
                        n++;
                    }
                }
                LCD_Square(gobang[ind[0]][ind[1]].pos_x, gobang[ind[0]][ind[1]].pos_y, 12, RGB(255, 0, 0));

                count++;
                if (player_win(WHITE, nxt_step))
                {
                    lcd_fill(620, 390, 160, 50, RGB(255, 255, 255));
                    while (1)
                    {
                        lcd_fill(250, 155, 300, 170, RGB(191, 191, 191));
                        lcd_draw_string("你输了", 296, 215, RGB(0, 0, 0), 50);
                        lcd_draw_icon("./bmplib/cancellation.bmp", 500, 155);
                        int ts_x, ts_y, ts_sta;
                        int rt;
                        rt = ts_read(&ts_x, &ts_y, &ts_sta);
                        if (rt < 0)
                            continue;
                        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
                        if (ts_sta)
                            continue;
                        if (ts_x >= 500 && ts_x <= 548 && ts_y >= 155 && ts_y <= 203)
                        {

                            init_gobang();
                            count = 0;
                            break;
                        }
                    }
                }
            }
            else
                printf("Invalid index\n");
        }
    }
}
int icon_app3_func()
{
    while (1)
    {
        // 选择模式
        int mode = select_mode();
        if (mode == 0)
            return 0;
        // 棋盘
        init_gobang();
        if (mode == 2)
        {
            wzq_pvp();
        }
        else if (mode == 1)
        {
            wzq_pve();
        }
    }
}