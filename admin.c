

void adminSystem(char currentUserId[]);

/*
    @�������ƣ�adminSystem    ��ڲ�������
    @�������ܣ�ϵͳ����Ա��ɫ�����ӳ���
*/
void adminSystem(char currentUserId[])
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
        printf("%s:",userArray[pos].nickname);  //��ʾ��ǰ�л�����
        showtime(0);                        //��ʾ��ӭ����
        c=menuAdmin();  //��ʾϵͳ����Ա��ɫ�˵�
        switch(c)
        {
            case    1:  //��ʾ�û���Ϣ
                        printUser(userArray,userTotal);
                        system("pause");
                        break;
            case    2:  //�����û���Ϣ
                        inputUser(userArray,&userTotal);
                        writeUserToFile(userArray,userTotal,"user.txt");
                        break;
            case    3:  //ɾ���û���Ϣ
                        deleteUser(userArray,&userTotal,currentUserId);
                        writeUserToFile(userArray,userTotal,"user.txt");
                        printUser(userArray,userTotal);
                        break;

           // case    4:  //��ʾͼ����Ϣ
                       // printBook(bookArray,bookTotal);
                       // system("pause");
                       // break;
            case    4:  //�޸ĸ�����Ϣ
                        system("cls");
                        modifyUserInfo(userArray,userTotal,currentUserId);
                        break;
            case    5:  //��ʼ���û�����
                        printUser(userArray,userTotal);
                        initPassWord(userArray,userTotal);
                        break;
            case    6:  //�޸ĵ�¼����
                        modifyPassWord(userArray,userTotal,currentUserId);
                        system("pause");
                        break;
            case    7:  //ϵͳ����
                        system("cls");
                        displayTopic("������վ����ϵͳ�������ݱ���");
                        backupUser(userArray,userTotal);
                        backupPackage(packageArray,packageTotal);
                        backupHistory(historyArray,historyTotal);
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
    @�������ƣ�inputUser()   ��ڲ�����user userArray[],int *n
    @�������ܣ������û���Ϣ
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
                displayTopic("������վ����ϵͳ-->����û�");
                printf("�û�����Ϊqʱ��������[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
                scanf("%s",account.userId);                                         //�����ʺ�
                if (account.userId[0]=='q')
                                break;
                if (userSearch(userArray,*n,account.userId)==-1)   //���Ҹ��˺��Ƿ����
                {
                        printf("�ǳ�\t�绰\t��ɫ����\n");
                        printf("---------------------------------\n");
                        scanf("%s",&account.nickname);                                 //�����ǳ�
                        scanf("%s",&account.phone);                   //����绰����
                        scanf("%d",&account.role);                                 //�����ɫ����

                        strcpy(account.email,"mmm");                                     //��ʼemailΪmmm
                        strcpy(account.password,"123456");                  //��ʼ����Ϊ"123456"
                        encryption(account.password);                           //����
                        j=*n-1;
                        while ( j>=0 &&   strcmp(userArray[j].userId,account.userId) >0   )
                                {
                                    userArray[j+1]=userArray[j];
                                    j--;
                                }
                        userArray[j+1]=account;                                     //���û��ʺ�����뵽�ʵ�λ��
                        (*n)++;
                        counter++;
                        printf("success...\n");
                        system("pause");
                        if (*n==MAX_USER) break;                            //��������
                }
                else
                    {
                            printf("���˺��Ѵ��ڣ����������룡\n");
                            system("pause");
                    }
            }
            printf("�ɹ�����%d���ʻ���Ϣ!\n",counter);
            system("pause");
        }
}

