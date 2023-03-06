void userSystem(char currentUserId[]);

void userSystem(char currentUserId[])
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
    package packageUserArray[MAX_PACKAGE];
    int packageUserTotal=packageSearchByRecId(packageArray,packageTotal,currentUserId,packageUserArray);
     while (loop==1)
    {
        system("cls");
        printf("%s:",userArray[pos].nickname);  //��ʾ��ǰ�û�����
        showtime(0);                        //��ʾ��ӭ����
        c=menuUser();  //��ʾ���Ա��ɫ�˵�
        switch(c)
        {
            case    1:  //�޸ĸ�����Ϣ
                        system("cls");
                        modifyUserInfo(userArray,userTotal,currentUserId);
                         system("pause");
                        break;
            case    2:  //�鿴�ҵĿ��
                        system("cls");
                        printMyPackage(packageArray,packageTotal,currentUserId);
                        system("pause");
                        break;
            case    3:  //ȡ��

                        system("cls");
                        getPackage(packageArray,packageTotal,currentUserId,historyArray,&historyTotal);
                        system("pause");
                        break;
            case    4://�ļ�
                        system("cls");
                        inputPackage(userArray,userTotal,packageArray,&packageTotal,historyArray,&historyTotal);
                        writePackageToFile(packageArray,packageTotal,"package.txt");
                        system("pause");
                        break;
            case    5:  //�޸ĵ�¼����
                        system("cls");
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


void printMyPackage(package packageArray[],int packageTotal,char currentUserId[])
{
    int c,loop=1;
     package packageUserArray[MAX_PACKAGE];
    int packageUserTotal=packageSearchByRecId(packageArray,packageTotal,currentUserId,packageUserArray);
     package packageSendArray[MAX_PACKAGE];
    int packageSendTotal=packageSearchBySendId(packageArray,packageTotal,currentUserId,packageSendArray);
    while(loop==1)
    {
         system("cls");
        c=menu1();
             switch(c)
        {
            case    1:  //���յ���
                         system("cls");
                        printpackage(packageUserArray,packageUserTotal);
                        system("pause");
                        break;
            case    2:  //�Ҽĳ���
                         system("cls");
                        printpackage(packageSendArray,packageSendTotal);
                        system("pause");
                        break;
            default:    //
                        loop=0;
                        break;
        }
    }
    return ;
}
/*
    @�������ƣ� packageSearchByStatus    ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ���������δȡ�����
*/
int  packageSearchByStatus(package packageArray[], int packageTotal,package package1Arrray[],int getPackage[], char id[])
{
    int counter=0,i;
    int k;
    for(i=0;i<packageTotal;i++)
    {
        if((strcmp(packageArray[i].status,"�ѵ�վ")==0)&&(strcmp(packageArray[i].rec_userId,id)==0))
        {
            getPackage[counter]=i;
            package1Arrray[counter]=packageArray[i];
            counter++;
        }
    }
    return counter;
}
/*
    @�������ƣ� getPackage    ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ�ȡ�����
*/

void getPackage(package packageArray[],int packageTotal,char id[],history historyArray[],int *n)
{
    time_t nowtime;
    package package1Array[1000];
    int getPackage[1000];
    int counter=packageSearchByStatus(packageArray,packageTotal,package1Array,getPackage,id);
    printpackage(package1Array,counter);
    printf("�밴���ѡ��Ҫȡ���Ŀ�ݣ�����0ȡ������δȡ�����,����-1������\n��");
    int num;
    int i;
    int j=0;
    history h;
    scanf("%d",&num);
    if(num==0)
    {
        for(i=0;i<counter;i++)
        {
           strcpy(packageArray[getPackage[i]].status,"��ȡ��");
            //strcpy(packageArray[getPackage[i]].code,num);
            strcpy(h.num,packageArray[getPackage[i]].num);
            strcpy(h.recName,packageArray[getPackage[i]].recName);
            strcpy(h.rec_phone,packageArray[getPackage[i]].rec_phone);
            strcpy(h.sendName,packageArray[getPackage[i]].sendName);
            strcpy(h.send_phone,packageArray[getPackage[i]].send_phone);
            strcpy(h.couName,packageArray[getPackage[i]].couPhone);
            strcpy(h.couPhone,packageArray[getPackage[i]].couPhone);
            strcpy(h.status,packageArray[getPackage[i]].status);
            strcpy(h.time,ctime(&nowtime));
            historyArray[*n+i]=h;
        }
         *n+=counter;
        writePackageToFile(packageArray,packageTotal,"package.txt");
        printf("�ɹ�ȡ��[%d]�����.\n",counter);
        writeHistoryToFile(historyArray,*n,"history.txt");
        return ;
    }else
    {
        while(num!=-1&&num<=counter)
        {
            strcpy(packageArray[getPackage[num-1]].status,"��ȡ��");
            strcpy(packageArray[getPackage[num-1]].code,num);
            strcpy(h.num,packageArray[getPackage[num-1]].num);
            strcpy(h.recName,packageArray[getPackage[num-1]].recName);
            strcpy(h.rec_phone,packageArray[getPackage[num-1]].rec_phone);
            strcpy(h.sendName,packageArray[getPackage[num-1]].sendName);
            strcpy(h.send_phone,packageArray[getPackage[num-1]].send_phone);
            strcpy(h.couName,packageArray[getPackage[num-1]].couName);
            strcpy(h.couPhone,packageArray[getPackage[num-1]].couPhone);
            strcpy(h.status,packageArray[getPackage[num-1]].status);
            strcpy(h.time,ctime(&nowtime));
            historyArray[*n+j]=h;
            j++;
            scanf("%d",&num);
        }
        if(j>0)
        {
            *n+=j;
            writePackageToFile(packageArray,packageTotal,"package.txt");
            printf("�ɹ�ȡ��[%d]�����.\n",j);
            writeHistoryToFile(historyArray,*n,"history.txt");
            return ;
        }else return ;

    }


}
/*
    @�������ƣ�inputPackage()   ��ڲ�����package packageArray[],int *n
    @�������ܣ���ӿ����Ϣ
*/
void inputPackage(user userArray[],int userTotal,package packageArray[],int *n,history historyArray[],int *historyTotal)
{
    time_t nowtime;
    int b=*n;
    int counter=0,i=0,j;
    package account;
    history h;
    printf("��ѡ��Ҫ�ĳ��Ŀ�ݵĸ�����[            ]\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%d",&j);
    if (*n<MAX_USER)
        {
            while (i<j)
            {
                system("cls");
                displayTopic("������վ����ϵͳ-->�û��ļ�");
                printf("�ռ���\t�ռ����ֻ�\t�ռ��˵�ַ\t�ļ���\t�ļ����ֻ�\t�ļ��˵�ַ\n");
                printf("--------------------------------------------------------------------------------\n");
                scanf("%s",&account.recName);                                 //�����ռ���
                scanf("%s",&account.rec_phone);                   //
                scanf("%s",&account.recAddress);                   //
                scanf("%s",&account.sendName);                   //
                scanf("%s",&account.send_phone);
                scanf("%s",&account.sendAddress);
                char num[20];
                getNum(num,8);
                strcpy(account.num,num);
                strcpy(account.code,"��");
                strcpy(account.status,"������");
                int k1=userSearchByPhone(userArray,userTotal,account.rec_phone);
                strcpy(account.rec_userId,userArray[k1].userId);
                int k2=userSearchByPhone(userArray,userTotal,account.send_phone);
                strcpy(account.send_userId,userArray[k2].userId);
                packageArray[*n]=account;
                i++;
                (*n)++;
                counter++;
                printf("success...\n");
                system("pause");
                if (*n==MAX_USER) break;                            //��������
                }
            }
            user courierArray[100];
           int k=printCourier(userArray,userTotal,courierArray);
           int m;
           scanf("%d",&m);
           for(i=0;i<counter;i++)
           {
                strcpy(packageArray[b+i].couName,courierArray[m-1].nickname);
                strcpy(packageArray[b+i].couPhone,courierArray[m-1].phone);
                strcpy(h.num,packageArray[b+i].num);
                strcpy(h.recName,packageArray[b+i].recName);
                strcpy(h.rec_phone,packageArray[b+i].rec_phone);
                strcpy(h.sendName,packageArray[b+i].sendName);
                strcpy(h.send_phone,packageArray[b+i].send_phone);
                //strcpy(h.couName,packageArray[b+i].couName);
               // strcpy(h.couPhone,packageArray[b+i].couPhone);
               // strcpy(h.status,packageArray[b+i].status);
               // strcpy(h.time,ctime(&nowtime));
                //historyArray[*historyTotal+i]=h;
           }
            *historyTotal+=counter;
            writeHistoryToFile(historyArray,*historyTotal,"history.txt");
            printf("�ɹ�����%d���ʻ���Ϣ!\n",counter);
            system("pause");
}
/*
    @�������ƣ�getNUm   ��ڲ���:char num[],int n
    @�������ܣ�����nλ�����
*/
void getNum(char num[],int n)
{
    char str[]="123456789";
    int i;
    srand(time(NULL));
    for (i=0;i<n;i++)
        num[i]=str[rand()%9];
    num[n]='\0';
}
/*
*/

int printCourier(user userArray[],int userTotal,user courierArray[])
{
    int i;
    int j;
    printf("��ѡ����Ա��\n");
    for (j=0;j<50;j++)
                printf("-");
    printf("\n");
    printf("%10s%12s%12s\n","���","����","�ֻ���");
     for (j=0;j<50;j++)
                printf("-");
    printf("\n");
    int counter=0;
    for(i=0;i<userTotal;i++)
    {
        if(userArray[i].role==1)
        {
            printf("%10d",counter+1);
            printf("%12s",userArray[i].nickname);
            printf("%12s\n",userArray[i].phone);
            courierArray[counter]=userArray[i];
            counter++;
        }
    }
    for (j=0;j<50;j++)
                printf("-");
    printf("\n");
    return counter;
}
int userSearchByPhone(user userArray[],int userTotal,char phone[])
{
     int left=0,right=userTotal-1,mid;
    int k;
    while (left<=right)
    {
        mid=(left+right)/2;                     //����
        k=strcmp(userArray[mid].phone,phone);
        if ( k==0)
            return mid;
        else
            if (k<0)
                left=mid+1;
            else
                right=mid-1;
    }
    return -1;                                  //����ʧ��
}
/*
    @�������ƣ� packageSearchBySendId    ��ڲ�����package packageArray[],int packageTotal
    @�������ܣ����ݼļ���id���������п��
*/
int  packageSearchBySendId(package packageArray[], int packageTotal, char id[],package packageSendArrray[])
{
    int counter=0,i;
    int k;
    for(i=0;i<packageTotal;i++)
    {
        if(strcmp(packageArray[i].send_userId,id)==0)
        {
            packageSendArrray[counter]=packageArray[i];
            counter++;
        }
    }
    return counter;
}

