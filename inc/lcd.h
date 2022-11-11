#ifndef __LCD_H__
#define __LCD_H__
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>



int fd_lcd;//屏幕文件描述符
int* p;//内存地址映射


//显示屏初始化
void lcd_init();

//画点
void draw_point(int x, int y, int color);

//解初始化
void lcd_uninit();


#endif



