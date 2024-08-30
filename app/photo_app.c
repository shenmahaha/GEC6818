#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "../lcd.h"
#include "../font.h"
#include "../ts.h"

// 获取目录文件名字
char **get_dir_name(char *pathname, int *file_count)
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(pathname);
    if (dir == NULL)
    {
        perror("无法打开目录");
        return NULL;
    }

    // 计算目录中的文件数量
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        count++;
    }

    // 重置目录流的位置
    rewinddir(dir);

    // 分配内存
    char **file_names = malloc(count * sizeof(char *));
    if (file_names == NULL)
    {
        perror("内存分配失败");
        closedir(dir);
        return NULL;
    }

    // 将文件名存储在字符指针数组中
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        file_names[i] = strdup(entry->d_name); // 复制文件名
        if (file_names[i] == NULL)
        {
            perror("内存分配失败");
            // 释放已经分配的内存
            for (int j = 0; j < i; j++)
            {
                free(file_names[j]);
            }
            free(file_names);
            closedir(dir);
            return NULL;
        }
        i++;
    }

    closedir(dir);
    *file_count = count;
    return file_names;
}

// 描绘照片墙
void lcd_draw_photo_List(char **file_names, int file_count, int page, int page_size)
{
    lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
    int h = 97;
    for (int i = page * page_size; i < (page + 1) * page_size && i < file_count; i++)
    {

        char str[30] = "./photolib/";
        if (i % 3 == 0 && (i != 0 && i % 6 != 0))
        {
            h += 167;
        }
        lcd_draw_bmp_size(strcat(str, file_names[i]), 50 * ((i % 3) + 1) + 200 * (i % 3), h, 200, 120);
    }
}
// 相册
int icon_app1_func()
{
    int page = 0;
    int page_size = 6;
    int file_count = 0;
    int flag = 0;
    int bmpIndex = 0;
    char **file_names = get_dir_name("./photolib", &file_count);
    // 顶部
    lcd_fill(0, 0, 800, 50, getColor(38, 38, 38, 255));
    // 底部
    lcd_fill(0, 430, 800, 50, getColor(38, 38, 38, 255));
    // 主体
    lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
    // 返回图标
    lcd_draw_icon("./bmplib/back.bmp", 30, 2);
    // 上一页图标
    lcd_draw_icon("./bmplib/leftarrow.bmp", 30, 433);
    // 下一页图标
    lcd_draw_icon("./bmplib/rightarrow.bmp", 710, 433);
    // 照片墙
    //  lcd_draw_resize_bmp("./bmplib/01.bmp",30,60,4);
    lcd_draw_photo_List(file_names, file_count, page, page_size);

    while (1)
    {
        char str[100] = "./photolib/";
        int ts_x, ts_y, ts_sta;
        int rt;
        rt = ts_read(&ts_x, &ts_y, &ts_sta);
        if (rt < 0)
            continue;
        printf("ts_x:%d ts_y:%d ts_sta:%d\n", ts_x, ts_y, ts_sta);
        if (ts_sta)
            continue;
        if (ts_y >= 2 && ts_y <= 46)
        {
            // 返回
            if (ts_x >= 30 && ts_x <= 74)
            {
                printf("%d\n", flag);
                if (flag == 0)
                {
                    return 0;
                }
                else if (flag == 1)
                {
                    flag = 0;
                    // 主体
                    lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
                    // 照片墙
                    //  lcd_draw_resize_bmp("./bmplib/01.bmp",30,60,4);
                    lcd_draw_photo_List(file_names, file_count, page, page_size);
                }
            }
        }
        // 照片墙触摸点
        if (ts_y >= 97 && ts_y <= 217)
        {
            if (ts_x >= 50 && ts_x <= 250 && page * page_size < file_count)
            {

                lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
                bmpIndex = page * page_size;
                lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                flag = 1;
            }
            if (ts_x >= 300 && ts_x <= 500 && page * page_size + 1 < file_count)
            {
                lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
                bmpIndex = page * page_size + 1;
                lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                flag = 1;
            }
            if (ts_x >= 550 && ts_x <= 750 && page * page_size + 2 < file_count)
            {
                lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
                bmpIndex = page * page_size + 2;
                lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                flag = 1;
            }
        }
        if (ts_y >= 264 && ts_y <= 384)
        {
            if (ts_x >= 50 && ts_x <= 250 && page * page_size + 3 < file_count)
            {
                lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
                bmpIndex = page * page_size + 3;
                lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                flag = 1;
            }
            if (ts_x >= 300 && ts_x <= 500 && page * page_size + 4 < file_count)
            {
                lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
                bmpIndex = page * page_size + 4;
                lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                flag = 1;
            }
            if (ts_x >= 550 && ts_x <= 750 && page * page_size + 5 < file_count)
            {
                lcd_fill(0, 50, 800, 380, getColor(75, 75, 75, 255));
                bmpIndex = page * page_size + 5;
                lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                flag = 1;
            }
        }
        if (ts_y >= 433 && ts_y <= 479)
        {
            // 上一页
            if (ts_x >= 30 && ts_x <= 90)
            {
                if (flag == 0)
                {
                    if (page != 0)
                    {
                        printf("上一页\n");
                        page--;
                        lcd_draw_photo_List(file_names, file_count, page, page_size);
                    }
                }
                else if (flag == 1)
                {
                    if (bmpIndex != 0)
                    {
                        printf("上一张\n");
                        bmpIndex--;
                        lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                    }
                }
            }
            // 下一页
            if (ts_x >= 710 && ts_x <= 770)
            {
                if (flag == 0)
                {
                    printf("下一页\n");
                    page++;
                    if (page * page_size < file_count)
                    {
                        lcd_draw_photo_List(file_names, file_count, page, page_size);
                    }
                    else
                        page--;
                }
                else if (flag == 1)
                {
                    printf("下一张\n");
                    bmpIndex++;
                    if (bmpIndex < file_count)
                    {
                        lcd_draw_bmp_size(strcat(str, file_names[bmpIndex]), 83, 50, 634, 380);
                    }
                    else
                        bmpIndex--;
                }
            }
        }
    };
}