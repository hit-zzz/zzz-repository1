#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")


int main(void)
{
    PlaySound(TEXT("music.wav"),NULL,SND_FILENAME | SND_ASYNC);
    system("pause");
    printf("hello world");
    return 0;
}
