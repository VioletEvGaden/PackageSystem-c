#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define MAX_USER            1000        //最大用户数
#define MAX_PACKAGE         1000        //最大快递数
#define LENGTH_OF_USERID    10          //用户名最大长度
#define LENGTH_OF_PASS      6           //密码最大长度


char *roleName[]= {  "系统管理员",              //0
                 "快递员",               //1
                 "用户"                    //2
              };

struct datenode
{
    short year;
    short month;
    short day;
};
typedef struct datenode date;       //日期结构体类型

struct usernode
{
    char userId[LENGTH_OF_USERID+1];            //编号
    char password[LENGTH_OF_PASS+1];            //密码
    char nickname[9];                           //用户昵称
    char phone[11];                            //电话号码
    int  role;                                  //角色，1为系统管理员 2为快递员  3为普通用户
    char email[16];                             //email
};
typedef struct usernode user;                   //用户结构体类型

struct packagenode{
    char num[30];                        //快递单号
    char recName[20];                   //收件人姓名
    char rec_phone[20];              //收件人手机
    char recAddress[20];                       //收件人地址
    char sendName[20];                   //寄件人姓名
    char send_phone[20];              //寄件人手机
    char sendAddress[20];                        //寄件人地址
    char code[20];                   //取件码
    char status[20];                  //快递状态
    char couName[20];                   //快递员姓名
    char couPhone[20];                  //快递员电话
    char rec_userId [20];                    //收件人id
    char send_userId  [20] ;                  //寄件人id

};
typedef struct packagenode package;

struct packageHistory{
    char num[30];           //快递单号
    char recName[20];                   //收件人姓名
    char rec_phone[20];              //收件人手机
    char sendName[20];                   //寄件人姓名
    char send_phone[20];              //寄件人手机
     char status[20];                  //快递状态
    char couName[20];                   //快递员姓名
    char couPhone[20];                  //快递员电话
    char time[20];                   //时间

};
typedef struct packageHistory history;

/*
    @函数名称:gotox    函数功能：到屏幕的第x行
*/
void gotox(int x)
{
    int i;
    for (i=0;i<x-1;i++)
        putchar('\n');
}

/*
    @函数名称：mainMenu      入口参数：无
    @函数功能：登录菜单，返回用户选择
*/
int mainMenu()
{
    int c;
    gotox(6);
    printf("\t\t|*^**^**^**^**^**^**^**^**^**^**^**^**^**^**^|\n");
	printf("\t\t+============================================+\n");
	printf("\t\t&&|      @  *·*·*·*·*·*·*·*  @      |&&\n");
	printf("\t\t&&|      .                          .      |&&\n");
	printf("\t\t&&|      * 江西师大菜鸟驿站管理系统 *      |&&\n");
	printf("\t\t&&|      .                          .      |&&\n");
	printf("\t\t&&|      .       1  登录系统        .      |&&\n");
	printf("\t\t&&|      .       2  注册系统        .      |&&\n");
	printf("\t\t&&|      .       0  退出系统        .      |&&\n");
	printf("\t\t&&|      .                          .      |&&\n");
	printf("\t\t&&|      @  *·*·*·*·*·*·*·*  @      |&&\n");
    printf("\t\t+============================================+\n");
	printf("\t\t*-^@^-----^@^-----^@^----^@^-----^@^-----^@^-*\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @函数名称：menuAdmin     入口参数：无
    @函数功能：显示系统管理员菜单，返回用户选择
*/
int menuAdmin()
{
    int c;
    gotox(6);
    printf("\t\t\t   菜鸟驿站管理系统——系统管理\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t浏览用户\t\t*\n");
    printf("\t\t\t*  2\t添加用户\t\t*\n");
    printf("\t\t\t*  3\t删除用户\t\t*\n");
    printf("\t\t\t*  4\t修改个人信息\t\t*\n");
    printf("\t\t\t*  5\t初始化用户密码\t\t*\n");
    printf("\t\t\t*  6\t修改登录密码\t\t*\n");
    printf("\t\t\t*  7\t系统备份\t\t*\n");
    printf("\t\t\t*  0\t注销\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}
/*
    @函数名称：menuCourier    入口参数：无
    @函数功能：显示驿站管理员菜单，返回用户选择
*/
int menuCourier()
{
    int c;
    gotox(6);
    printf("\t\t\t   菜鸟驿站管理系统——驿站管理员\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t修改个人信息\t\t*\n");
    printf("\t\t\t*  2\t浏览快递信息\t\t*\n");
    printf("\t\t\t*  3\t修改快递信息\t\t*\n");
    printf("\t\t\t*  4\t批量导入快递\t\t*\n");
    printf("\t\t\t*  5\t将快递编码进快递柜\t*\n");
    printf("\t\t\t*  6\t查看快递历史\t\t*\n");
    printf("\t\t\t*  7\t修改登录密码\t\t*\n");
    printf("\t\t\t*  0\t注销\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}
/*
    @函数名称：menuUser    入口参数：无
    @函数功能：显示用户菜单，返回用户选择
*/
int menuUser()
{
    int c;
    gotox(6);
    printf("\t\t\t   菜鸟驿站管理系统——用户系统\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t修改个人信息\t\t*\n");
    printf("\t\t\t*  2\t查看我的快递\t\t*\n");
    printf("\t\t\t*  3\t取件\t\t\t*\n");
    printf("\t\t\t*  4\t寄件\t\t\t*\n");
    printf("\t\t\t*  5\t修改登录密码\t\t*\n");
    printf("\t\t\t*  0\t注销\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}

/*
    @函数名称：menu1    入口参数：无
    @函数功能：显示我的快递菜单，返回用户选择
*/
int menu1()
{
    int c;
    gotox(6);
    printf("\t\t\t   菜鸟驿站管理系统——查看我的快递\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t*  1\t我收到的\t\t*\n");
    printf("\t\t\t*  2\t我寄出的\t\t*\n");
    printf("\t\t\t*  0\t退出\t\t\t*\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[ ]\b\b");
    scanf("%d",&c);
    return c;
}


/*
    @函数名称：displayTopic      入口参数：char *s
    @函数功能：显示子模块名称
*/
void displayTopic(char *s)
{
    int i;
    gotox(6);           //到第6行
    printf("%s\n",s);
    for (i=0;i<80;i++)
            printf("-");
    printf("\n");
}
/*
    @函数名称：showtime()        入口参数：int k
    @函数功能：显示时间与欢迎界面
*/
void showtime(int k)
{
    time_t nowtime;
    struct tm *t;
    time(&nowtime);

    t=localtime(&nowtime);
    if (t->tm_hour>=5 && t->tm_hour<9)
        printf("早上好！\n  ");
    else
           if (t->tm_hour>=9 && t->tm_hour<12)
                  printf("上午好！\n  ");
           else
                   if (t->tm_hour>12 && t->tm_hour<18)
                        printf("下午好！\n    ");
                   else
                        printf("晚上好！\n    ");

    switch(k)
    {
        case 0: printf("  欢迎使用快递管理系统！");        //进入系统时调用showtime(0);
            break;
        case 1: printf("\t谢谢使用快递管理系统！\n");      //退出系统时调用showtime(0);
                printf("\t当前时间: %s",  ctime(&nowtime));
            break;
    }
}
