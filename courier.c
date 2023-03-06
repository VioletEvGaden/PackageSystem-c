
void courierSystem(char currentUserId[]);

/*
    @函数名称：courierSystem    入口参数：无
    @函数功能：快递员角色管理子程序
*/
void courierSystem(char currentUserId[])
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
        printf("%s:",userArray[pos].nickname);  //显示当前快递员姓名
        showtime(0);                        //显示欢迎界面
        c=menuCourier();  //显示快递员角色菜单
        switch(c)
        {
            case    1:  //修改个人信息
                        system("cls");
                        modifyUserInfo(userArray,userTotal,currentUserId);
                        break;
            case    2:  //浏览快递信息
                        printpackage(packageArray,packageTotal);
                        system("pause");
                        break;

            case    3:  //修改快递信息
                        system("cls");
                        char num[20];
                        printf("请输入要修改的快递单号:");
                        scanf("%s",&num);
                        modifyPackageInfo(packageArray,packageTotal,num);
                        break;
            case    4:  //将快递批量进快递柜（添加快递）
                        importpackage(packageArray,&packageTotal,userArray[pos]);
                        printpackage(packageArray,packageTotal);
                        system("pause");
                        break;
            case    5://添加取件码
                        system("cls");
                        addCode(packageArray,packageTotal,historyArray,&historyTotal);
                        system("pause");
                        break;
            case    6: //查看快递历史
                        system("cls");
                        printhistory(historyArray,historyTotal);
                        system("pause");
                        break;

            case    7:  //修改登录密码
                        modifyPassWord(userArray,userTotal,currentUserId);
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
    @函数名称：printpackage     入口参数：package packageArray[],int packageTotal
    @函数功能：将用户信息分页显示在屏幕上
*/
void printpackage(package packageArray[],int packageTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (packageTotal>0)
    {   totalPage=(packageTotal-1)/10;                     //每页显示10条记录
        if (totalPage*10<packageTotal-1) totalPage++;     //计算总页数
        for (i=0;i<packageTotal;)
        {   system("cls");
            gotox(6);           //到第6行
            printf("%s\n","菜鸟驿站管理系统-->显示快递信息");
            for (k=0;k<150;k++)
                printf("-");
            printf("\n");
            page++;
            printf("%10s%12s%15s%15s%20s%15s%15s%20s%10s%12s\n","序号","快递单号","收件人姓名","收件人电话","收件人地址","寄件人姓名","寄件人电话","寄件人地址","取件码","快递状态");
            for (k=0;k<150;k++)  putchar('-');
            printf("\n");

            for (j=0;j<10&&i<packageTotal;j++)
            {

                printf("%10d",i+1);
                printf("%12s",packageArray[i].num);
                printf("%15s",packageArray[i].recName);
                printf("%15s",packageArray[i].rec_phone);
                printf("%20s",packageArray[i].recAddress);
                printf("%15s",packageArray[i].sendName);
                printf("%15s",packageArray[i].send_phone);
                printf("%20s",packageArray[i].sendAddress);
                printf("%10s",packageArray[i].code);
                printf("%12s\n",packageArray[i].status);
                i++;
            }
            for (k=0;k<150;k++)  putchar('-');
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
    @函数名称：importpackage   入口参数：package packageArray[],int packageTotal
    @函数功能：从文件导入批量导入快递信息
*/
void importpackage(package packageArray[],int *n,user p )
{
    FILE *fp1,*fp2;
    char file[20];
    int counter=0;
    system("cls");
    displayTopic("菜鸟驿站管理系统-->批量导入快递");
    printf("请输入要导入的文件名：[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",file);
    fp1=fopen(file,"r");            //打开导入文件
    fp2=fopen("package.txt","ab");     //打开快递数据文件
    if (fp1!=NULL && fp2!=NULL)
    {
         if (*n<MAX_PACKAGE)
         {
             while (!feof(fp1))
             {
                 fscanf(fp1,"%s",packageArray[*n+counter].num);   //读入快递单号
                 fscanf(fp1,"%s",packageArray[*n+counter].recName);   //读入收件人姓名
                 fscanf(fp1,"%s",packageArray[*n+counter].rec_phone);   //读入收件人手机号
                 fscanf(fp1,"%s",packageArray[*n+counter].recAddress);   //读入收件人地址
                 fscanf(fp1,"%s",packageArray[*n+counter].sendName);   //读入寄件人姓名
                 fscanf(fp1,"%s",packageArray[*n+counter].send_phone);   //读入寄件人手机号
                 fscanf(fp1,"%s",packageArray[*n+counter].sendAddress);   //读入寄件人地址
                 fscanf(fp1,"%s",packageArray[*n+counter].code);         //读入取件码
                 strcpy(packageArray[*n+counter].status,"已到站");//新入库快递的状态为可取
                 strcpy(packageArray[*n+counter].couName,p.nickname);
                 strcpy(packageArray[*n+counter].couPhone,p.phone);
                 fscanf(fp1,"%s",packageArray[*n+counter].rec_userId);         //读入收件人id
                 fscanf(fp1,"%s",packageArray[*n+counter].send_userId);         //读入寄件人id
                 counter++;
                 if (*n+counter>=MAX_PACKAGE)
                        break;
             }
             writePackageToFile(packageArray,*n+counter,"package.txt");
             //fwrite(packageArray+*n, sizeof(package),counter,fp2);    //将新导入的快递写入快递文件
             *n+=counter;
             printf("批量导入[%d]个快递,快递总数[%d].\n",counter,*n);
             system("pause");
         }
        fclose(fp1);
        fclose(fp2);
    }
    else  {
                printf("输入的文件有误，导入失败！\n");
                system("pause");
          }
}
/*
    @函数名称：modifyPackageInfo    @入口参数：package packageArray[],int packageTotal
    @函数功能：修改快递信息
*/
void  modifyPackageInfo(package packageArray[],int packageTotal,char num[])
{
    int pos,i;
    char recName[20];                   //收件人姓名
    char rec_phone[20];              //收件人手机
    char recAddress[20];                       //收件人地址
    char sendName[20];                   //寄件人姓名
    char send_phone[20];              //寄件人手机
    char sendAddress[20];                        //寄件人地址
    char rec_userId [20];                    //收件人id
    char send_userId  [20] ;                  //寄件人id
    int flag=0;
    pos=packageSearchByNum(packageArray,packageTotal,num);
    gotox(6);           //到第6行
    printf("%s\n","菜鸟驿站管理系统-->修改快递信息");
    for (i=0;i<100;i++)
        printf("-");
    printf("\n");
    printf("%15s%15s%18s%15s%15s%18s\n","收件人姓名","收件人手机","收件人地址","寄件人姓名","寄件人手机","寄件人地址");
    for (i=0;i<100;i++)  putchar('-');
        printf("\n");
    printf("%15s",packageArray[pos].recName);
    printf("%15s",packageArray[pos].rec_phone);
    printf("%18s",packageArray[pos].recAddress);
    printf("%15s",packageArray[pos].sendName);
    printf("%15s",packageArray[pos].send_phone);
    printf("%18s\n",packageArray[pos].sendAddress);
    for (i=0;i<100;i++)  putchar('-');
    printf("\n");

    printf("若需修改收件人姓名,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    getchar();
    gets(recName);
    printf("若需修改收件人手机,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();
    gets(rec_phone);
    printf("若需修改收件人地址,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();
    gets(recAddress);
    printf("若需修改寄件人姓名,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //去除键盘缓冲区中的回车符
    gets(sendName);
    printf("若需修改寄件人手机,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //去除键盘缓冲区中的回车符
    gets(send_phone);
    printf("若需修改寄件人地址,请输入(直接回车不修改):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //去除键盘缓冲区中的回车符
    gets(sendAddress);

    if (recName[0]!='\0')
    {   strcpy(packageArray[pos].recName,recName);
        flag=1;
    }if (rec_phone[0]!='\0')
    {   strcpy(packageArray[pos].rec_phone,rec_phone);
        flag=1;
    }if (recAddress[0]!='\0')
    {   strcpy(packageArray[pos].recAddress,recAddress);
        flag=1;
    }
    if (sendName[0]!='\0')
    {   strcpy(packageArray[pos].sendName,sendName);
        flag=1;
    }if (send_phone[0]!='\0')
    {   strcpy(packageArray[pos].send_phone,send_phone);
        flag=1;
    }if (sendAddress[0]!='\0')
    {   strcpy(packageArray[pos].sendAddress,sendAddress);
        flag=1;
    }
    if(flag==1)   writePackageToFile(packageArray,packageTotal,"package.txt");       //存盘s
}
/*
    @函数名称： packageSearchByNum    入口参数：package packageArray[],int packageTotal
    @函数功能：根据单号查找快递
*/
int  packageSearchByNum(package packageArray[], int packageTotal, char num[])
{
    int counter=0,i;
    int k;
    for(i=0;i<packageTotal;i++)
    {
       k=strcmp(packageArray[i].num,num);
       if(k==0)
       {
           return i;
       }
    }
    return -1;                                  //查找失败
}
/*
    @函数名称：writePackageToFile   入口参数：
    @函数功能：将用户信息存入文件
*/
void writePackageToFile(package packageArray[],int packageTotal,char *f)
{
    FILE *fp;
    package *p;
    fp=fopen(f,"w");
    int i;
    if (fp!=NULL)
    {
       for(i=0;i<packageTotal;i++)
        {
            p=(package *)malloc(sizeof(package));
            *p=packageArray[i];
            if(fprintf(fp,"%s   %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s  %s\n",&p->num,&p->recName,&p->rec_phone,&p->recAddress,&p->sendName,&p->send_phone,&p->sendAddress,&p->code,&p->status,&p->couName,&p->couPhone,&p->rec_userId,&p->send_userId)==0)
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
    @函数名称：readPackageFromFile    入口参数：package packageArray[],char *f
    @函数功能：从文件中读取用户信息至数组，函数返回记录总数
*/
int readPackageFromFile(package packageArray[],char *f)
{
    FILE *fp;
    package *p;
    int counter=0,k;

    fp=fopen(f,"rb");
    if (fp==NULL)
    {
        printf("文件不存在!\n");
        return 0;
    }
    else
    {
        while (1)
        {
            p=(package *)malloc(sizeof(package));
            k=fscanf(fp,"%s%s%s%s%s%s%s%s%s%s%s%s%s\n",&p->num,&p->recName,&p->rec_phone,&p->recAddress,&p->sendName,&p->send_phone,&p->sendAddress,&p->code,&p->status,&p->couName,&p->couPhone,&p->rec_userId,&p->send_userId);
            if (k!=-1)
            {
                packageArray[counter]=*p;
                counter++;
            }
            else
            {
                printf("快递文件载入失败!\n");
                break;

            }

        }
        fclose(fp);
        return counter;
    }
}
/*
    @函数名称： packageSearchByRecId    入口参数：package packageArray[],int packageTotal
    @函数功能：根据收件人id查找其所有快递
*/
int  packageSearchByRecId(package packageArray[], int packageTotal, char id[],package packageUserArrray[])
{
    int counter=0,i;
    int k;
    for(i=0;i<packageTotal;i++)
    {
        if(strcmp(packageArray[i].rec_userId,id)==0)
        {
            packageUserArrray[counter]=packageArray[i];
            counter++;
        }
    }
    return counter;
}
/*
    @函数名称： packageSearchByBlank    入口参数：package packageArray[],int packageTotal
    @函数功能：根据无取件码查找所有快递
*/
int  packageSearchByBlank(package packageArray[], int packageTotal,int addPackage[],package package1Array[])
{
    int counter=0,i;
    int k;
    for(i=0;i<packageTotal;i++)
    {
        if(strcmp(packageArray[i].code,"无")==0)
        {
            package1Array[counter]=packageArray[i];
           addPackage[counter]=i;;
            counter++;
        }
    }
    return counter;
}
/*
    @函数名称：addCode  入口参数：package packageArray[],int packageTotal
    @函数功能：为快递添加取件码
*/
 void addCode(package packageArray[],int packageTotal,history historyArray[],int *n)
 {
      time_t nowtime;
     history h;
     package package1array[1000];
    int addPackage[1000];
    int counter=packageSearchByBlank(packageArray,packageTotal,addPackage,package1array);
    printpackage(package1array,counter);
    int i;
    printf("请依次输入每个快递的取件码：");
    char num[20];
    for(i=0;i<counter;i++)
    {
        scanf("%s",&num);
        strcpy(packageArray[addPackage[i]].code,num);
        strcpy(h.num,packageArray[addPackage[i]].num);
        strcpy(h.recName,packageArray[addPackage[i]].recName);
        strcpy(h.rec_phone,packageArray[addPackage[i]].rec_phone);
        strcpy(h.sendName,packageArray[addPackage[i]].sendName);
        strcpy(h.send_phone,packageArray[addPackage[i]].send_phone);
        strcpy(h.couName,packageArray[addPackage[i]].couName);
        strcpy(h.couPhone,packageArray[addPackage[i]].couPhone);
        strcpy(h.status,packageArray[addPackage[i]].status);
        strcpy(h.time,ctime(&nowtime));
        historyArray[*n+i]=h;
    }
    *n+=counter;
    writePackageToFile(packageArray,packageTotal,"package.txt");
    printf("成功为[%d]个快递添加取件码.\n",counter);
    writeHistoryToFile(historyArray,*n,"history.txt");
 }

/*
    @函数名称
    @函数

*/
/*
    @函数名称：readHistoryFromFile    入口参数：package packageArray[],char *f
    @函数功能：从文件中读取用户信息至数组，函数返回记录总数
*/
int readHistoryFromFile(history historyArray[],char *f)
{
    FILE *fp;
    history *p;
    int counter=0,k;
    char s1[20];
    char s2[20];
    char s3[20];
    fp=fopen(f,"rb");
    if (fp==NULL)
    {
        printf("文件不存在!\n");
        return 0;
    }
    else
    {
        while (1)
        {
            p=(history *)malloc(sizeof(history));
            k=fscanf(fp,"%s%s%s%s%s%s%s%s%s%s%s%s\n",&p->num,&p->recName,&p->rec_phone,&p->sendName,&p->send_phone,&p->status,&p->couName,&p->couPhone,&p->time,&s1,&s2,&s3);
            strcat(p->time,s1);
            strcat(p->time,s2);
            strcat(p->time,"_");
            strcat(p->time,s3);
            if (k!=-1)
            {
                historyArray[counter]=*p;
                counter++;
            }
            else
            {
                printf("快递文件载入失败!\n");
                break;

            }

        }
        fclose(fp);
        return counter;
    }
}

/*
    @函数名称：writeHistoryToFile   入口参数：
    @函数功能：将历史记录存入文件
*/
void writeHistoryToFile(history historyArray[],int historyTotal,char *f)
{
    FILE *fp;
    history *p;
    fp=fopen(f,"w");
    int i;
    if (fp!=NULL)
    {
       for(i=0;i<historyTotal;i++)
        {
            p=(history *)malloc(sizeof(history));
            *p=historyArray[i];
            if(fprintf(fp,"%s   %s  %s  %s  %s  %s  %s  %s  %s\n",&p->num,&p->recName,&p->rec_phone,&p->sendName,&p->send_phone,&p->status,&p->couName,&p->couPhone,&p->time)==0)
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
    @函数名称：printhistory   入口参数：package packageArray[],int packageTotal
    @函数功能：将历史记录信息分页显示在屏幕上
*/
void printhistory(history historyArray[],int historyTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (historyTotal>0)
    {   totalPage=(historyTotal-1)/10;                     //每页显示10条记录
        if (totalPage*10<historyTotal-1) totalPage++;     //计算总页数
        for (i=historyTotal-1;i>=0;)
        {   system("cls");
            gotox(6);           //到第6行
            printf("%s\n","菜鸟驿站管理系统-->显示快递历史记录信息");
            for (k=0;k<140;k++)
                printf("-");
            printf("\n");
            page++;
            printf("%12s%15s%15s%15s%15s%10s%20s%20s%20s\n","快递单号","收件人姓名","收件人电话","寄件人姓名","寄件人电话","快递状态","快递员姓名","快递员电话","时间");
            for (k=0;k<140;k++)  putchar('-');
            printf("\n");

            for (j=0;j<10&&i>=0;j++)
            {

                printf("%12s",historyArray[i].num);
                printf("%15s",historyArray[i].recName);
                printf("%15s",historyArray[i].rec_phone);
                printf("%15s",historyArray[i].sendName);
                printf("%15s",historyArray[i].send_phone);
                printf("%10s",historyArray[i].status);
                 printf("%20s",historyArray[i].couName);
                printf("%20s",historyArray[i].couPhone);

                printf("%20s\n",historyArray[i].time);
                i--;
            }
            for (k=0;k<140;k++)  putchar('-');
            printf("\n");
            printf("第%d页，共%d页，上一页（↑）  下一页（↓），ESC键退出\n",page,totalPage);
            ch=getch();
            if (27==ch) return ;
            if (0==ch||0xe0==ch) ch|=getch()<<8;    //非字符键
            if (0x48e0==ch)     //向上键（↑）
            {
                    i=i+j;
                    if (i+10<historyTotal)
                        { i=i+10; page-=2;}
                    else
                        {i=historyTotal-1; page=0;}
            }
        }
    }
}






