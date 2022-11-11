#include "lcd.h"



//显示屏初始化
void lcd_init(){
	//打开屏幕文件
	fd_lcd = open("/dev/fb0", O_RDWR);
	if(fd_lcd == -1){
		perror("open /dev/fb0 failed");
	}

	//内存地址映射
	p = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE, MAP_SHARED, fd_lcd, 0);
	
	//初始化屏幕颜色
	int color = 0x00FFFFFF;
	for(int i = 479; i >=0; i--){
		for(int j = 0; j < 800; j++){
			draw_point(i, j, color);
		}
	}
}

//画点
void draw_point(int i, int j, int color){
	if(i >= 0 && i < 480 && j >= 0 && j < 800){
		*(p + i * 800 + j) = color;
	}
}

//解初始化
void lcd_uninit(){
	//解除映射
	int m = munmap(p, 800*480*4);
	if(m == -1){
		perror("munmap failed");
	}
	//关闭文件
	int c = close(fd_lcd);
	if(c == -1){
		perror("close /dev/fb0 failed");
	}
}










