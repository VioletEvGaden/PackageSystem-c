#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define MAX_USER            1000        //����û���
#define MAX_PACKAGE         1000        //�������
#define LENGTH_OF_USERID    10          //�û�����󳤶�
#define LENGTH_OF_PASS      6           //������󳤶�


char *roleName[]= {  "ϵͳ����Ա",              //0
                 "���Ա",               //1
                 "�û�"                    //2
              };

struct datenode
{
    short year;
    short month;
    short day;
};
typedef struct datenode date;       //���ڽṹ������

struct usernode
{
    char userId[LENGTH_OF_USERID+1];            //���
    char password[LENGTH_OF_PASS+1];            //����
    char nickname[9];                           //�û��ǳ�
    char phone[11];                            //�绰����
    int  role;                                  //��ɫ��1Ϊϵͳ����Ա 2Ϊ���Ա  3Ϊ��ͨ�û�
    char email[16];                             //email
};
typedef struct usernode user;                   //�û��ṹ������

struct packagenode{
    char num[30];                        //��ݵ���
    char recName[20];                   //�ռ�������
    char rec_phone[20];              //�ռ����ֻ�
    char recAddress[20];                       //�ռ��˵�ַ
    char sendName[20];                   //�ļ�������
    char send_phone[20];              //�ļ����ֻ�
    char sendAddress[20];                        //�ļ��˵�ַ
    char code[20];                   //ȡ����
    char status[20];                  //���״̬
    char couName[20];                   //���Ա����
    char couPhone[20];                  //���Ա�绰
    char rec_userId [20];                    //�ռ���id
    char send_userId  [20] ;                  //�ļ���id

};
typedef struct packagenode package;

struct packageHistory{
    char num[30];           //��ݵ���
    char recName[20];                   //�ռ�������
    char rec_phone[20];              //�ռ����ֻ�
    char sendName[20];                   //�ļ�������
    char send_phone[20];              //�ļ����ֻ�
     char status[20];                  //���״̬
    char couName[20];                   //���Ա����
    char couPhone[20];                  //���Ա�绰
    char time[20];                   //ʱ��

};
typedef struct packageHistory history;

/*
    @��������:gotox    �������ܣ�����Ļ�ĵ�x��
*/
void gotox(int x)
{
    int i;
    for (i=0;i<x-1;i++)
        putchar('\n');
}

