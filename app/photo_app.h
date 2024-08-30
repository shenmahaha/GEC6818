#ifndef __PHOTO_APP_H__
#define __PHOTO_APP_H__
extern char **get_dir_name(char *pathname, int *file_count);
// 描绘照片墙
extern void lcd_draw_photo_List(char **file_names, int file_count, int page, int page_size);
// 相册
extern int icon_app1_func();

#endif