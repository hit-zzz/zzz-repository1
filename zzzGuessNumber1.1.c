//��������:zzzGuessNumber
//��������:������
//��ϵ��ʽ:18846185293
//���ʱ��:2017 7 5
//��Ϸ���:�ɼ�����������һ��С��maxNum����������Ҳ�һ����ans����ȷ��Ϊanswer
//��Ϸ�汾:v1.0
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
void main(){
    FILE *fp1;
    FILE *fp2;
    char a;
    int j;
    int i=0;
    int maxNum=100;
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

    printf("maxNum=%d\n",maxNum);
    while(i!=-1){
                j=rand()%100;
                printf("���������һ��0~99֮�����:\n");
                fprintf(fp2,"���������һ��0~99֮�����:\n");
                scanf("%d",&ans);
                fprintf(fp2,"%d\n",ans);
                while(ans!=j){
                    if(ans>j){
                        printf("���µ�������\n");
                        fprintf(fp2,"���µ�������\n");
                    } else{
                            printf("���µ���С��\n");
                            fprintf(fp2,"���µ���С��\n");
                    }
                    cnt++;
                    printf("����Ҽ�������һ��0~99֮�����:\n");
                    fprintf(fp2,"����Ҽ�������һ��0~99֮�����:\n");
                    scanf("%d",&ans);
                    fprintf(fp2,"%d\n",ans);
                }
                printf("����%d�ξͲµ��˴𰸣���\n",cnt);
                fprintf(fp2,"����%d�ξͲµ��˴𰸣���\n",cnt);
                printf("�������������0������������-1\n");
                fprintf(fp2,"�������������0������������-1\n");
                scanf("%d",&i);
                fprintf(fp2,"%d\n",i);
    }

    fclose(fp1);
    fclose(fp2);
}
