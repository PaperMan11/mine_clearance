#ifndef __PLAY_H__
#define __PLAY_H__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linklistqueue.h"
#include "bmp.h"
#include "touch.h"
#define M 8
#define N 8

typedef struct lattice{
	int flag;//判断是否被点过(点击过了就显示图片)
	int num;//记录格子内的数字(雷9)
	int qizi;//记录是否被插了旗子
	//坐标
	int i;
	int j;
}lattice;


void init_game(lattice arr[M][N]);//初始化布局
void add_a_lei(lattice arr[M][N]);//随机在数组中产生一个雷
void touch_lattice(lattice arr[M][N]);//点击格子
void print_arr(lattice arr[M][N]);//输出数组
void print_image(lattice arr[M][N]);//显示数组图片
void dfs(lattice arr[M][N], int i, int j);//递归显示非雷的格子,遇到数字停止
int victory(lattice arr[M][N]);//游戏胜利

#endif
