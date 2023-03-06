

void adminSystem(char currentUserId[]);

/*
    @函数名称：adminSystem    入口参数：无
    @函数功能：系统管理员角色管理子程序
*/
void adminSystem(char currentUserId[])
{
    int c,loop=1;

    user userArray[MAX_USER];   //用户数组
    package packageArray[MAX_PACKAGE];   //快递数组
    history historyArray[MAX_PACKAGE];   //快递数组
    int userTotal;              //用户总数
    int packageTotal;           //快递总数
    int historyTotal;
    int pos;
    userTotal=readUserFromFile(userArray,"user.txt");   //从文件中读入用户信息
    packageTotal=readPackageFromFile(packageArray,"package.txt");   //从文件中读取快递信息
    historyTotal=readHistoryFromFile(historyArray,"history.txt");
    pos=userSearch(userArray,userTotal,currentUserId);
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].nickname);  //显示当前有户姓名
        showtime(0);                        //显示欢迎界面
        c=menuAdmin();  //显示系统管理员角色菜单
        switch(c)
        {
            case    1:  //显示用户信息
                        printUser(userArray,userTotal);
                        system("pause");
                        break;
            case    2:  //输入用户信息
                        inputUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.txt");
                        break;
            case    3:  //删除用户信息
                        deleteUser(userArray,&userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.txt");
                        printUser(userArray,userTotal);
                        break;

           // case    4:  //显示图书信息
                       // printBook(bookArray,bookTotal);
                       // system("pause");
                       // break;
            case    4:  //修改个人信息
                        system("cls");
                        modifyUserInfo(userArray,userTotal,currentUserId);
                        break;
            case    5:  //初始化用户密码
                        printUser(userArray,userTotal);
                        initPassWord(userArray,userTotal);
                        break;
            case    6:  //修改登录密码
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            case    7:  //系统备份
                        system("cls");
                        displayTopic("菜鸟驿站管理系统——数据备份");
                        backupUser(userArray,userTotal);
                        backupPackage(packageArray,packageTotal);
                        backupHistory(historyArray,historyTotal);
                        system("pause");
                        break;
            default:    //注销登录
                        loop=0;
                        break;
        }
    }
    return;
}

