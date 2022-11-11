#ifndef __LINKLISTQUEUE_H__
#define __LINKLISTQUEUE_H__
#include<stdlib.h>
#include<stdio.h>

typedef void*  LElemType;

typedef struct LQNoed{
	LElemType data;
	struct LQNoed* next;
}LQNoed;

typedef struct QHead{
	LQNoed* front;
	LQNoed* rear;
	int num;
}QHead;

QHead* initqueue();//初始化队列
void destroyqueue(QHead* h);//销毁队列
void clearqueue(QHead* h);//清空一个队列
int queueisempty(QHead* h);//判断队列是否为空
int queuelength(QHead* h);//返回队列长度
int enqueue(QHead* h, LElemType e);//入队
int dequeue(QHead* h, LElemType* e);//出队
int gettop(QHead* h, LElemType* e);//获取队头元素
#endif