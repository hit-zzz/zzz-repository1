//程序名称:zzzGuessNumber
//程序作者:张子蓁
//联系方式:18846185293
//编程时间:2017 7 5
//游戏简介:由计算机随机产生一个小于maxNum的数，由玩家猜一个数ans，正确答案为answer
//游戏版本:v1.0
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void main(){
    FILE *fp1;
    FILE *fp2;
    char a;
    int j;
    int i;
    int maxNum;
    int ans=0;
    int cnt=1;
    if ((fp1=fopen("Readme.txt","r"))==NULL){
        printf("Cannot open file!\n");
        exit(0);
    }

    while((a=fgetc(fp1))!=EOF) putchar(a);
    if((fp2=fopen("file22.txt","w"))==NULL){
        printf("Cannot open file!\n");
        exit(0);
    }
    
    srand((unsigned)time(NULL));
    printf("\n");
    printf("游戏初始化loading......\n");
    fprintf(fp2,"游戏初始化loading......\n");
    do{
	    printf("设置请输入1，开始游戏请输入0，结束游戏请输入-1\n");
	    fprintf(fp2,"设置请输入1，开始游戏请输入0，结束游戏请输入-1\n");
	    scanf("%d",&i);
	    fprintf(fp2,"i=%d\n",i);
	    if(i==1){
			printf("请输入猜数范围：maxNum=");
			fprintf(fp2,"请输入猜数范围：maxNum=\n");
			scanf("%d",&maxNum);
			fprintf(fp2,"maxNum=%d\n",maxNum);
			printf("设置成功！\n");
			fprintf(fp2,"设置成功！\n");
    	}
    	if (i==-1) {
    		break;
		} 
    	printf("设置请输入1，开始游戏请输入0，结束游戏请输入-1\n");
	    fprintf(fp2,"设置请输入1，开始游戏请输入0，结束游戏请输入-1\n");
	    scanf("%d",&i);
	    fprintf(fp2,"i=%d\n",i);
    } while(i!=0 && i!=-1);
    while(i==0){
       //  printf("\n");
        printf("maxNum=%d\n",maxNum);
        fprintf(fp2,"maxNum=%d\n",maxNum);
            j=rand()%maxNum;
            printf("请玩家输入一个0~%d之间的数:\n",maxNum-1);
            fprintf(fp2,"请玩家输入一个0~%d之间的数:\n",maxNum-1);
            scanf("%d",&ans);
            fprintf(fp2,"%d\n",ans);
            while(ans!=j){
                if(ans>j){
                    printf("您猜的数大了\n");
                    fprintf(fp2,"您猜的数大了\n");
                } else{
                        printf("您猜的数小了\n");
                        fprintf(fp2,"您猜的数小了\n");
                }
                cnt++;
                printf("请玩家输入一个0~%d之间的数:\n",maxNum-1);
            	fprintf(fp2,"请玩家输入一个0~%d之间的数:\n",maxNum-1);
                scanf("%d",&ans);
                fprintf(fp2,"%d\n",ans);
            }
            printf("你用%d次就猜到了答案！！\n",cnt);
            fprintf(fp2,"你用%d次就猜到了答案！！\n",cnt);
            system("cls");
            printf("想继续玩请输入0，结束请输入-1\n");
            fprintf(fp2,"想继续玩请输入0，结束请输入-1\n");
            scanf("%d",&i);
            fprintf(fp2,"%d\n",i);
    }
    printf("Game over\n");
    fprintf(fp2,"Game over\n");

    fclose(fp1);
    fclose(fp2);
}