/*
    @�������ƣ�printUser     ��ڲ�����user userArray[],int userTotal
    @�������ܣ����û���Ϣ��ҳ��ʾ����Ļ��
*/
void printUser(user userArray[],int userTotal)
{   int i,j,k,page=0,totalPage;
    unsigned short ch;
    if (userTotal>0)
    {   totalPage=(userTotal-1)/10;                     //ÿҳ��ʾ10����¼
        if (totalPage*10<userTotal-1) totalPage++;     //������ҳ��
        for (i=0;i<userTotal;)
        {   system("cls");
            displayTopic("������վ����ϵͳ-->��ʾ�û�");
            page++;
            printf("%12s%9s%15s%11s","�û���","�ǳ�","�绰����","��ɫ");
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
    @�������ƣ�writeUserToFile   ��ڲ�����user userArray[],int userTotal,char *f
    @�������ܣ����û���Ϣ�����ļ�
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
    @�������ƣ�deleteUser    ��ڲ�����user userArray,int *n ,user currentUser[]
    @�������ܣ�ɾ���û���Ϣ
*/
void deleteUser(user userArray[],int *n,user currentUser[])
{
    char id[LENGTH_OF_USERID +1],ans;
    int pos,i;
    system("cls");
    printUser(userArray,*n);
    printf("������Ҫɾ�����û��ʺ�(���벻���ڵ��˺ŷ���)��[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",id);
    if (strcmp(id,currentUser)!=0)                      //����ɾ��ϵͳ����Ա�û�
    {
        pos=userSearch(userArray,*n,id);            //����λ��
        if (pos==-1)                                //����ʧ��
                    {   printf("�޴��û���\n");
                        system("pause");
                        return ;
                    }
        //if (userArray[pos].count!=0)
        //{
            //printf("���Ȼ�������ͼ�飬����ɾ�����û���\n");
            //system("pause");
           // return ;
        //}
        printf("���Ҫɾ����(y/n)");
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
        {       printf("����ɾ����ǰ�û���\n");
                system("pause");
                return ;
        }
}
/*
    @�������ƣ�modifyUserInfo    @��ڲ�����user userArray[],int userTotal,char userId[]
    @�������ܣ��޸��û���Ϣ��email��
*/
void  modifyUserInfo(user userArray[],int userTotal,char userId[])
{
    int pos,i;
    char email[16];
    char phone[16];
    char nickname[16];
    int flag=0;
    pos=userSearch(userArray,userTotal,userId);
    displayTopic("������վ����ϵͳ-->�޸ĸ�����Ϣ");
    printf("%12s%12s%15s%16s","�û���","�ǳ�","�绰����","��ɫ");
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

    printf("�����޸��ǳ�,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    getchar();
    gets(nickname);
    printf("�����޸ĵ绰,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();
    gets(phone);
    printf("�����޸�Email,������(ֱ�ӻس����޸�):[               ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    //getchar();              //ȥ�����̻������еĻس���
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
    if(flag==1)   writeUserToFile(userArray,userTotal,"user.txt");       //����s
}
/*
    @�������ƣ�modifyPassWord    ��ڲ�����user userArray[],int userTatal, char userId[]
    @�������ܣ��޸ĸ�������
*/
void modifyPassWord(user userArray[],int userTotal, char userId[])//�޸�����
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
    displayTopic("������վ����ϵͳ-->�޸�����");
    printf("ԭʼ���룺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password1,7);
    printf("�������룺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password2,7);
    printf("����һ�飺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    inputPassWord(password3,7);
    if (strcmp(originalPassWord,password1)!=0)
        printf("ԭʼ���������޸�ʧ�ܡ�\n");
    else
        if (strcmp(password2,password3)!=0)
            printf("������������벻һ�£��޸�ʧ�ܡ�\n");
        else  //�ɹ�
        {
            encryption(password2);
            strcpy(userArray[pos].password,password2);
            writeUserToFile(userArray,userTotal,"user.txt");
            printf("�����޸ĳɹ���\n");
        }
}
/*
    @�������ƣ�initPassWord  ��ڲ�����user userArray[],int userTotal
    @�������ܣ���ʼ���û�����
*/
void initPassWord(user userArray[],int userTotal)
{
    char ans,userId[LENGTH_OF_USERID +1];
    int pos,i;
    printf("�������û��ʺţ�[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s",userId);
    pos=userSearch(userArray,userTotal,userId);
    if (pos==-1)
    {   printf("�û������ڣ�\n");
        system("pause");
        return ;
    }
    else
    {
        printf("\033[40;31m��ʼ���˺�Ϊ%s\033[0m\n",userArray[pos].userId);;
        printf("ȷ�ϳ�ʼ��(y/n):[   ]\b\b\b");
        scanf(" %c",&ans);
        if (ans=='Y' || ans=='y')
            {
                strcpy(userArray[pos].password,"123456");
                encryption(userArray[pos].password);
                writeUserToFile(userArray,userTotal,"user.txt");
                printf("�Ѿ��ɹ���%s�˻������ʼ��Ϊ123456!\n\n",userArray[pos].userId);
                system("pause");
            }
        else
            return ;
    }
}
/*
    @�������ƣ�backupUser        ��ڲ�����user userArray[],int userTotal
    @�������ܣ������û���Ϣ
*/
void backupUser(user userArray[],int userTotal)
{
    char filename[30]="user_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".txt");
    printf("�û����ݱ�����:%s\n",filename);
    writeUserToFile(userArray,userTotal,filename);
}
/*
    @�������ƣ�backupUser        ��ڲ�����user userArray[],int userTotal
    @�������ܣ������û���Ϣ
*/
void backupPackage(package packageArray[],int packageTotal)
{
    char filename[30]="package_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".txt");
    printf("�û����ݱ�����:%s\n",filename);
    writePackageToFile(packageArray,packageTotal,filename);
}
/*
    @�������ƣ�backupUser        ��ڲ�����user userArray[],int userTotal
    @�������ܣ������û���Ϣ
*/
void backupHistory(history historyArray[],int historyTotal)
{
    char filename[30]="history_";
    time_t t;
    time(&t);
    strcat(filename,ctime(&t));
    strcpy(filename+strlen(filename)-15,".txt");
    printf("�û����ݱ�����:%s\n",filename);
    writeHistoryToFile(historyArray,historyTotal,filename);
}


