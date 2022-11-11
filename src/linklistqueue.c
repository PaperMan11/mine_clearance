#include"linklistqueue.h"


//初始化队列
QHead* initqueue(){
	QHead* h = malloc(sizeof(QHead));
	h->front = NULL;
	h->rear = NULL;
	h->num = 0;
	return h;
}

//销毁队列
void destroyqueue(QHead* h){
	if(h == NULL) return;
	clearqueue(h);
	free(h->front);
	free(h->rear);
	free(h);
	h == NULL;
}

//清空一个队列
void clearqueue(QHead* h){
	if(h == NULL || h->front == NULL) return;
	LQNoed* q = h->front;
	while(q){
		q = h->front;
		h->front = h->front->next;
		free(q);
	}
	h->front = h->rear = NULL;
}

//判断队列是否为空
int queueisempty(QHead* h){
	if(h == NULL || h->num == 0) return 1;
	return 0;
}

//返回队列长度
int queuelength(QHead* h){
	if(queueisempty(h) || h == NULL) return 0;
	return h->num;
}

//入队
int enqueue(QHead* h, LElemType e){
	if(h == NULL) return 0;
	LQNoed* p = malloc(sizeof(LQNoed));
	p->data = e;
	p->next = NULL;
	if(h->rear == NULL){
    	h->front = p;
		h->rear = p;
	}
	else{
		h->rear->next = p;
		h->rear = p;
	}
	h->num++;
	return 1;
}

//出队
int dequeue(QHead* h, LElemType* e){
	if(queueisempty(h)) return 0;
	*e = h->front->data;
	LQNoed* p = h->front;
	h->front = h->front->next;
	free(p);
	if(h->front == NULL) h->rear =  NULL;
	h->num--;
	return 1;
}


//获取队头元素
int gettop(QHead* h, LElemType* e){
	if(queueisempty(h)) return 0;
	*e = h->front->data;
	return 1;
}


