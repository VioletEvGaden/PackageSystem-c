#include "packagesystem.h"


char *getRole(int code);                                //���ݴ����ȡ�û���ɫ                          //���ݴ����ȡϵ������
int login(char currentUserId[]);
void enterSystem(int c,char currentUserId[]);
void encryption(char password[]) ;    //����
void decryption(char password[]) ;    //����
int readUserFromFile(user userArray[],char *f);                 //���ļ������û���Ϣ
int userSearch(user userArray[], int userTotal, char id[]);         //�����û���Ϣ
#include "admin.c"
#include "courier.c"
#include "user.c"



int main()
{
    int c,loop=1;
     user userArray[MAX_USER];   //�û�����
    int userTotal;              //�û�����
      userTotal=readUserFromFile(userArray,"user.txt");   //���ļ��ж����û���Ϣ
    char currentUserId[LENGTH_OF_USERID+1];             //��ǰ�û��ʺ�
    while (loop==1)
    {
        system("cls");  //�����Ļ
        c=mainMenu();   //��ʾ��¼�˵�
        switch(c)
        {
            case    1:  //��¼ϵͳ
                        c=login(currentUserId);         //���������֤�����������û���ɫ
                        enterSystem(c,currentUserId);   //��ʾ��ͬ��ɫ��Ӧ�Ĳ˵�
                        break;
            case   2://ע��
                     inputUser(userArray,&userTotal);
            default: //�˳�ϵͳ
                        loop=0;
                        break;
        }
        showtime(1);
    }
    return 0;
}


/*
    @�������ƣ�getVerificationCode   ��ڲ���:char verificationCode[],int n
    @�������ܣ�����nλ��֤��
*/
void getVerificationCode(char verificationCode[],int n)
{
    char str[]="2323456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //0,1������ĸ��o���롮l'����������
    int i;
    srand(time(NULL));
    for (i=0;i<n;i++)
        verificationCode[i]=str[rand()%62];
    verificationCode[n]='\0';
}

/*
    @�������ƣ�inputPassWord         ��ڲ�����char password[],int n
    @�������ܣ�������󳤶�Ϊn������
*/
void inputPassWord(char password[],int n)
{
    int i;
    char c;
    i=0;
    while (i<n)
    {
        c=getch();
        if (c=='\r') break;         //�س���
        if (c==8 && i>0 )           //�˸��
            {   printf("\b \b");
                i--;
            }
         else
            {   password[i++]=c;    //��Ч�����ַ�
                printf("*");        //����*��
            }
    }
    printf("\n");
    password[i]='\0';
}
/*
    @�������ƣ�login     ��ڲ�������
    @�������ܣ��û������֤��Ϣ�������û���ɫ
*/
int login( char currentUserId[])
{
    user userArray[MAX_USER];               //�û�����
    int userTotal;                          //�û�����
    int counter=3;
    char verificationCode[5];                //�����֤��
    char inputVerificationCode[5];           //�����û��������֤��
    char originalPassWord[LENGTH_OF_PASS+1];
    char password[LENGTH_OF_PASS+1];
    int pos;

    userTotal=readUserFromFile(userArray,"user.txt");   //���ļ��ж����û���Ϣ\b
    while (counter>0)
    {   system("cls");
        counter--;
        displayTopic("������վ����ϵͳ-->�û���¼");
        printf("�û�����[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s",currentUserId);
        printf("��  �룺[           ]\b\b\b\b\b\b\b\b\b\b\b\b");
        inputPassWord(password,7);
        getVerificationCode(verificationCode,4);
        printf("��֤�룺[           ] %s\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b",verificationCode);
        scanf("%s",inputVerificationCode);

        pos=userSearch(userArray,userTotal,currentUserId);
        if (pos==-1)
            {   printf("���û������ڣ�����%d�ε�¼���ᡣ\n",counter);
                getch();
                continue;
            }
        else
        {   strcpy(originalPassWord,userArray[pos].password);
            decryption(originalPassWord);        //����ԭʼ����
            if (strcmp(originalPassWord,password)!=0)
                {   printf("������������󣬻���%d�ε�¼���ᡣ\n",counter);
                    getch();
                    continue;
                }
            else
                if ( strcasecmp(verificationCode,inputVerificationCode)!=0)
                {   printf("�������֤�����󣬻���%d�ε�¼���ᡣ\n",counter);
                    getch();
                    continue;
                }
            else
                return userArray[pos].role;     //�����û���ɫ
        }
    }
    return -1;       //��¼ʧ��
}
/*
    @�������ƣ�readUserFromFile    ��ڲ�����user userArray[],char *f
    @�������ܣ����ļ��ж�ȡ�û���Ϣ�����飬�������ؼ�¼����
*/
int readUserFromFile(user userArray[],char *f)
{
    FILE *fp;
    user *p;
    int counter=0,k;

    fp=fopen(f,"rb");
    if (fp==NULL)
    {
        printf("δ�ҵ��ļ�!\n");
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
                printf("�û��ļ�����ʧ��!\n");
                break;

            }

        }
        fclose(fp);
        return counter;
    }
}

/*
    @�������ƣ�userSearch     ��ڲ�����user userArray[],int userTotal
    @�������ܣ����ö��ֲ��ҷ���userArray[]�в����û��ʺ�Ϊid[]�ļ�¼λ�ã�����ʧ�ܷ���-1
*/
int userSearch(user userArray[], int userTotal, char id[])
{
    int left=0,right=userTotal-1,mid;
    int k;
    while (left<=right)
    {
        mid=(left+right)/2;                     //����
        k=strcmp(userArray[mid].userId,id);
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
    @�������ƣ�enterSystem     ��ڲ�������
    @�������ܣ������û��Ľ�ɫ���ò�ͬ�Ĺ�����ϵͳ
*/

void enterSystem(int c,char currentUserId[])
{
     switch(c)
    {
        case 0: //c==0��ʾϵͳ����Ա�û�
                adminSystem(currentUserId);
                break;
        case 1://c==1��ʾ���Ա��¼
                courierSystem(currentUserId);
                break;
        case 2://c==2��ʾ��ͨ�û�
                userSystem(currentUserId);
                break;
        default:
                break;
    }

}
/*
    @�������ƣ�encryption        �������ܣ���������м���
*/
void encryption(char password[])     //����
{
    int i=0;
    int count=strlen(password);
    while (password[i]!='\0')                     //password����
    {
        password[i]=password[i]^0xba;
        i++;
    }

}

/*
    @�������ƣ�decryption        �������ܣ���������н���
*/
void decryption(char password[])     //����
{
    int i=0;
    while (password[i]!='\0')                  //password����
    {
        password[i]=password[i]^0xba;
        i++;
    }

}
/*
    @�������ƣ�getRole     @�������ܣ����ݽ�ɫ�����ȡ��ɫ����
*/
char *getRole(int code)
{

    return roleName[code];
}


