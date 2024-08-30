#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "font.h"
#include "lcd.h"

char color_buf[800 * 480 * 4] = {0};

unsigned int *g_fb = NULL;

int g_fd_lcd;

font *g_font = NULL;
;

// 描点操作
void lcd_draw_point(int x, int y, unsigned int color)
{
    *(g_fb + y * 800 + x) = color;
}

// 获点操作
unsigned int lcd_read_point(int x, int y)
{
    return *(g_fb + y * 800 + x);
}

// 清屏操作
void lcd_clear(unsigned int color)
{
    int x, y;

    for (y = 479; y >= 0; y--)
    {
        for (x = 0; x < 800; x++)
        {
            // 对每个像素点进行赋值
            lcd_draw_point(x, y, color);
        }
    }
}

// 填充函数
void lcd_fill(int x, int y, int width, int height, unsigned int color)
{
    int x_s = x;
    int y_s = y;
    int x_e = x + width;
    int y_e = y + height;

    if (x_e > LCD_WIDTH)
        x_e = LCD_WIDTH;

    if (y_e > LCD_HEIGHT)
        y_e = LCD_HEIGHT;

    for (y = y_s; y < y_e; y++)
    {
        for (x = x_s; x < x_e; x++)
        {
            // 对每个像素点进行赋值
            lcd_draw_point(x, y, color);
        }
    }
}

// 位图显示
int lcd_draw_bmp(const char *pathname, int x, int y)
{

    // 打开4.bmp
    int fd_bmp = open(pathname, O_RDONLY);

    if (fd_bmp < 0)
    {
        printf("open %s fail\n", pathname);
        return -1;
    }

    // 位图文件头
    BITMAPFILEHEADER file_head;
    read(fd_bmp, &file_head, sizeof(file_head));
    printf("%s图片大小:%d bytes\n", pathname, file_head.bfSize);

    // 位图信息段，获取位图的高度、宽度、颜色深度
    BITMAPINFOHEADER info_head;
    read(fd_bmp, &info_head, sizeof(info_head));
    printf("%s图片尺寸:宽%ld 高%ld\n", pathname, info_head.biWidth, info_head.biHeight);
    printf("%s图片颜色深度:%d\n", pathname, info_head.biBitCount);

    int bmp_rgb_size = info_head.biWidth * info_head.biHeight * info_head.biBitCount / 8;

    // 定义一个变长数组
    char bmp_buf[bmp_rgb_size];

    // 读取该bmp的所有RGB的数据
    read(fd_bmp, bmp_buf, bmp_rgb_size);

    // 关闭bmp文件
    close(fd_bmp);

    // 开始显示图片
    int x_s = x;
    int y_s = y;
    int x_e = x_s + info_head.biWidth;
    int y_e = y_s + info_head.biHeight;

    int x_pos, y_pos;

    unsigned int color;
    int i = 0;

    for (y_pos = y_e - 1; y_pos >= y_s; y_pos--)
    {
        for (x_pos = x_s; x_pos < x_e; x_pos++, i += 3)
        {

            color = (bmp_buf[i + 2] << 16) | (bmp_buf[i + 1] << 8) | bmp_buf[i];
            // printf("%lu\n",sizeof(color));
            lcd_draw_point(x_pos, y_pos, color);
        }
    }

    return 0;
}

