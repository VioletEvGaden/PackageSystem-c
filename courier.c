
void courierSystem(char currentUserId[]);

/*
    @�������ƣ�courierSystem    ��ڲ�������
    @�������ܣ����Ա��ɫ�����ӳ���
*/
void courierSystem(char currentUserId[])
{
    int c,loop=1;

    user userArray[MAX_USER];   //�û�����
    package packageArray[MAX_PACKAGE];   //�������
    history historyArray[MAX_PACKAGE];   //�������
    int userTotal;              //�û�����
    int packageTotal;           //�������
    int historyTotal;
    int pos;
    userTotal=readUserFromFile(userArray,"user.txt");   //���ļ��ж����û���Ϣ
    packageTotal=readPackageFromFile(packageArray,"package.txt");   //���ļ��ж�ȡ�����Ϣ
    historyTotal=readHistoryFromFile(historyArray,"history.txt");
    pos=userSearch(userArray,userTotal,currentUserId);
    while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].nickname);  //��ʾ��ǰ���Ա����
        showtime(0);                        //��ʾ��ӭ����
        c=menuCourier();  //��ʾ���Ա��ɫ�˵�
        switch(c)
        {
            case    1:  //�޸ĸ�����Ϣ
                        system("cls");
                        modifyUserInfo(userArray,userTotal,currentUserId);
                        break;
            case    2:  //��������Ϣ
                        printpackage(packageArray,packageTotal);
                        system("pause");
                        break;

            case    3:  //�޸Ŀ����Ϣ
                        system("cls");
                        char num[20];
                        printf("������Ҫ�޸ĵĿ�ݵ���:");
                        scanf("%s",&num);
                        modifyPackageInfo(packageArray,packageTotal,num);
                        break;
            case    4:  //�������������ݹ���ӿ�ݣ�
                        importpackage(packageArray,&packageTotal,userArray[pos]);
                        printpackage(packageArray,packageTotal);
                        system("pause");
                        break;
            case    5://���ȡ����
                        system("cls");
                        addCode(packageArray,packageTotal,historyArray,&historyTotal);
                        system("pause");
                        break;
            case    6: //�鿴�����ʷ
                        system("cls");
                        printhistory(historyArray,historyTotal);
                        system("pause");
                        break;

            case    7:  //�޸ĵ�¼����
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            default:    //ע����¼
                        loop=0;
                        break;
        }
    }
    return;
}



