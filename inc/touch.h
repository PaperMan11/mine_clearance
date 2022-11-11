#ifndef __TOUCH_H__
#define __TOUCH_H__
#include<stdio.h>
#include<linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int fd_tc;//触摸屏文件描述符

//触摸屏初始化
void TcInit();

//获取触摸屏信息
/*
	@i:按下去时的横坐标
	@j:按下去时的纵坐标
*/
int TcEvent(int* i, int* j);

//解初始化
void TcUnit();

#endif