// 位图显示(可缩放图片大小)
int lcd_draw_resize_bmp(const char *pathname, int x, int y, int scale)
{

    // 打开4.bmp
    int fd_bmp = open(pathname, O_RDONLY);

    if (fd_bmp < 0)
    {
        printf("open %s fail\n", pathname);
        return -1;
    }

    // 位图文件头
    BITMAPFILEHEADER file_head;
    read(fd_bmp, &file_head, sizeof(file_head));
    printf("%s图片大小:%d bytes\n", pathname, file_head.bfSize);

    // 位图信息段，获取位图的高度、宽度、颜色深度
    BITMAPINFOHEADER info_head;
    read(fd_bmp, &info_head, sizeof(info_head));
    printf("%s图片尺寸:宽%ld 高%ld\n", pathname, info_head.biWidth, info_head.biHeight);
    printf("%s图片颜色深度:%d\n", pathname, info_head.biBitCount);

    // 计算缩小后的图像尺寸
    int new_width = info_head.biWidth / scale;
    int new_height = info_head.biHeight / scale;

    int bmp_rgb_size = info_head.biWidth * info_head.biHeight * info_head.biBitCount / 8;
    int new_size = new_width * new_height * info_head.biBitCount / 8;

    int row_size = (info_head.biWidth * info_head.biBitCount + 31) / 32 * 4;
    int new_row_size = (new_width * info_head.biBitCount + 31) / 32 * 4;

    // 定义一个变长数组
    char bmp_buf[bmp_rgb_size];
    char new_pixel_data[new_size];
    // 读取该bmp的所有RGB的数据
    read(fd_bmp, bmp_buf, bmp_rgb_size);

    // 缩小图像
    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            int src_x = x * scale;
            int src_y = y * scale;
            // 简单取最邻近像素值
            new_pixel_data[y * new_row_size + x * 3] = bmp_buf[src_y * row_size + src_x * 3];
            new_pixel_data[y * new_row_size + x * 3 + 1] = bmp_buf[src_y * row_size + src_x * 3 + 1];
            new_pixel_data[y * new_row_size + x * 3 + 2] = bmp_buf[src_y * row_size + src_x * 3 + 2];
        }
    }

    // 关闭bmp文件
    close(fd_bmp);

    // 开始显示图片
    int x_s = x;
    int y_s = y;
    int x_e = x_s + new_width;
    int y_e = y_s + new_height;

    int x_pos, y_pos;

    unsigned int color;
    int i = 0;

    for (y_pos = y_e - 1; y_pos >= y_s; y_pos--)
    {
        for (x_pos = x_s; x_pos < x_e; x_pos++, i += 3)
        {

            color = (new_pixel_data[i + 2] << 16) | (new_pixel_data[i + 1] << 8) | new_pixel_data[i];
            // printf("%lu\n",sizeof(color));
            lcd_draw_point(x_pos, y_pos, color);
        }
    }

    return 0;
}

// 位图显示(按照任意大小展示图片)
int lcd_draw_bmp_size(const char *pathname, int x, int y, int new_width, int new_height)
{

    // 打开4.bmp
    int fd_bmp = open(pathname, O_RDONLY);

    if (fd_bmp < 0)
    {
        printf("open %s fail\n", pathname);
        return -1;
    }

    // 位图文件头
    BITMAPFILEHEADER file_head;
    read(fd_bmp, &file_head, sizeof(file_head));
    printf("%s图片大小:%d bytes\n", pathname, file_head.bfSize);

    // 位图信息段，获取位图的高度、宽度、颜色深度
    BITMAPINFOHEADER info_head;
    read(fd_bmp, &info_head, sizeof(info_head));
    printf("%s图片尺寸:宽%ld 高%ld\n", pathname, info_head.biWidth, info_head.biHeight);
    printf("%s图片颜色深度:%d\n", pathname, info_head.biBitCount);

    int bmp_rgb_size = info_head.biWidth * info_head.biHeight * info_head.biBitCount / 8;

    // 定义一个变长数组
    char bmp_buf[bmp_rgb_size];
    unsigned char *new_img_data = (unsigned char *)malloc(new_width * new_height * 3);
    // 读取该bmp的所有RGB的数据
    read(fd_bmp, bmp_buf, bmp_rgb_size);
    // 最邻近插值缩放算法
    for (int y = 0; y < new_height; y++)
    {
        for (int x = 0; x < new_width; x++)
        {
            // 计算对应的原图像素
            int src_x = x * info_head.biWidth / new_width;
            int src_y = y * info_head.biHeight / new_height;
            for (int c = 0; c < 3; c++)
            {
                new_img_data[(y * new_width + x) * 3 + c] =
                    bmp_buf[(src_y * info_head.biWidth + src_x) * 3 + c];
            }
        }
    }
    // 关闭bmp文件
    close(fd_bmp);

    // 开始显示图片
    int x_s = x;
    int y_s = y;
    int x_e = x_s + new_width;
    int y_e = y_s + new_height;

    int x_pos, y_pos;

    unsigned int color;
    int i = 0;

    for (y_pos = y_e - 1; y_pos >= y_s; y_pos--)
    {
        for (x_pos = x_s; x_pos < x_e; x_pos++, i += 3)
        {

            color = (new_img_data[i + 2] << 16) | (new_img_data[i + 1] << 8) | new_img_data[i];
            // printf("%lu\n",sizeof(color));
            lcd_draw_point(x_pos, y_pos, color);
        }
    }

    return 0;
}