/*
    @�������ƣ�printpackage     ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ����û���Ϣ��ҳ��ʾ����Ļ��
*/
void printpackage(package packageArray[],int packageTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (packageTotal>0)
    {   totalPage=(packageTotal-1)/10;                     //ÿҳ��ʾ10����¼
        if (totalPage*10<packageTotal-1) totalPage++;     //������ҳ��
        for (i=0;i<packageTotal;)
        {   system("cls");
            gotox(6);           //����6��
            printf("%s\n","������վ����ϵͳ-->��ʾ�����Ϣ");
            for (k=0;k<150;k++)
                printf("-");
            printf("\n");
            page++;
            printf("%10s%12s%15s%15s%20s%15s%15s%20s%10s%12s\n","���","��ݵ���","�ռ�������","�ռ��˵绰","�ռ��˵�ַ","�ļ�������","�ļ��˵绰","�ļ��˵�ַ","ȡ����","���״̬");
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
            printf("��%dҳ����%dҳ����һҳ������  ��һҳ��������ESC���˳�\n",page,totalPage);
            ch=getch();
            if (27==ch) return ;
            if (0==ch||0xe0==ch) ch|=getch()<<8;    //���ַ���
            if (0x48e0==ch)     //���ϼ�������
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
    @�������ƣ�importpackage   ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ����ļ�����������������Ϣ
*/
void importpackage(package packageArray[],int *n,user p )
{
    FILE *fp1,*fp2;
    char file[20];
    int counter=0;
    system("cls");
    displayTopic("������վ����ϵͳ-->����������");
    printf("������Ҫ������ļ�����[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",file);
    fp1=fopen(file,"r");            //�򿪵����ļ�
    fp2=fopen("package.txt","ab");     //�򿪿�������ļ�
    if (fp1!=NULL && fp2!=NULL)
    {
         if (*n<MAX_PACKAGE)
         {
             while (!feof(fp1))
             {
                 fscanf(fp1,"%s",packageArray[*n+counter].num);   //�����ݵ���
                 fscanf(fp1,"%s",packageArray[*n+counter].recName);   //�����ռ�������
                 fscanf(fp1,"%s",packageArray[*n+counter].rec_phone);   //�����ռ����ֻ���
                 fscanf(fp1,"%s",packageArray[*n+counter].recAddress);   //�����ռ��˵�ַ
                 fscanf(fp1,"%s",packageArray[*n+counter].sendName);   //����ļ�������
                 fscanf(fp1,"%s",packageArray[*n+counter].send_phone);   //����ļ����ֻ���
                 fscanf(fp1,"%s",packageArray[*n+counter].sendAddress);   //����ļ��˵�ַ
                 fscanf(fp1,"%s",packageArray[*n+counter].code);         //����ȡ����
                 strcpy(packageArray[*n+counter].status,"�ѵ�վ");//������ݵ�״̬Ϊ��ȡ
                 strcpy(packageArray[*n+counter].couName,p.nickname);
                 strcpy(packageArray[*n+counter].couPhone,p.phone);
                 fscanf(fp1,"%s",packageArray[*n+counter].rec_userId);         //�����ռ���id
                 fscanf(fp1,"%s",packageArray[*n+counter].send_userId);         //����ļ���id
                 counter++;
                 if (*n+counter>=MAX_PACKAGE)
                        break;
             }
             writePackageToFile(packageArray,*n+counter,"package.txt");
             //fwrite(packageArray+*n, sizeof(package),counter,fp2);    //���µ���Ŀ��д�����ļ�
             *n+=counter;
             printf("��������[%d]�����,�������[%d].\n",counter,*n);
             system("pause");
         }
        fclose(fp1);
        fclose(fp2);
    }
    else  {
                printf("������ļ����󣬵���ʧ�ܣ�\n");
                system("pause");
          }
}
/*
    @�������ƣ�modifyPackageInfo    @��ڲ�����package packageArray[],int packageTotal
    @�������ܣ��޸Ŀ����Ϣ
*/
void  modifyPackageInfo(package packageArray[],int packageTotal,char num[])
{
    int pos,i;
    char recName[20];                   //�ռ�������
    char rec_phone[20];              //�ռ����ֻ�
    char recAddress[20];                       //�ռ��˵�ַ
    char sendName[20];                   //�ļ�������
    char send_phone[20];              //�ļ����ֻ�
    char sendAddress[20];                        //�ļ��˵�ַ
    char rec_userId [20];                    //�ռ���id
    char send_userId  [20] ;                  //�ļ���id
    int flag=0;
    pos=packageSearchByNum(packageArray,packageTotal,num);
    gotox(6);           //����6��
    printf("%s\n","������վ����ϵͳ-->�޸Ŀ����Ϣ");
    for (i=0;i<100;i++)
        printf("-");
    printf("\n");
    printf("%15s%15s%18s%15s%15s%18s\n","�ռ�������","�ռ����ֻ�","�ռ��˵�ַ","�ļ�������","�ļ����ֻ�","�ļ��˵�ַ");
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

    printf("�����޸��ռ�������,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    getchar();
    gets(recName);
    printf("�����޸��ռ����ֻ�,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();
    gets(rec_phone);
    printf("�����޸��ռ��˵�ַ,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();
    gets(recAddress);
    printf("�����޸ļļ�������,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //ȥ�����̻������еĻس���
    gets(sendName);
    printf("�����޸ļļ����ֻ�,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //ȥ�����̻������еĻس���
    gets(send_phone);
    printf("�����޸ļļ��˵�ַ,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //ȥ�����̻������еĻس���
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
    if(flag==1)   writePackageToFile(packageArray,packageTotal,"package.txt");       //����s
}
/*
    @�������ƣ� packageSearchByNum    ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ����ݵ��Ų��ҿ��
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
    return -1;                                  //����ʧ��
}
/*
    @�������ƣ�writePackageToFile   ��ڲ�����
    @�������ܣ����û���Ϣ�����ļ�
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
                printf("����ʧ��!\n");
                return;

            }
        }
        free(p);
        fclose(fp);
        printf("����ɹ�!\n");

    }
    else
        printf("����ʧ�ܣ�");
}
/*
    @�������ƣ�readPackageFromFile    ��ڲ�����package packageArray[],char *f
    @�������ܣ����ļ��ж�ȡ�û���Ϣ�����飬�������ؼ�¼����
*/
int readPackageFromFile(package packageArray[],char *f)
{
    FILE *fp;
    package *p;
    int counter=0,k;

    fp=fopen(f,"rb");
    if (fp==NULL)
    {
        printf("�ļ�������!\n");
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
                printf("����ļ�����ʧ��!\n");
                break;

            }

        }
        fclose(fp);
        return counter;
    }
}
/*
    @�������ƣ� packageSearchByRecId    ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ������ռ���id���������п��
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
    @�������ƣ� packageSearchByBlank    ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ�������ȡ����������п��
*/
int  packageSearchByBlank(package packageArray[], int packageTotal,int addPackage[],package package1Array[])
{
    int counter=0,i;
    int k;
    for(i=0;i<packageTotal;i++)
    {
        if(strcmp(packageArray[i].code,"��")==0)
        {
            package1Array[counter]=packageArray[i];
           addPackage[counter]=i;;
            counter++;
        }
    }
    return counter;
}
/*
    @�������ƣ�addCode  ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ�Ϊ������ȡ����
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
    printf("����������ÿ����ݵ�ȡ���룺");
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
    printf("�ɹ�Ϊ[%d]��������ȡ����.\n",counter);
    writeHistoryToFile(historyArray,*n,"history.txt");
 }

/*
    @��������
    @����

*/
/*
    @�������ƣ�readHistoryFromFile    ��ڲ�����package packageArray[],char *f
    @�������ܣ����ļ��ж�ȡ�û���Ϣ�����飬�������ؼ�¼����
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
        printf("�ļ�������!\n");
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
                printf("����ļ�����ʧ��!\n");
                break;

            }

        }
        fclose(fp);
        return counter;
    }
}

/*
    @�������ƣ�writeHistoryToFile   ��ڲ�����
    @�������ܣ�����ʷ��¼�����ļ�
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
                printf("����ʧ��!\n");
                return;
            }
        }
        free(p);
        fclose(fp);
        printf("����ɹ�!\n");

    }
    else
        printf("����ʧ�ܣ�");
}

/*
    @�������ƣ�printhistory   ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ�����ʷ��¼��Ϣ��ҳ��ʾ����Ļ��
*/
void printhistory(history historyArray[],int historyTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (historyTotal>0)
    {   totalPage=(historyTotal-1)/10;                     //ÿҳ��ʾ10����¼
        if (totalPage*10<historyTotal-1) totalPage++;     //������ҳ��
        for (i=historyTotal-1;i>=0;)
        {   system("cls");
            gotox(6);           //����6��
            printf("%s\n","������վ����ϵͳ-->��ʾ�����ʷ��¼��Ϣ");
            for (k=0;k<140;k++)
                printf("-");
            printf("\n");
            page++;
            printf("%12s%15s%15s%15s%15s%10s%20s%20s%20s\n","��ݵ���","�ռ�������","�ռ��˵绰","�ļ�������","�ļ��˵绰","���״̬","���Ա����","���Ա�绰","ʱ��");
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
            printf("��%dҳ����%dҳ����һҳ������  ��һҳ��������ESC���˳�\n",page,totalPage);
            ch=getch();
            if (27==ch) return ;
            if (0==ch||0xe0==ch) ch|=getch()<<8;    //���ַ���
            if (0x48e0==ch)     //���ϼ�������
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