/*
    @函数名称：inputUser()   入口参数：user userArray[],int *n
    @函数功能：输入用户信息
*/
void inputUser(user userArray[],int *n)
{

    int counter=0,j;
    user account;
    if (*n<MAX_USER)
        {
            while (1)
            {
                system("cls");
                displayTopic("菜鸟驿站管理系统-->添加用户");
                printf("用户名（为q时结束）：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
                scanf("%s",account.userId);                                         //输入帐号
                if (account.userId[0]=='q')
                                break;
                if (userSearch(userArray,*n,account.userId)==-1)   //查找该账号是否存在
                {
                        printf("昵称\t电话\t角色代码\n");
                        printf("---------------------------------\n");
                        scanf("%s",&account.nickname);                                 //输入昵称
                        scanf("%s",&account.phone);                   //输入电话号码
                        scanf("%d",&account.role);                                 //输入角色代码

                        strcpy(account.email,"mmm");                                     //初始email为mmm
                        strcpy(account.password,"123456");                  //初始密码为"123456"
                        encryption(account.password);                           //加密
                        j=*n-1;
                        while ( j>=0 &&   strcmp(userArray[j].userId,account.userId) >0   )
                                {
                                    userArray[j+1]=userArray[j];
                                    j--;
                                }
                        userArray[j+1]=account;                                     //按用户帐号序插入到适当位置
                        (*n)++;
                        counter++;
                        printf("success...\n");
                        system("pause");
                        if (*n==MAX_USER) break;                            //容量已满
                }
                else
                    {
                            printf("该账号已存在！请重新输入！\n");
                            system("pause");
                    }
            }
            printf("成功创建%d条帐户信息!\n",counter);
            system("pause");
        }
}

/*
    @函数名称：printUser     入口参数：user userArray[],int userTotal
    @函数功能：将用户信息分页显示在屏幕上
*/
void printUser(user userArray[],int userTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (userTotal>0)
    {   totalPage=(userTotal-1)/10;                     //每页显示10条记录
        if (totalPage*10<userTotal-1) totalPage++;     //计算总页数
        for (i=0;i<userTotal;)
        {   system("cls");
            displayTopic("菜鸟驿站管理系统-->显示用户");
            page++;
            printf("%12s%9s%15s%11s","用户名","昵称","电话号码","角色");
            printf("%17s\n","Email");
            for (k=0;k<80;k++)  putchar('-');
            printf("\n");

            for (j=0;j<10&&i<userTotal;j++)
            {
                if ( userArray[i].role!=0)
                {
                    printf("%12s",userArray[i].userId);
                    printf("%9s",userArray[i].nickname);
                    printf("%15s",userArray[i].phone);
                    printf("%11s",getRole(userArray[i].role));
                    if(strcmp(userArray[i].email,"mmm")==0) printf("%17s\n","");
                    else printf("%17s\n",userArray[i].email);
                }
                i++;
            }
            for (k=0;k<80;k++)  putchar('-');
            printf("\n");
            printf("第%d页，共%d页，上一页（↑）  下一页（↓），ESC键退出\n",page,totalPage);
            ch=getch();
            if (27==ch) return ;
            if (0==ch||0xe0==ch) ch|=getch()<<8;    //非字符键
            if (0x48e0==ch)     //向上键（↑）
            {
                    i=i-j;
                    if (i>10)
                        { i=i-10; page-=2;}
                    else
                        {i=0; page=0;}
            }
        }
    }
}
/*
    @函数名称：writeUserToFile   入口参数：user userArray[],int userTotal,char *f
    @函数功能：将用户信息存入文件
*/
void writeUserToFile(user userArray[],int userTotal,char *f)
{
    FILE *fp;
    user *p;
    fp=fopen(f,"w");
    int i;
    if (fp!=NULL)
    {
       for(i=0;i<userTotal;i++)
        {
            p=(user *)malloc(sizeof(user));
            *p=userArray[i];
            if(fprintf(fp,"%s %s %s %s %d %s\n",&p->userId,&p->password,&p->nickname,&p->phone,userArray[i].role,&p->email)==0)
            {
                printf("保存失败!\n");
                return;

            }
        }
        free(p);
        fclose(fp);
        printf("保存成功!\n");

    }
    else
        printf("保存失败！");
}
/*
    @函数名称：deleteUser    入口参数：user userArray,int *n ,user currentUser[]
    @函数功能：删除用户信息
*/
void deleteUser(user userArray[],int *n,user currentUser[])
{
    char id[LENGTH_OF_USERID +1],ans;
    int pos,i;
    system("cls");
    printUser(userArray,*n);
    printf("请输入要删除的用户帐号(输入不存在的账号返回)：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",id);
    if (strcmp(id,currentUser)!=0)                      //不能删除系统管理员用户
    {
        pos=userSearch(userArray,*n,id);            //查找位置
        if (pos==-1)                                //查找失败
                    {   printf("无此用户！\n");
                        system("pause");
                        return ;
                    }
        //if (userArray[pos].count!=0)
        //{
            //printf("请先还清所借图书，才能删除该用户！\n");
            //system("pause");
           // return ;
        //}
        printf("真的要删除吗？(y/n)");
        scanf(" %c",&ans);
        if (ans=='y'|| ans=='Y')
        {
               for (i=pos+1;i<*n;i++)
                   userArray[i-1]=userArray[i];
               *n=*n-1;
               writeUserToFile(userArray,*n,"user.dat");
               printUser(userArray,*n);
               system("pause");
        }
        else
        {
               printUser(userArray,*n);
               system("pause");
        }
    }
    else
        {       printf("不能删除当前用户！\n");
                system("pause");
                return ;
        }
}
/*
    @函数名称：modifyUserInfo    @入口参数：user userArray[],int userTotal,char userId[]
    @函数功能：修改用户信息（email）
*/
void  modifyUserInfo(user userArray[],int userTotal,char userId[])
{
    int pos,i;
    char email[16];
    char phone[16];
    char nickname[16];
    int flag=0;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("菜鸟驿站管理系统-->修改个人信息");
    printf("%12s%12s%15s%16s","用户名","昵称","电话号码","角色");
    printf("%17s\n","Email");
    for (i=0;i<80;i++)  putchar('-');
        printf("\n");
    printf("%12s",userArray[pos].userId);
    printf("%12s",userArray[pos].nickname);
    printf("%15s",userArray[pos].phone);
    printf("%16s",getRole(userArray[pos].role));
    if(strcmp(userArray[i].email,"mmm")==0) printf("%17s\n","");
    else printf("%17s\n",userArray[i].email);
    for (i=0;i<80;i++)  putchar('-');
    printf("\n");

    printf("若需修改昵称,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    getchar();
    gets(nickname);
    printf("若需修改电话,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();
    gets(phone);
    printf("若需修改Email,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //去除键盘缓冲区中的回车符
    gets(email);

    if (nickname[0]!='\0')
    {   strcpy(userArray[pos].nickname,nickname);
        flag=1;
    }
    if (phone[0]!='\0')
    {   strcpy(userArray[pos].phone,phone);
        flag=1;
    }

    if (email[0]!='\0')
        {   strcpy(userArray[pos].email,email);
            flag=1;
        }
    if(flag==1)   writeUserToFile(userArray,userTotal,"user.txt");       //存盘s
}
/*
    @函数名称：modifyPassWord    入口参数：user userArray[],int userTatal, char userId[]
    @函数功能：修改个人密码
*/
void modifyPassWord(user userArray[],int userTotal, char userId[])//修改密码
{
    int pos;
    char originalPassWord[LENGTH_OF_PASS+1];
    char password1[LENGTH_OF_PASS+1];
    char password2[LENGTH_OF_PASS+1];
    char password3[LENGTH_OF_PASS+1];
    pos=userSearch(userArray,userTotal,userId);
    strcpy(originalPassWord,userArray[pos].password);
    decryption(originalPassWord);
    system("cls");
    displayTopic("菜鸟驿站管理系统-->修改密码");
    printf("原始密码：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password1,7);
    printf("新设密码：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password2,7);
    printf("再输一遍：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password3,7);
    if (strcmp(originalPassWord,password1)!=0)
        printf("原始密码有误！修改失败。\n");
    else
        if (strcmp(password2,password3)!=0)
            printf("两次输入的密码不一致！修改失败。\n");
        else  //成功
        {
            encryption(password2);
            strcpy(userArray[pos].password,password2);
            writeUserToFile(userArray,userTotal,"user.txt");
            printf("密码修改成功！\n");
        }
}
/*
    @函数名称：initPassWord  入口参数：user userArray[],int userTotal
    @函数功能：初始化用户密码
*/
void initPassWord(user userArray[],int userTotal)
{
    char ans,userId[LENGTH_OF_USERID +1];
    int pos,i;
    printf("请输入用户帐号：[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",userId);
    pos=userSearch(userArray,userTotal,userId);
    if (pos==-1)
    {   printf("用户不存在！\n");
        system("pause");
        return ;
    }
    else
    {
        printf("\033[40;31m初始化账号为%s\033[0m\n",userArray[pos].userId);;
        printf("确认初始化(y/n):[   ]\b\b\b");
        scanf(" %c",&ans);
        if (ans=='Y' || ans=='y')
            {
                strcpy(userArray[pos].password,"123456");
                encryption(userArray[pos].password);
                writeUserToFile(userArray,userTotal,"user.txt");
                printf("已经成功将%s账户密码初始化为123456!\n\n",userArray[pos].userId);
                system("pause");
            }
        else
            return ;
    }
}
/*
    @函数名称：backupUser        入口参数：user userArray[],int userTotal
    @函数功能：备份用户信息
*/
void backupUser(user userArray[],int userTotal)
{
    char filename[30]="user_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".txt");
    printf("用户数据备份至:%s\n",filename);
    writeUserToFile(userArray,userTotal,filename);
}
/*
    @函数名称：backupUser        入口参数：user userArray[],int userTotal
    @函数功能：备份用户信息
*/
void backupPackage(package packageArray[],int packageTotal)
{
    char filename[30]="package_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".txt");
    printf("用户数据备份至:%s\n",filename);
    writePackageToFile(packageArray,packageTotal,filename);
}
/*
    @函数名称：backupUser        入口参数：user userArray[],int userTotal
    @函数功能：备份用户信息
*/
void backupHistory(history historyArray[],int historyTotal)
{
    char filename[30]="history_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".txt");
    printf("用户数据备份至:%s\n",filename);
    writeHistoryToFile(historyArray,historyTotal,filename);
}


