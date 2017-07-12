#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
//#include"stdAfx.h"
#define height 28//����߶�
#define width 60//������ ����ż��



//---------------------------------------------------------
//��������
void GameStart();//��������
void GameOver();//��������
void draw_cube();//�����
void initialization();//��ʼ�����������
void gotoxy(int x,int y);//�ƶ�����
void move();//������������ƶ�
void p_move();//������ͷ�ƶ�������ָ����ƶ�
void food();//����ʳ��
void judge_head();//�ж���ͷ��λ��
void static_info();//��̬��Ϣ������Ϸ����������ʾ
void dynamic_info();//��̬��Ϣ������Ϸ�÷�
//---------------------------------------------------------
//ȫ�ֱ���
struct snake
{
	short x;
	short y;
	struct snake *next;
}*head=NULL,*scan=NULL,*pf=NULL,*pb=NULL;

int i1[5],i2[5];
int speed=250;//���ƶ����ٶ�(����)
short length=4;//��ʼ������
char direction='d';//��ͷ������ w/a/s/d
short food_x,food_y,tail_x,tail_y;
short snake_xy[1024];//�洢������ÿһ���ڵ������ ���ı�ṹ��ָ������ʹ��
short score=0;//��Ϸ�÷�
short music=1;//�Ե�ʳ����Ƿ�����,Ĭ����
//---------------------------------------------------------
//����������
void initialization()//��ʼ�����������
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
			printf("��");
		} else {
			pb->x=pf->x-2;
			gotoxy(pb->x,pb->y);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			gotoxy(pb->x,pb->y);
			printf("��");
			pf->next=pb;
		}
		pf=pb;
		pf->next=NULL;
	}
}
void draw_cube()//�����
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
			gotoxy(x,y);printf("��");
		}

	for(i=1;i<=height;i++)//���������з���
	{
		gotoxy(0,i);printf("��");
		gotoxy(width,i);printf("��");
	}
	for(i=0;i<=width+1;i+=2)//���������з���
	{
		gotoxy(i,0);printf("��");
		gotoxy(i,height+1);printf("��");
	}
}
void gotoxy(int x,int y) //�ƶ�����
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void GameStart()//��Ϸ��ʼ
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
void GameOver()//��Ϸ����
{
	char a;
    FILE *fp;
    int i;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	gotoxy(20,6);printf("Game Over");
	gotoxy(20,8);printf("�÷�:%d",score);

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
void static_info()//��̬��Ϣ������Ϸ����������ʾ
{
	gotoxy(width+4,2);printf("%c %c %c %c����",24,25,26,27);
	gotoxy(width+4,3);printf("���������ͣ");
	gotoxy(width+4,4);printf("F1����,F2����");
	gotoxy(width+4,5);printf("F3��������");
	gotoxy(width+4,8);printf("�÷�:");
	gotoxy(width+4,10);printf("��ͷλ��:");
	gotoxy(width+4,12);printf("ʳ��λ��:");
	gotoxy(width+4,14);printf("����:");
	gotoxy(width+4,16);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED|FOREGROUND_INTENSITY);printf("F4:��");//��ɫ
	gotoxy(width+4,18);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|
	FOREGROUND_INTENSITY);printf("F5:��");//��ɫ
	gotoxy(width+4,20);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_INTENSITY);printf("F6:��");//�� ɫ
	gotoxy(width+4,22);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|
	FOREGROUND_INTENSITY);printf("F7:��");//��ɫ
	gotoxy(width+4,24);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED|
	FOREGROUND_INTENSITY);printf("F8:��");//����ɫ
	gotoxy(width+4,26);SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
	printf ("F9:��");//��ɫ
}
void dynamic_info()//��̬��Ϣ������Ϸ�÷�
{
	gotoxy(width+9,8);printf("%d",score);
	gotoxy(width+13,10);printf("%2d,%2d",head->x,head->y);
	gotoxy(width+13,12);printf("%2d,%2d",food_x,food_y);
	gotoxy(width+9,14);music==1?printf("��"):printf("��");
}
void move()//��Ϸ����  ��ô�ƶ�����
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	short a,b;//�����������Ҽ�
	char key_direction='d';
	while(!kbhit())//�ж��Ƿ��а�������//�����ƶ�
	{
		loop:
		//gotoxy(food_x,food_y);printf("*");
		switch(direction)
		{
			case 'w':gotoxy(scan->x,scan->y-1);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("��");p_move(); head->y=head->y-1;break;
			case 'a':gotoxy(scan->x-2,scan->y);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("��");p_move(); head->x=head->x-2;break;
			case 's':gotoxy(scan->x,scan->y+1);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("��");p_move(); head->y=head->y+1;break;
			case 'd':gotoxy(scan->x+2,scan->y);
			SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			printf("��");p_move(); head->x=head->x+2;
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
			FOREGROUND_INTENSITY);break;//��ɫ
			case 63:system("color 0E");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_RED|
			FOREGROUND_INTENSITY);break;//��ɫ
			case 64:system("color 0A");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|
			FOREGROUND_INTENSITY);break;//��ɫ
			case 65:system("color 0D");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_RED|
			FOREGROUND_INTENSITY);break;//��ɫ
			case 66:system("color 0F");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|
			FOREGROUND_RED|FOREGROUND_INTENSITY);break;//����ɫ
			case 67:system("color 08");static_info();SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN|FOREGROUND_BLUE|
			FOREGROUND_RED);//��ɫ
		}break;
		default: goto loop;
	}
	if(key_direction)
	direction=key_direction;
	else
	goto loop;
	goto loop;
}
void p_move()//������ͷ�ƶ�������ָ����ƶ�
{
	short i=0;
	while(scan->next!=NULL)
	scan=scan->next;//scan����ָ����β
	gotoxy(scan->x,scan->y);printf(" ");//��һ�������У���ӡ����ͷ��������ȥ����β
	scan=head;//scanָ�� ԭ�� ����ͷλ��
	while(scan->next!=NULL)//�洢��ͷ����βǰһ���ڵ������
	{
		snake_xy[i]=scan->x;
		i++;
		snake_xy[i]=scan->y;
		i++;
		scan=scan->next;
	}
	tail_x=scan->x;
	tail_y=scan->y;//�洢��β����   Ϊ�����ڳԵ�ʳ��ʱ  ����������������
	i=0;
	scan=head->next;
	while(scan->next!=NULL)//�Ѵ洢���������������ͷ����һ���ڵ㵽��β
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
void food()// ����ʳ��
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
void judge_head()// �ж���ͷ��λ��
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	short i=0;
	if(head->x==0 || head->x==width || head->y==0 || head->y==height+1 ||
	((head->x==i1[0]) && (head->y==i2[0])) || ((head->x==i1[1]) && (head->y==i2[1])) ||
	((head->x==i1[2]) && (head->y==i2[2])) || ((head->x==i1[3]) && (head->y==i2[3])) || ((head->x==i1[4]) && (head->y==i2[4])))//�����ж��ǲ���ײǽ��
	GameOver();
	while(scan->next!=NULL)//�ж��ǲ���ҧ���Լ���
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
	if(head->x==food_x && head->y==food_y)//����Ե�ʳ��,��β�ͼ���һ��
	{
		//if(music)
		putchar(7);//����
		score+=100;
		pb=(struct snake*)malloc(sizeof(struct snake));
		pf->next=pb;
		pb->next=NULL;
		pf=pb;
		pb->x=tail_x;
		pb->y=tail_y;
		gotoxy(pb->x,pb->y);
		printf("��");
		food();
	}
	scan=head;
}

//---------------------------------------------------------
//main����
int main()
{
	system("mode con: cols=100 lines=40");
	GameStart();
	//PlaySound("����ҹ.wav",NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
	//system("pause");
//	system("cls");
//	initialization();
//	food();
//	static_info();
//	move();
	return 0;
}
