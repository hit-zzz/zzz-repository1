#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
//#include"stdAfx.h"
#define height 28//方块高度
#define width 60//方块宽度 必须偶数



//---------------------------------------------------------
//函数声明
void GameStart();//启动画面
void GameOver();//结束画面
void draw_cube();//画框框
void initialization();//初始化最初的蛇身
void gotoxy(int x,int y);//移动坐标
void move();//决定蛇身如何移动
void p_move();//处理蛇头移动后蛇身指针的移动
void food();//产生食物
void judge_head();//判断蛇头的位置
void static_info();//静态信息，如游戏侧栏文字提示
void dynamic_info();//动态信息，如游戏得分
//---------------------------------------------------------
//全局变量
struct snake
{
	short x;
	short y;
	struct snake *next;
}*head=NULL,*scan=NULL,*pf=NULL,*pb=NULL;

int i1[5],i2[5];
int speed=250;//蛇移动的速度(毫秒)
short length=4;//初始蛇身长度
char direction='d';//蛇头方向有 w/a/s/d
short food_x,food_y,tail_x,tail_y;
short snake_xy[1024];//存储蛇身上每一个节点的坐标 供改变结构体指针坐标使用
short score=0;//游戏得分
short music=1;//吃到食物后是否响铃,默认响
//---------------------------------------------------------
//函数定义区
void initialization()//初始化最初的蛇身
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	short i;
	draw_cube();
	for(i=1;i<=length;i++)
	{
		pb=(struct snake*)malloc(sizeof(struct snake));
		pb->y=17;
		if(i==1) {
			head=scan=pf=pb;
			pb->x=30;
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			gotoxy(pb->x,pb->y);
			printf("■");
		} else {
			pb->x=pf->x-2;
			gotoxy(pb->x,pb->y);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			gotoxy(pb->x,pb->y);
			printf("■");
			pf->next=pb;
		}
		pf=pb;
		pf->next=NULL;
	}
}
void draw_cube()//画框框
{
		int x,y,maxNum; short i;
		srand((unsigned)time(NULL));
		for(i=0;i<5;i++) {
			x=rand()%(width-4);
			y=rand()%(height-4);
			while((x%2)!=0) {
				x=rand()%(height-4);
			}
			i1[i]=x;
			i2[i]=y;
			gotoxy(x,y);printf("■");
		}

	for(i=1;i<=height;i++)//画左右两列方块
	{
		gotoxy(0,i);printf("■");
		gotoxy(width,i);printf("■");
	}
	for(i=0;i<=width+1;i+=2)//画上下两行方块
	{
		gotoxy(i,0);printf("■");
		gotoxy(i,height+1);printf("■");
	}
}
void gotoxy(int x,int y) //移动坐标
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void GameStart()//游戏开始
{
    char a;
    FILE *fp;
    int i;
    if ((fp=fopen("Readme.txt","r"))==NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    while((a=fgetc(fp))!=EOF) putchar(a);
    scanf("%d",&i);
    if(i==1) {
    	draw_cube();
	} else if(i==2) {
		GameOver();
	}

	system("cls");
	PlaySound("lyy.wav",NULL, SND_FILENAME | SND_ASYNC);
	initialization();
	food();
	static_info();
	move();
}
void GameOver()//游戏结束
{
	char a;
    FILE *fp;
    int i;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	gotoxy(20,6);printf("Game Over");
	gotoxy(20,8);printf("得分:%d",score);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|
	FOREGROUND_INTENSITY);
    if ((fp=fopen("ending.txt","r"))==NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    while((a=fgetc(fp))!=EOF) putchar(a);
    scanf("%d",&i);
    if(i==3){
    	system("cls");
    	GameStart();
	}
	getch();
	exit(0);
}
void static_info()//静态信息，如游戏侧栏文字提示
{
	gotoxy(width+4,2);printf("%c %c %c %c控制",24,25,26,27);
	gotoxy(width+4,3);printf("按任意键暂停");
	gotoxy(width+4,4);printf("F1加速,F2减速");
	gotoxy(width+4,5);printf("F3开关声音");
	gotoxy(width+4,8);printf("得分:");
	gotoxy(width+4,10);printf("蛇头位置:");
	gotoxy(width+4,12);printf("食物位置:");
	gotoxy(width+4,14);printf("声音:");
	gotoxy(width+4,16);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F4:■");//红色
	gotoxy(width+4,18);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|
	FOREGROUND_INTENSITY);printf("F5:■");//黄色
	gotoxy(width+4,20);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);printf("F6:■");//绿 色
	gotoxy(width+4,22);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|
	FOREGROUND_INTENSITY);printf("F7:■");//紫色
	gotoxy(width+4,24);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|
	FOREGROUND_INTENSITY);printf("F8:■");//亮白色
	gotoxy(width+4,26);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
	printf ("F9:■");//灰色
}
void dynamic_info()//动态信息，如游戏得分
{
	gotoxy(width+9,8);printf("%d",score);
	gotoxy(width+13,10);printf("%2d,%2d",head->x,head->y);
	gotoxy(width+13,12);printf("%2d,%2d",food_x,food_y);
	gotoxy(width+9,14);music==1?printf("开"):printf("关");
}
void move()//游戏核心  怎么移动蛇身
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	short a,b;//接收上下左右键
	char key_direction='d';
	while(!kbhit())//判断是否有按键输入//蛇身移动
	{
		loop:
		//gotoxy(food_x,food_y);printf("*");
		switch(direction)
		{
			case 'w':gotoxy(scan->x,scan->y-1);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("■");p_move(); head->y=head->y-1;break;
			case 'a':gotoxy(scan->x-2,scan->y);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("■");p_move(); head->x=head->x-2;break;
			case 's':gotoxy(scan->x,scan->y+1);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("■");p_move(); head->y=head->y+1;break;
			case 'd':gotoxy(scan->x+2,scan->y);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("■");p_move(); head->x=head->x+2;
		}
		dynamic_info();
		scan=head;
		judge_head();
		Sleep(speed);
	}
	scan=head;
	a=getch();
	b=getch();
	switch(a)
	{
		case 224:switch(b)
		{
			case 72:key_direction='w';if(direction=='s')key_direction=0; break;
			case 75:key_direction='a';if(direction=='d')key_direction=0; break;
			case 80:key_direction='s';if(direction=='w')key_direction=0; break;
			case 77:key_direction='d';if(direction=='a')key_direction=0;
		}break;
		case 0:  switch(b)
		{
			case 59:speed-=20;break;
			case 60:speed+=20;break;
			case 61:music=music==1?0:1;break;
			case 62:system("color 0C");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|
			FOREGROUND_INTENSITY);break;//红色
			case 63:system("color 0E");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|
			FOREGROUND_INTENSITY);break;//黄色
			case 64:system("color 0A");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|
			FOREGROUND_INTENSITY);break;//绿色
			case 65:system("color 0D");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|
			FOREGROUND_INTENSITY);break;//紫色
			case 66:system("color 0F");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|
			FOREGROUND_RED|FOREGROUND_INTENSITY);break;//亮白色
			case 67:system("color 08");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|
			FOREGROUND_RED);//灰色
		}break;
		default: goto loop;
	}
	if(key_direction)
	direction=key_direction;
	else
	goto loop;
	goto loop;
}
void p_move()//处理蛇头移动后蛇身指针的移动
{
	short i=0;
	while(scan->next!=NULL)
	scan=scan->next;//scan最终指向蛇尾
	gotoxy(scan->x,scan->y);printf(" ");//上一个函数中，打印了蛇头，这里消去了蛇尾
	scan=head;//scan指向 原来 的蛇头位置
	while(scan->next!=NULL)//存储蛇头到蛇尾前一个节点的坐标
	{
		snake_xy[i]=scan->x;
		i++;
		snake_xy[i]=scan->y;
		i++;
		scan=scan->next;
	}
	tail_x=scan->x;
	tail_y=scan->y;//存储蛇尾坐标   为的是在吃到食物时  给这个坐标输出方块
	i=0;
	scan=head->next;
	while(scan->next!=NULL)//把存储的坐标逐个赋给蛇头打下一个节点到蛇尾
	{
		scan->x=snake_xy[i];
		i++;
		scan->y=snake_xy[i];
		i++;
		scan=scan->next;
	}
	scan->x=snake_xy[i];
	i++;
	scan->y=snake_xy[i];
}
void food()// 产生食物
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int x;
	short i = 0;
	struct snake *pfood = head;
	while (1)
	{
		srand((unsigned)time(NULL));
		do
		{
			food_x = rand() % (width - 3) + 2;
		} while ((food_x % 2) != 0);
		food_y = rand() % (height - 1) + 1;
		x=rand()%4;
		for(i=0;pfood != NULL;i++)
		{
			if (pfood->x == food_x&&pfood->y == food_y|| ((pfood->x == i1[0]) && (pfood->y == i2[0])) || ((pfood->x == i1[1]) && (pfood->y == i2[1])) ||
				((pfood->x == i1[2]) && (pfood->y == i2[2])) || ((pfood->x == i1[3]) && (pfood->y == i2[3])) || ((pfood->x == i1[4]) && (pfood->y == i2[4])))
				break;
			pfood = pfood->next;
		}
		if (i >= length)
		{
			gotoxy(food_x, food_y);
			switch (x){
		case 0:	SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_GREEN);
				printf("*");break;
		case 1:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_BLUE);
				printf("*");break;
		case 2:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
				printf("*");break;
		case 3:SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
				printf("*");
	}

			scan = head;
			break;
		}
	}


}
void judge_head()// 判断蛇头的位置
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	short i=0;
	if(head->x==0 || head->x==width || head->y==0 || head->y==height+1 ||
	((head->x==i1[0]) && (head->y==i2[0])) || ((head->x==i1[1]) && (head->y==i2[1])) ||
	((head->x==i1[2]) && (head->y==i2[2])) || ((head->x==i1[3]) && (head->y==i2[3])) || ((head->x==i1[4]) && (head->y==i2[4])))//首先判断是不是撞墙了
	GameOver();
	while(scan->next!=NULL)//判断是不是咬着自己了
	{
		if(head->x==snake_xy[i])
		if(head->y==snake_xy[++i])
		GameOver();
		else
		i++;
		else
		i+=2;
		scan=scan->next;
	}
	if(head->x==snake_xy[i])
	if(head->y==snake_xy[++i])
	GameOver();
	if(head->x==food_x && head->y==food_y)//如果吃到食物,给尾巴加上一节
	{
		//if(music)
		putchar(7);//响铃
		score+=100;
		pb=(struct snake*)malloc(sizeof(struct snake));
		pf->next=pb;
		pb->next=NULL;
		pf=pb;
		pb->x=tail_x;
		pb->y=tail_y;
		gotoxy(pb->x,pb->y);
		printf("■");
		food();
	}
	scan=head;
}

//---------------------------------------------------------
//main函数
int main()
{
	system("mode con: cols=100 lines=40");
	GameStart();
	//PlaySound("冷雨夜.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	//system("pause");
//	system("cls");
//	initialization();
//	food();
//	static_info();
//	move();
	return 0;
}
