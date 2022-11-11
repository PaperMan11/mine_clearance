#include "bmp.h"

void show_bmp(char* bmpname, int x, int y){
	//打开bmp图片文件
	int fd_bmp = open(bmpname, O_RDWR);
	if(fd_bmp == -1){
		perror("open fd_bmp failed");
	}

	//读bmp图片文件
	//获取bmp图片文件的 宽、长、色深
	int width, heigth;
	short int depth;
	int l, r;
	//获取宽,将光标移动到表示宽度的地方
	l = lseek(fd_bmp, 0x12, SEEK_SET);
	if(l == -1){
		perror("lseek width failed");
	}
	r = read(fd_bmp, &width, 4);
	if(r != 4){
		perror("read width failed");
	}
	//获取长,将光标移动到表示长度的地方
	l = lseek(fd_bmp, 0x16, SEEK_SET);
	if(l == -1){
		perror("lseek heigth failed");
	}
	r = read(fd_bmp, &heigth, 4);
	if(r != 4){
		perror("read heigth failed");
	}
	//获取色深,将光标移动到表示色深的地方
	l = lseek(fd_bmp, 0x1C, SEEK_SET);
	if(l == -1){
		perror("lseek depth failed");
	}
	r = read(fd_bmp, &depth, 2);
	if(r != 2){
		perror("read depth failed");
	}
	//将像素点信息存入buf中
	int linebyte = 0;//一行的总字节数
	int t = 0;
	if(width * depth / 8 % 4 != 0){
		t = 4 - width * depth / 8 % 4;//一行中填充的字节数(一行中的字节数是4的倍数)
	}
	linebyte = width * depth / 8 + t;
	unsigned char buf[480*800*3] = {0};
	l = lseek(fd_bmp, 0x36, SEEK_SET);
	if(l == -1){
		perror("lseek array failed");
	}
	r = read(fd_bmp, buf, heigth*linebyte);
	if(r == -1){
		perror("write buf failed");
	}
	
	//将buf获得的bmp信息写进映射内存中去
	int num = 0;
	unsigned int a = 0;
	
	for(int i = heigth-1; i >= 0; i--){
		for(int j = 0; j < width; j++){
			//将RGB -> ARGB
			int color = a << 24 | buf[num+2] << 16 | buf[num+1] << 8 | buf[num];
			num += 3;
			draw_point(x+i, y+j, color);
		}
		num += t;//过掉一行中填充的字节
	}

	//关闭bmp文件
	int c_bmp = close(fd_bmp);
	if(c_bmp == -1){
		perror("close c_bmp failed");
	}
}


