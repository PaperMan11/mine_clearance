#include "play.h"

//初始化布局
void init_game(lattice arr[M][N]){
	//初始化数组
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			lattice x = {0, 0, 0, i, j};
			arr[i][j] = x;
		}
	}
	
	//初始化八个雷
	for(int i = 0; i < 8; i++){
		add_a_lei(arr);
	}

	//初始化布局(层次遍历的方式)
	//1、将所有的雷入队
	QHead* que = initqueue();
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			if(arr[i][j].num == 9){
				enqueue(que, (void*)&arr[i][j]);
			}
		}
	}
	//2、初始化(层次遍历)
	int dir[9] = {1, 0, -1, 0, 1, 1, -1, -1, 1};//记录一个格子的八个方向
	while(!queueisempty(que)){
		lattice* e = NULL;
		dequeue(que, (void*)&e);//出队
		for(int x = 0; x < 8; x++){
			int x1 = e->i + dir[x];
			int y1 = e->j + dir[x+1];
			if(x1 < 0 || x1 >= M || y1 < 0 || y1 >= N) continue;//越界了
			//非9的元素+1
			arr[x1][y1].num = arr[x1][y1].num == 9 ? arr[x1][y1].num : arr[x1][y1].num+1;
		}	
	}
}

//随机在数组中产生一个雷
void add_a_lei(lattice arr[M][N]){
	int a[64] = {0}; // 用于记录没有雷的坐标
	int count = 0;
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			if(arr[i][j].num == 0){
				a[count++] = i*8 + j;
			}
		}
	}
	srand((unsigned)time(NULL));
	int x = rand() % count;
	arr[a[x]/8][a[x]%8].num = 9; 
}


//点击格子(玩游戏)
void touch_lattice(lattice arr[M][N]){
	lcd_init();//屏幕初始化
	TcInit();//触摸屏初始化
	int x, y;
	int flag_q = 0;//判断是否插旗
	int flag_w = 0;
	//显示按钮
	show_bmp("button1.bmp", 80, 540);
	show_bmp("button2.bmp", 240, 540);
	while(1){
		print_arr(arr);//显示字符数组
		printf("---------------------\n");
		print_image(arr);//显示图片数组
		if(victory(arr)){
			flag_w = 1;
			break;
		}
		TcEvent(&x, &y);

		//判断是哪个按钮
		if(x >= 700 && x < 950 && y >= 100 && y < 250) flag_q = 1;
		else if(x >= 700 && x < 950 && y >= 300 && y < 450) flag_q = 0;
		if(x >= 616) continue;

		if(flag_q){//插旗
			if(arr[y/75][x/77].qizi == 0) arr[y/75][x/77].qizi = 1;
			else arr[y/75][x/77].qizi = 0;
		}
		else{//点击
			if(arr[y/75][x/77].qizi == 0){//只能点击没插旗子的格子
				if(arr[y/75][x/77].num == 0){
					dfs(arr, y/75, x/77);
				}
				else if(arr[y/75][x/77].num == 9){
					arr[y/75][x/77].flag = 1;
					show_bmp("9.bmp", y/75*60, x/77*60);
					break;
				}
				else{
					arr[y/75][x/77].flag = 1;
				}
			}
		}
		
	}
	if(flag_w) show_bmp("victory.bmp", 0, 0);//赢了
	else{//输了
		for(int i = 0; i < M; i++){
			for(int j = 0; j < N; j++){
				if(arr[i][j].num == 9 && arr[i][j].flag == 0){
					show_bmp("lei2.bmp", 60*i, 60*j); // 输了后显示所有的雷
				}
			}
		}
	}
	lcd_uninit();
	TcInit();
}

//输出数组
void print_arr(lattice arr[M][N]){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			printf("%d ", arr[i][j].num);
		}
		printf("\n");
	}
}

//显示数组图片
void print_image(lattice arr[M][N]){
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			if(arr[i][j].flag == 0){//没被点击的图片
				if(arr[i][j].qizi == 1) show_bmp("qizi.bmp", 60*i, 60*j);
				else show_bmp("back.bmp", 60*i, 60*j);
			}
			else if(arr[i][j].flag == 1){//被点击过的图片
				char a[32] = {0};
				sprintf(a, "%d.bmp", arr[i][j].num);
				show_bmp(a, 60*i, 60*j);
			}
		}
	}
}


//递归显示非雷的空格格子,遇到数字停止
void dfs(lattice arr[M][N], int i, int j){
	if(i < 0 || i >= M || j < 0 || j >= N || arr[i][j].flag || arr[i][j].qizi) return;
	if(arr[i][j].num != 0){//遇到数字停止
		arr[i][j].flag = 1;
		return;
	}
	arr[i][j].flag = 1;
	//八个方向深度搜索
	dfs(arr, i+1, j);
	dfs(arr, i-1, j);
	dfs(arr, i, j+1);
	dfs(arr, i, j-1);
	dfs(arr, i+1, j+1);
	dfs(arr, i+1, j-1);
	dfs(arr, i-1, j+1);
	dfs(arr, i-1, j-1);
}

//游戏胜利
int victory(lattice arr[M][N]){
	int flag_num = 0;
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			if(arr[i][j].num != 9 && arr[i][j].flag == 1){
				flag_num++;
			}
		}
	}
	return flag_num == 56 ? 1 : 0;
}