int lcd_draw_icon(const char *pathname, int x, int y)
{

    int fd_bmp = open(pathname, O_RDONLY);

    if (fd_bmp < 0)
    {
        printf("open %s fail\n", pathname);
        return -1;
    }

    // 位图文件头
    BITMAPFILEHEADER file_head;
    read(fd_bmp, &file_head, sizeof(file_head));
    printf("%s图片大小:%d bytes\n", pathname, file_head.bfSize);

    // 位图信息段，获取位图的高度、宽度、颜色深度
    BITMAPINFOHEADER info_head;
    read(fd_bmp, &info_head, sizeof(info_head));
    printf("%s图片尺寸:宽%ld 高%ld\n", pathname, info_head.biWidth, info_head.biHeight);
    printf("%s图片颜色深度:%d\n", pathname, info_head.biBitCount);

    int bmp_rgb_size = info_head.biWidth * info_head.biHeight * info_head.biBitCount / 8;

    // 定义一个变长数组
    char bmp_buf[bmp_rgb_size];

    // 读取该bmp的所有RGB的数据
    read(fd_bmp, bmp_buf, bmp_rgb_size);

    // 关闭bmp文件
    close(fd_bmp);

    // 开始显示图片
    int x_s = x;
    int y_s = y;
    int x_e = x_s + info_head.biWidth;
    int y_e = y_s + info_head.biHeight;

    int x_pos, y_pos;

    unsigned int color;
    int i = 0;

    for (y_pos = y_e - 1; y_pos >= y_s; y_pos--)
    {
        for (x_pos = x_s; x_pos < x_e; x_pos++, i += 3)
        {

            color = (bmp_buf[i + 2] << 16) | (bmp_buf[i + 1] << 8) | bmp_buf[i];

            if (color == 16777215)
                continue;

            lcd_draw_point(x_pos, y_pos, color);
        }
    }

    return 0;
}

int lcd_screenshot()
{

    unsigned char *pixelData = malloc(632 * 480 * 3);
    if (!pixelData)
    {
        printf("无法分配内存\n");
        return 1;
    }
    int i = 0;
    for (int y = 0; y < 480; y++)
    {
        for (int x = 84; x < 716; x++, i += 3)
        {
            pixelData[i] = (*(g_fb + y * 800 + x) >> 16) & 0xFF;
            pixelData[i + 1] = (*(g_fb + y * 800 + x) >> 8) & 0xFF;
            pixelData[i + 2] = (*(g_fb + y * 800 + x)) & 0xFF;
        }
    }

    time_t timestamp = time(NULL);
    char time[20];
    sprintf(time, "%ld", timestamp);
    char str[20] = "./photolib/";
    char *filename = strcat(strcat(str, time), ".bmp");
    printf("%s\n", filename);
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("文件%s创建失败!\n", filename);
        return -1;
    }
    // 填写bmp文件头
// 计算总文件大小
#if 1
    int paddingSize = (4 - (632 * 3) % 4) % 4; // 每行填充字节数，使行字节数为4的倍数
    int rowSize = 632 * 3 + paddingSize;       // 每行的实际字节数
    int dataSize = rowSize * 480;              // 图像数据的总大小

    // 设置文件头
    BITMAPFILEHEADER fileHeader;
    fileHeader.bfType = 0x4D42; // 'BM'
    fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dataSize;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // 设置信息头
    BITMAPINFOHEADER infoHeader;
    infoHeader.biSize = sizeof(BITMAPINFOHEADER);
    infoHeader.biWidth = 632;
    infoHeader.biHeight = 480;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = 24;   // 每个像素24位（RGB）
    infoHeader.biCompression = 0; // 不压缩
    infoHeader.biSizeImage = dataSize;
    infoHeader.biXPelsPerMeter = 2835; // 72 DPI
    infoHeader.biYPelsPerMeter = 2835; // 72 DPI
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;

    // 写入文件头
    fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    // 写入信息头
    fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

    int padding[3] = {0, 0, 0};
    for (int y = 480 - 1; y >= 0; y--)
    {
        fwrite(pixelData + (y * 632 * 3), 3, 632, fp);
        fwrite(padding, 1, paddingSize, fp);
    }
    fclose(fp);
    free(pixelData);
    printf("BMP文件已写入: %s\n", filename);
    return 0;
#endif
}

int lcd_font_select(const char *pathname)
{
    if (pathname == NULL)
    {
        printf("字体路径参数为NULL\n");

        return -1;
    }

    if (access(pathname, F_OK) == -1)
    {
        printf("%s 不存在\n", pathname);

        return -1;
    }

    // 若以前加载过字体，卸载字体
    if (g_font)
    {
        fontUnload(g_font);
        g_font = NULL;
    }

    // 加载字体
    g_font = fontLoad((char *)pathname);

    if (g_font == NULL)
    {
        printf("加载 %s 失败\n", pathname);

        return -1;
    }

    return 0;
}

