#include "packagesystem.h"


char *getRole(int code);                                //根据代码获取用户角色                          //根据代码获取系科名称
int login(char currentUserId[]);
void enterSystem(int c,char currentUserId[]);
void encryption(char password[]) ;    //加密
void decryption(char password[]) ;    //解密
int readUserFromFile(user userArray[],char *f);                 //从文件读入用户信息
int userSearch(user userArray[], int userTotal, char id[]);         //查找用户信息
#include "admin.c"
#include "courier.c"
#include "user.c"



int main()
{
    int c,loop=1;
     user userArray[MAX_USER];   //用户数组
    int userTotal;              //用户总数
      userTotal=readUserFromFile(userArray,"user.txt");   //从文件中读入用户信息
    char currentUserId[LENGTH_OF_USERID+1];             //当前用户帐号
    while (loop==1)
    {
        system("cls");  //清除屏幕
        c=mainMenu();   //显示登录菜单
        switch(c)
        {
            case    1:  //登录系统
                        c=login(currentUserId);         //调用身份验证函数，返回用户角色
                        enterSystem(c,currentUserId);   //显示不同角色对应的菜单
                        break;
            case   2://注册
                     inputUser(userArray,&userTotal);
            default: //退出系统
                        loop=0;
                        break;
        }
        showtime(1);
    }
    return 0;
}


/*
    @函数名称：getVerificationCode   入口参数:char verificationCode[],int n
    @函数功能：产生n位验证码
*/
void getVerificationCode(char verificationCode[],int n)
{
    char str[]="2323456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //0,1易与字母‘o’与‘l'混消，不用
    int i;
    srand(time(NULL));
    for (i=0;i<n;i++)
        verificationCode[i]=str[rand()%62];
    verificationCode[n]='\0';
}

/*
    @函数名称：inputPassWord         入口参数：char password[],int n
    @函数功能：输入最大长度为n的密码
*/
void inputPassWord(char password[],int n)
{
    int i;
    char c;
    i=0;
    while (i<n)
    {
        c=getch();
        if (c=='\r') break;         //回车键
        if (c==8 && i>0 )           //退格键
            {   printf("\b \b");
                i--;
            }
         else
            {   password[i++]=c;    //有效密码字符
                printf("*");        //回显*号
            }
    }
    printf("\n");
    password[i]='\0';
}
/*
    @函数名称：login     入口参数：无
    @函数功能：用户身份验证信息，返回用户角色
*/
int login( char currentUserId[])
{
    user userArray[MAX_USER];               //用户数组
    int userTotal;                          //用户总数
    int counter=3;
    char verificationCode[5];                //存放验证码
    char inputVerificationCode[5];           //存入用户输入的验证码
    char originalPassWord[LENGTH_OF_PASS+1];
    char password[LENGTH_OF_PASS+1];
    int pos;

    userTotal=readUserFromFile(userArray,"user.txt");   //从文件中读入用户信息\b
    while (counter>0)
    {   system("cls");
        counter--;
        displayTopic("菜鸟驿站管理系统-->用户登录");
        printf("用户名：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s",currentUserId);
        printf("密  码：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        inputPassWord(password,7);
        getVerificationCode(verificationCode,4);
        printf("验证码：[           ] %s\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",verificationCode);
        scanf("%s",inputVerificationCode);

        pos=userSearch(userArray,userTotal,currentUserId);
        if (pos==-1)
            {   printf("该用户不存在！还有%d次登录机会。\n",counter);
                getch();
                continue;
            }
        else
        {   strcpy(originalPassWord,userArray[pos].password);
            decryption(originalPassWord);        //解密原始密码
            if (strcmp(originalPassWord,password)!=0)
                {   printf("输入的密码有误，还有%d次登录机会。\n",counter);
                    getch();
                    continue;
                }
            else
                if ( strcasecmp(verificationCode,inputVerificationCode)!=0)
                {   printf("输入的验证码有误，还有%d次登录机会。\n",counter);
                    getch();
                    continue;
                }
            else
                return userArray[pos].role;     //返回用户角色
        }
    }
    return -1;       //登录失败
}
/*
    @函数名称：readUserFromFile    入口参数：user userArray[],char *f
    @函数功能：从文件中读取用户信息至数组，函数返回记录总数
*/
int readUserFromFile(user userArray[],char *f)
{
    FILE *fp;
    user *p;
    int counter=0,k;

    fp=fopen(f,"rb");
    if (fp==NULL)
    {
        printf("未找到文件!\n");
        return 0;
    }
    else
    {
        while (!feof(fp))
        {
            p=(user *)malloc(sizeof(user));
            k=fscanf(fp,"%s%s%s%s%d%s\n",&p->userId,&p->password,&p->nickname,&p->phone,&p->role,&p->email);
            if (k!=-1)
            {
                userArray[counter]=*p;
                counter++;
            }
            else
            {
                printf("用户文件载入失败!\n");
                break;

            }

        }
        fclose(fp);
        return counter;
    }
}

/*
    @函数名称：userSearch     入口参数：user userArray[],int userTotal
    @函数功能：采用二分查找法在userArray[]中查找用户帐号为id[]的记录位置，查找失败返回-1
*/
int userSearch(user userArray[], int userTotal, char id[])
{
    int left=0,right=userTotal-1,mid;
    int k;
    while (left<=right)
    {
        mid=(left+right)/2;                     //二分
        k=strcmp(userArray[mid].userId,id);
        if ( k==0)
            return mid;
        else
            if (k<0)
                left=mid+1;
            else
                right=mid-1;
    }
    return -1;                                  //查找失败
}


/*
    @函数名称：enterSystem     入口参数：无
    @函数功能：根据用户的角色调用不同的箮理子系统
*/

void enterSystem(int c,char currentUserId[])
{
     switch(c)
    {
        case 0: //c==0表示系统管理员用户
                adminSystem(currentUserId);
                break;
        case 1://c==1表示快递员登录
                courierSystem(currentUserId);
                break;
        case 2://c==2表示普通用户
                userSystem(currentUserId);
                break;
        default:
                break;
    }

}
/*
    @函数名称：encryption        函数功能：对密码进行加密
*/
void encryption(char password[])     //加密
{
    int i=0;
    int count=strlen(password);
    while (password[i]!='\0')                     //password加密
    {
        password[i]=password[i]^0xba;
        i++;
    }

}

/*
    @函数名称：decryption        函数功能：对密码进行解密
*/
void decryption(char password[])     //加密
{
    int i=0;
    while (password[i]!='\0')                  //password加密
    {
        password[i]=password[i]^0xba;
        i++;
    }

}
/*
    @函数名称：getRole     @函数功能：根据角色代码获取角色名称
*/
char *getRole(int code)
{

    return roleName[code];
}


