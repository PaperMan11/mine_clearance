#include "touch.h"

//初始化触摸屏
void TcInit(){
	fd_tc = open("/dev/input/event0", O_RDWR);
	if(fd_tc == -1){
		perror("open /dev/input/even0 failed");
	}
}

//触摸滑动
/*
	@i:按下去时的横坐标
	@j:按下去时的纵坐标
*/

int TcEvent(int* i, int* j){
	//读取用户点击的信息(用一个结构体表示)
	int x_start,y_start;//第一次按下去那个点的坐标
	int x_stop,y_stop;//手抬起来的那个坐标
	int x,y;//滑动时的坐标
	struct input_event ev;
	while(1){
		int r = read(fd_tc, &ev, sizeof(ev));
		if(r != sizeof(ev)){
			perror("read failed");
			continue;
		}
		
		//触摸事件,获取手指在触摸屏上的位置
		if(ev.type == EV_ABS && ev.code == ABS_X){
			x = ev.value;
		}
		if(ev.type == EV_ABS && ev.code == ABS_Y){
			y = ev.value;
		}

		//按键事件
		if(ev.type == EV_KEY && ev.code == BTN_TOUCH){
			if(ev.value == 1){//按下
				x_start = x;
				y_start = y;
				*i = x;
				*j = y;
			}
			else if(ev.value == 0){//弹起
				x_stop = x;
				y_stop = y;
				break;
			}
		}		
	}
	
	return 0;
}





//
void TcUnit(){
	int c = close(fd_tc);
	if(c == -1){
		perror("close /dev/input/even0 failed");
	}
}

