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
    printf("��Ϸ��ʼ��loading......\n");
    fprintf(fp2,"��Ϸ��ʼ��loading......\n");
    do{
	    printf("����������1����ʼ��Ϸ������0��������Ϸ������-1\n");
	    fprintf(fp2,"����������1����ʼ��Ϸ������0��������Ϸ������-1\n");
	    scanf("%d",&i);
	    fprintf(fp2,"i=%d\n",i);
	    if(i==1){
			printf("�����������Χ��maxNum=");
			fprintf(fp2,"�����������Χ��maxNum=\n");
			scanf("%d",&maxNum);
			fprintf(fp2,"maxNum=%d\n",maxNum);
			printf("���óɹ���\n");
			fprintf(fp2,"���óɹ���\n");
    	}
    	if (i==-1) {
    		break;
		} 
    	printf("����������1����ʼ��Ϸ������0��������Ϸ������-1\n");
	    fprintf(fp2,"����������1����ʼ��Ϸ������0��������Ϸ������-1\n");
	    scanf("%d",&i);
	    fprintf(fp2,"i=%d\n",i);
    } while(i!=0 && i!=-1);
    while(i==0){
       //  printf("\n");
        printf("maxNum=%d\n",maxNum);
        fprintf(fp2,"maxNum=%d\n",maxNum);
            j=rand()%maxNum;
            printf("���������һ��0~%d֮�����:\n",maxNum-1);
            fprintf(fp2,"���������һ��0~%d֮�����:\n",maxNum-1);
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
                printf("���������һ��0~%d֮�����:\n",maxNum-1);
            	fprintf(fp2,"���������һ��0~%d֮�����:\n",maxNum-1);
                scanf("%d",&ans);
                fprintf(fp2,"%d\n",ans);
            }
            printf("����%d�ξͲµ��˴𰸣���\n",cnt);
            fprintf(fp2,"����%d�ξͲµ��˴𰸣���\n",cnt);
            system("cls");
            printf("�������������0������������-1\n");
            fprintf(fp2,"�������������0������������-1\n");
            scanf("%d",&i);
            fprintf(fp2,"%d\n",i);
    }
    printf("Game over\n");
    fprintf(fp2,"Game over\n");

    fclose(fp1);
    fclose(fp2);
}