/*
    @�������ƣ�mainMenu      ��ڲ�������
    @�������ܣ���¼�˵��������û�ѡ��
*/
int mainMenu()
{
    int c;
    gotox(6);
    printf("\t\t|*^**^**^**^**^**^**^**^**^**^**^**^**^**^**^|\n");
	printf("\t\t+============================================+\n");
	printf("\t\t&&|      @  *��*��*��*��*��*��*��*  @      |&&\n");
	printf("\t\t&&|      .                          .      |&&\n");
	printf("\t\t&&|      * ����ʦ�������վ����ϵͳ *      |&&\n");
	printf("\t\t&&|      .                          .      |&&\n");
	printf("\t\t&&|      .       1  ��¼ϵͳ        .      |&&\n");
	printf("\t\t&&|      .       2  ע��ϵͳ        .      |&&\n");
	printf("\t\t&&|      .       0  �˳�ϵͳ        .      |&&\n");
	printf("\t\t&&|      .                          .      |&&\n");
	printf("\t\t&&|      @  *��*��*��*��*��*��*��*  @      |&&\n");
    printf("\t\t+============================================+\n");
	printf("\t\t*-^@^-----^@^-----^@^----^@^-----^@^-----^@^-*\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @�������ƣ�menuAdmin     ��ڲ�������
    @�������ܣ���ʾϵͳ����Ա�˵��������û�ѡ��
*/
int menuAdmin()
{
    int c;
    gotox(6);
    printf("\t\t\t   ������վ����ϵͳ����ϵͳ����\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t����û�\t\t*\n");
    printf("\t\t\t*  2\t����û�\t\t*\n");
    printf("\t\t\t*  3\tɾ���û�\t\t*\n");
    printf("\t\t\t*  4\t�޸ĸ�����Ϣ\t\t*\n");
    printf("\t\t\t*  5\t��ʼ���û�����\t\t*\n");
    printf("\t\t\t*  6\t�޸ĵ�¼����\t\t*\n");
    printf("\t\t\t*  7\tϵͳ����\t\t*\n");
    printf("\t\t\t*  0\tע��\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}
/*
    @�������ƣ�menuCourier    ��ڲ�������
    @�������ܣ���ʾ��վ����Ա�˵��������û�ѡ��
*/
int menuCourier()
{
    int c;
    gotox(6);
    printf("\t\t\t   ������վ����ϵͳ������վ����Ա\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t�޸ĸ�����Ϣ\t\t*\n");
    printf("\t\t\t*  2\t��������Ϣ\t\t*\n");
    printf("\t\t\t*  3\t�޸Ŀ����Ϣ\t\t*\n");
    printf("\t\t\t*  4\t����������\t\t*\n");
    printf("\t\t\t*  5\t����ݱ������ݹ�\t*\n");
    printf("\t\t\t*  6\t�鿴�����ʷ\t\t*\n");
    printf("\t\t\t*  7\t�޸ĵ�¼����\t\t*\n");
    printf("\t\t\t*  0\tע��\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}
/*
    @�������ƣ�menuUser    ��ڲ�������
    @�������ܣ���ʾ�û��˵��������û�ѡ��
*/
int menuUser()
{
    int c;
    gotox(6);
    printf("\t\t\t   ������վ����ϵͳ�����û�ϵͳ\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t�޸ĸ�����Ϣ\t\t*\n");
    printf("\t\t\t*  2\t�鿴�ҵĿ��\t\t*\n");
    printf("\t\t\t*  3\tȡ��\t\t\t*\n");
    printf("\t\t\t*  4\t�ļ�\t\t\t*\n");
    printf("\t\t\t*  5\t�޸ĵ�¼����\t\t*\n");
    printf("\t\t\t*  0\tע��\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @�������ƣ�menu1    ��ڲ�������
    @�������ܣ���ʾ�ҵĿ�ݲ˵��������û�ѡ��
*/
int menu1()
{
    int c;
    gotox(6);
    printf("\t\t\t   ������վ����ϵͳ�����鿴�ҵĿ��\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t���յ���\t\t*\n");
    printf("\t\t\t*  2\t�Ҽĳ���\t\t*\n");
    printf("\t\t\t*  0\t�˳�\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t������ѡ��[ ]\b\b");
    scanf("%d",&c);
    return c;
}


/*
    @�������ƣ�displayTopic      ��ڲ�����char *s
    @�������ܣ���ʾ��ģ������
*/
void displayTopic(char *s)
{
    int i;
    gotox(6);           //����6��
    printf("%s\n",s);
    for (i=0;i<80;i++)
            printf("-");
    printf("\n");
}
/*
    @�������ƣ�showtime()        ��ڲ�����int k
    @�������ܣ���ʾʱ���뻶ӭ����
*/
void showtime(int k)
{
    time_t nowtime;
    struct tm *t;
    time(&nowtime);

    t=localtime(&nowtime);
    if (t->tm_hour>=5 && t->tm_hour<9)
        printf("���Ϻã�\n  ");
    else
           if (t->tm_hour>=9 && t->tm_hour<12)
                  printf("����ã�\n  ");
           else
                   if (t->tm_hour>12 && t->tm_hour<18)
                        printf("����ã�\n    ");
                   else
                        printf("���Ϻã�\n    ");

    switch(k)
    {
        case 0: printf("  ��ӭʹ�ÿ�ݹ���ϵͳ��");        //����ϵͳʱ����showtime(0);
            break;
        case 1: printf("\tллʹ�ÿ�ݹ���ϵͳ��\n");      //�˳�ϵͳʱ����showtime(0);
                printf("\t��ǰʱ��: %s",  ctime(&nowtime));
            break;
    }
}