int is_utf8_chinese(char ch)
{
    return (ch & 0xE0) == 0xE0; // 判断是否是UTF-8中文字符的第一个字节
}

int is_utf8_english(char ch)
{
    return (ch & 0x80) == 0x00; // 判断是否是UTF-8英文字符的字节
}

int utf8_strlen(const char *str, unsigned int *cn_total, unsigned int *en_total)
{
    int len = 0;
    int i = 0;

    while (str[i] != '\0')
    {
        if (is_utf8_chinese(str[i]))
        {
            len += 3; // 中文字符占三个字节
            i += 3;
            (*cn_total)++;
        }
        else if (is_utf8_english(str[i]))
        {
            len++; // 英文字符占一个字节
            i++;
            (*en_total)++;
        }
    }

    return len;
}

int lcd_draw_string(const char *str, int x, int y, unsigned int color, unsigned int font_size)
{
    if (g_font == NULL)
    {
        printf("目前还没有加载字体，无法显示...\n");
        return -1;
    }

    unsigned int cn_total = 0, en_total = 0;

    // 获取汉字数量、英文及符号等数量
    int len = utf8_strlen(str, &cn_total, &en_total);
    printf("[lcd_draw_string] len = %d\n", len);
    printf("[lcd_draw_string] cn_total = %d, en_total=%d\n", cn_total, en_total);

    // 字体大小的设置
    fontSetSize(g_font, font_size);

    unsigned int bitmap_draw_board_width = cn_total * font_size + en_total * font_size / 2;
    unsigned int bitmap_draw_board_height = font_size;

    printf("[lcd_draw_string] bitmap_draw_board_width=%d\n", bitmap_draw_board_width);
    printf("[lcd_draw_string] bitmap_draw_board_height=%d\n", bitmap_draw_board_height);

    // 创建一个画板（点阵图）
    // 画板宽、高，色深32位色即4字节
    bitmap *bm = createBitmap(bitmap_draw_board_width,
                              bitmap_draw_board_height,
                              4);

    // 设置画板底色
    int bm_x_s = x, bm_y_s = y;
    int bm_x_e = x + bitmap_draw_board_width;
    int bm_y_e = y + bitmap_draw_board_height;
    int bm_x, bm_y;

    unsigned int *p = (unsigned int *)bm->map;

    // 获取指定区域的颜色块

    for (bm_y = bm_y_s; bm_y < bm_y_e; bm_y++)
    {
        for (bm_x = bm_x_s; bm_x < bm_x_e; bm_x++)
        {
            *p = lcd_read_point(bm_x, bm_y);

            p++;
        }
    }

    // 将字体写到点阵图上
    // f:操作的字库
    // 0,0:字体在画板中的起始位置
    // str:显示的内容
    // getColor(0,100,100,100):字体颜色
    // 默认为0
    fontPrint(g_font, bm, 0, 0, (char *)str, color, 0);

    // 把字体框输出到LCD屏幕上
    // g_fb:mmap后内存映射首地址
    // x,y:画板显示的起始位置
    // bm:画板
    show_font_to_lcd(g_fb, x, y, bm);

    // 销毁画板
    destroyBitmap(bm);

    return 0;
}

int lcd_open(const char *pathname)
{
    // 打开/dev/fb0
    int g_fd_lcd = open(pathname, O_RDWR);

    if (g_fd_lcd < 0)
    {
        printf("open %s fail\n", pathname);
        return -1;
    }

    // 将设备文件/dev/fb0映射到内存
    g_fb = mmap(NULL,                   // 映射区的起始地址由系统自动分配
                800 * 480 * 4,          // 映射内存的大小，往往填写文件的大小
                PROT_READ | PROT_WRITE, // 映射区的保护形式，当前是可读可写
                MAP_SHARED,             // 共享，把映射内存的数据同步到文件
                g_fd_lcd,               // 映射的文件描述符
                0);                     // 文件的偏移量，0就不需要进行的偏移

    if (g_fb == MAP_FAILED)
    {
        printf("mmap fail\n");
        return -1;
    }

    return 0;
}

int lcd_close(void)
{
    if (g_fd_lcd > 0)
        close(g_fd_lcd);

    // 解除内存映射
    if (g_fb)
    {
        munmap(g_fb, 800 * 480 * 4);
        g_fb = NULL;
    }

    // 若以前加载过字体，卸载字体
    if (g_font)
    {
        fontUnload(g_font);
        g_font = NULL;
    }

    return 0;
}
