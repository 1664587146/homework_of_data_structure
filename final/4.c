/*
    [��������]
    ʵ�־������й��ܵļ��׹���ϵͳ��
    [����Ҫ��]
    ��1�������ļ��Դ����������и���Ա����Ϣ����Ա����Ϣ�о�Ӧ�����������ݣ�
        �������������ڡ���񡢵�ַ�����ڷ��������ڣ���������������
        Ҳ�ɸ���������Ϣ�������Ǳ���ġ�
    ��2��ʵ�����ݵ��ļ��洢�Ͷ�ȡ��
    ��3����ͼ�η�ʽ��ʾ���ס�
    ��4����ʾ��n �������˵���Ϣ��
    ��5������������ѯ�������Ա��Ϣ�������䱾�ˡ����ס����ӵ���Ϣ����
    ��6�����ճ������ڲ�ѯ��Ա������
    ��7����������������ȷ�����ϵ��
    ��8��ĳ��Ա��Ӻ��ӡ�
    ��9��ɾ��ĳ��Ա�����仹�к������һ��ɾ������
    ��10���޸�ĳ��Ա��Ϣ��
    ��11��Ҫ��������20����Ա�����ݣ��Խ�Ϊֱ�۵ķ�ʽ��ʾ��������ṩ�ĸ���ʽ�Ա��顣
    ��12������Ҫ���к������ʾ��ÿ�����ܿ��������˵���������ʾ�����������صĹ���Ҫ��
    ��13���洢�ṹ������ϵͳ����Ҫ��������ƣ�����Ҫ���������Ҫ�洢�������ļ��С�
    �������ݣ�Ҫ��ʹ��1��ȫ���Ϸ����ݣ�
    2���ֲ��Ƿ����ݡ����г�����ԣ��Ա�֤������ȶ���
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//�ļ����ͣ��ı��ļ�
//���ݽṹ�������ֵ���
typedef struct Person
{
    char name[20];
    //����
    int birthday[3];
    /* 
        birthday[0] ��
        birthday[1] ��
        birthday[2] ��
    */
    int marriage;
    /*
        ��� marriage = 1�����
            marriage = 0δ��
    */
    char name_of_mate[20];
    //��ż������
    char address[20];
    int generation;
    //�ڼ���
    int alive;
    /*
        ���ڷ� alive = 1������
        alive = 0 ȥ��
    */
    int death_date[3];
    //�������ĺ����birthdayһ��
    //����������������Ϊ��
    int flag_self;
    //��ʾ����ڵ��Ƿ����ã�flag_self��ʾ��Ч
    //����ɾ����
    int flag_sibling,flag_child;
    /*
        �����ж��Ƿ��к��Ӻ��ֵ�
        flag==1 ��
        ���������bool��but cû��bool ������int
    */
    Person *sibling,*child,*father;
    //�����Ǽ��������ϵ�
    Person *parent;
    //parent������ڵ�ĸ��ڵ�
}Person,*Family;

//�ļ��Ĵ洢����������������洢��
//���Զ�ȡҲ���������
//�кϷ��Լ��飬��Ҫ�������
//����û��д��˫��
int Read_Data(Family *family , FILE *file_r)
{
    if(feof(file_r))
    {
        //�ļ�����
        return (-1);
    }
    else
    {
        (*family) = (Person *)calloc(1, sizeof(Person));
        //������
        fscanf(file_r,"%s",(*family) -> name);
        //����������
        fscanf(file_r," %d %d %d",&((*family)-> birthday[0]) , &((*family) -> birthday[1]) , &((*family) -> birthday[2]));
        //[1][2]Ҫ������
        if(!((*family) ->birthday[1] > 0 && (*family) ->birthday[1] <= 12) || !((*family) ->birthday[2] > 0 && (*family) ->birthday[2] <= 31))
        {
            printf("�������ڴ��� \n");
            system("pause");
            exit(0);
        }
        //���Ƿ���
        fscanf(file_r,"%d",&((*family) -> marriage) );
        if((*family) -> marriage )
        {
            fscanf(file_r,"%s",(*family) -> name_of_mate);
        }
        //����ַ
        fscanf(file_r,"%s",(*family) -> address);
        //���Ǽ���ڼ���
        fscanf(file_r,"%d",&((*family) -> generation));
        if((*family) ->generation <= 0)
        {
            printf("���ֳ���С�ڵ���0 \n");
            exit(0);
        }        
        //���Ƿ���
        fscanf(file_r,"%d",&((*family) -> alive));
        if((*family) -> alive == 0)
        {
            fscanf(file_r,"%d %d %d",&((*family) -> death_date[0]) , &((*family) -> death_date[1]) , &((*family) -> death_date[2]));
        }
        if(!((*family) ->death_date[1] > 0 && (*family) ->death_date[1] <= 12) || !((*family) ->death_date[2] > 0 && (*family) -> death_date[2] <= 31))
        {
            printf("�������ڴ��� \n");
            exit(0);
        }
        //flag_self �ܶ��Զ���Ч
        (*family) -> flag_self = 1;
        fscanf(file_r,"%d",&((*family) -> flag_child));
        fscanf(file_r,"%d",&((*family) -> flag_sibling));
        if((*family) -> flag_child)
        {
            Read_Data(&((*family) -> child),file_r);
        }
        if((*family) -> flag_sibling)
        {
            Read_Data(&((*family) -> sibling),file_r);
        }
        return (1);
    }
}

int Make_The_Tree_Complete(Family family)
{
    if(!family)
    {
        return (-2);
    }
    if(family -> flag_child)
    {
        family -> child -> father = family;
        family -> child -> parent = family;
        Make_The_Tree_Complete(family -> child);
    }
    if(family -> flag_sibling)
    {
        family -> sibling -> father = family -> father;
        family -> sibling -> parent = family;
        Make_The_Tree_Complete(family -> sibling);

    }
    return (2);
}

int Save_Data(Family family , FILE *file_w)
//��ڵ�
//�൱��read����
{
    if(!family)
    {
        return (-3);
    }
    if(family -> flag_self )
    {
        //������
        fprintf(file_w,"%s",family -> name);
        //���������
        fprintf(file_w," %d %d %d",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
        fprintf(file_w," ");
        //���Ƿ���
        fprintf(file_w,"%d",family -> marriage );
        fprintf(file_w," ");
        if(family -> marriage )
        {
            fprintf(file_w,"%s",family -> name_of_mate);
            fprintf(file_w," ");
        }
        //���ַ
        fprintf(file_w,"%s",family -> address);
        fprintf(file_w," ");
        //���Ǽ���ڼ���
        fprintf(file_w,"%d",family -> generation);
        fprintf(file_w," ");
        //���Ƿ���
        fprintf(file_w,"%d",family -> alive);
        fprintf(file_w," ");
        if(family -> alive == 0)
        {
            fprintf(file_w," %d %d %d",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            fprintf(file_w," ");
        }
        fprintf(file_w,"%d",family -> flag_child);
        fprintf(file_w," ");
        fprintf(file_w,"%d",family -> flag_sibling);
        fprintf(file_w,"\n");
        //flag_self �ܶ��Զ���Ч
        if(family -> flag_child)
        {
            Save_Data(family -> child,file_w);
        }
        if(family -> sibling)
        {
            Save_Data(family -> sibling,file_w);
        }
    }
    else
    {
        if(family -> flag_sibling)
        {
            Save_Data(family -> sibling,file_w);
        }
    }
    return (3);
}

//��3����дͼ�ν��棬��Ϊcͼ�ν��治��д��qtֻ֧��cpp
void Show_Information(Family family)
//����ħ��
{
    if(!family)
    {
        return ;
    }
    if(family -> flag_self)
    //���濪ʼ�����Ϣ
    {        
        printf("���֣�%s\n",family -> name);
        printf("�������ڣ�%d�� %d�� %d��\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
        if(family -> marriage )
        {
            printf("�ѻ� ��ż��%s\n",family -> name_of_mate);
        }
        else
            printf("δ��\n");
        //���ַ
        printf("��%d��\n",family -> generation);
        printf("��ͥ��ַ%s\n",family -> address);
        if(family -> alive == 0)
        {
            printf("��ȥ����ȥ��ʱ���� %d�� %d�� %d��\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            printf("\n");
        }
        else
        {
            printf("\n");
        }
        if(family -> flag_sibling)
        {
            Show_Information(family -> sibling );
        }
        if(family -> flag_child)
        {
            Show_Information(family -> child );
        }
    }
    else
    {
        if(family -> flag_sibling)
        {
            Show_Information(family ->sibling);           
        }
    }
}//����з���4�����û�з���-4

int Show_Information_By_Generation(Family family , int generation)
//����ħ��
{
    int i = -4;
    if(!family)
    {
        return (-4);
    }
    if(generation < 0)
    {
        printf("���ֲ���\n");
        return(-101);
    }
    if(family -> generation == generation && family -> flag_self)
    //���濪ʼ�����Ϣ
    {        
        printf("���֣�%s\n",family -> name);
        printf("�������ڣ�%d�� %d�� %d��\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
        if(family -> marriage )
        {
            printf("�ѻ� ��ż��%s\n",family -> name_of_mate);
        }
        else
            printf("δ��\n");
        //���ַ
        printf("��ͥ��ַ%s\n",family -> address);
        if(family -> alive == 0)
        {
            printf("��ȥ����ȥ��ʱ���� %d�� %d�� %d��\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            printf("\n");
        }
        else
        {
            printf("\n");
        }
        if(family -> flag_sibling)
        {
            Show_Information_By_Generation(family ->sibling ,generation);
        }//ͬһֻ���ӱ���һ���ȸ��������ϴ�
        i = 4;
    }
    else
    {
        if(!family -> flag_self)
        {
            if(family -> flag_sibling)
            {
                i = Show_Information_By_Generation(family ->sibling ,generation);
            }            
        }
        if(family -> generation <= generation)
        //�������ָ����û��Ҫ��
        {
            if(family ->flag_child)
            {
                i = Show_Information_By_Generation(family ->child,generation);
            }
            if(family -> flag_sibling)
            {
                i = Show_Information_By_Generation(family ->sibling ,generation);
            }
        }
    }
    return (i);
}//����з���4�����û�з���-4

int Information_Inquiry_By_Name(Family family)
{
    printf("���֣�%s\n",family -> name);
    printf("�������ڣ�%d�� %d�� %d��\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
    if(family -> marriage )
    {
        printf("�ѻ� ��ż��%s\n",family -> name_of_mate);
    }
    else
        printf("δ��\n");
    //���ַ
    printf("��%d��\n",family -> generation);
    printf("��ͥ��ַ%s\n",family -> address);
    if(family -> alive == 0)
    {
        printf("��ȥ����ȥ��ʱ���� %d�� %d�� %d��\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
    }
    printf("\n");
}

int Inquiry_By_Name(Family family,char *name)
//ǰ���ħ��
{    
    int i = -5;
    if(!family)
    {
        return (-5);
    }
    if(!name)
    {
        printf("����Ϊ��\n");
        return (-102);
    }
    if(strcmp(family -> name, name ) == 0 && family ->flag_self)
    //���濪ʼ�����Ϣ
    {        
        printf("����:\n");
        Information_Inquiry_By_Name(family -> father);
        printf("�Լ�:\n");
        Information_Inquiry_By_Name(family);
        Family point;
        printf("����\n");
        if(family -> flag_child)
        {
            point = family -> child;
            for (  ; point ;)
            {
                if(point -> flag_self)
                {
                    Information_Inquiry_By_Name(point);
                    if(point -> flag_sibling)
                    {
                        point = point -> sibling;
                    }
                    else
                    {
                        break;
                    }
                    
                }
            }
        }
        i = 5;
    }
    else
    {
        if(family ->flag_child)
        {
            i = Inquiry_By_Name(family -> child ,name);
        }
        if(family -> flag_sibling)
        {
            i = Inquiry_By_Name(family -> sibling,name);
        }
    }
    return (i);
}
//i = 5�ҵ� i= -5û�������

int Inquiry_By_Birthday(Family family,int *birthday)
//��ǰ����������
{
    int i = -6;
    if(!family)
    {
        return (-6);
    }
    if(!birthday)
    {
        printf("��������Ϊ��\n");
        return (-103);
    }
    if(family -> flag_self)
    {
        if(family ->birthday[0] == birthday[0] && family ->birthday[1] == birthday[1] && family ->birthday[1] == birthday[1] )
        {
            printf("���֣�%s\n",family -> name);
            printf("�������ڣ�%d�� %d�� %d��\n",family -> birthday[0] , family -> birthday[1] , family -> birthday[2]);
            if(family -> marriage )
            {
                printf("�ѻ� ��ż��%s\n",family -> name_of_mate);
            }
            else
                printf("δ��\n");
            //���ַ
            printf("��%d��\n",family -> generation);
            printf("��ͥ��ַ%s\n",family -> address);
            if(family -> alive == 0)
            {
                printf("��ȥ����ȥ��ʱ���� %d�� %d�� %d��\n",family -> death_date[0] , family -> death_date[1] , family -> death_date[2]);
            }
            printf("\n");
            i = 6;            
        }
        else
        {
            if(family ->flag_child)
            {
                i = Inquiry_By_Birthday(family -> child ,birthday);
            }
            if(family -> flag_sibling)
            {
                i = Inquiry_By_Birthday(family -> sibling,birthday);
            }
        }
    }
    else
    {
        if(family -> flag_sibling)
            i = Inquiry_By_Birthday(family ->sibling,birthday);
    }
     return(i);
}
//

int Define_Generation(Family family,char *name)
{
    int i = -7;
    if(!family)
    {
        return (-7);
    }
    if(!name)
    {
        printf("����Ϊ��\n");
        return (-104);
    }
    if(strcmp(family -> name , name ) == 0)
    //���濪ʼ�����Ϣ
    {        
        i = family -> generation;
        return (i);
    }
    else
    {
        if(family ->flag_child)
        {
            i = Define_Generation(family -> child ,name);
            if(i != -7 && i != 0)
            {
                return (i);
            }
        }
        if(family -> flag_sibling)
        {
            i = Define_Generation(family -> sibling,name);
            if(i != -7  && i != 0)
            {
                return (i);
            }
        }
    }
}

int Define_Relationship(Family family,char *name1,char *name2)
/*
    ����˵��������ֻ��ȷ�����֣�������岮����̫���ˣ���Ҫ�����Լ�Ҳ�������
*/
{
    if( !name1 || !name2 )
    {
        printf("���ִ���\n");
        return (-105);
    }
    int generation1,generation2;
    //���￪ʼȷ������
    Family point1 = family,point2 = family;
    generation1 = Define_Generation(point1,name1);
    generation2 = Define_Generation(point2,name2);
    //generation == -7��ʾ������û�������
    if(generation1 == - 7 )
    {
        printf("û��%s\n",name1);
        return (-107);
    }
    if(generation2 == - 7 )
    {
        printf("û��%s\n",name2);
        return(-107);
    }
    if (generation1 < generation2)
    {
        //ͨ������� ������ֵС����ʹ�
        printf("%s��%s�ĳ������곤%d��\n",name1,name2,generation2 - generation1);
    }
    else if(generation1 == generation2)
    {
        printf("%s��%s��ͬ��\n",name1,name2);
    }
    else if(generation1 > generation2)
    {
        printf("%s��%s�ĳ������곤%d��\n",name2,name1,generation1 - generation2);
    }
    return (8);
}

Family locate(Family family,char *name)
//ǰ���ħ��
{   
    Family point = 0;
    if( strcmp(family -> name, name ) == 0)
    //���濪ʼ�����Ϣ
    {    
        point = family;
        return(point);    
    }
    else
    {
        if(family -> flag_child)
        {
            point = locate(family -> child ,name);
            if (point)
            {
                return(point);    
            }
        }
        if(family -> flag_sibling)
        {
            point = locate(family -> sibling ,name);
            if (point)
            {
                return(point);    
            }
        }
    }
}

int Add_child(Family family,char *name_parent)
/*
    ��Ҫ��λҪ�Ӻ��ӵĳ�Ա
*/
{
    if(!family)
    {
        return (-8);
    }
    if(!name_parent)
    {
        printf("����Ϊ��\n");
        return (-106);
    }
    Person *add;//Ҫ�ӵĺ��ӵ���
    add = locate(family,name_parent);//locate��ǰ���inquiry��
    Person *adds_child, *point;
    adds_child =(Person *)calloc(1,sizeof(Person));
    //
    if(add -> flag_child)
    {    point = add -> child;
        //�ӵ��ֵ����������
        //��add -> child��������������//8
        for ( ; point -> sibling; point = point -> sibling) ;
        point -> flag_sibling = 1;
        point -> sibling = adds_child;
        adds_child -> parent = point;
        adds_child -> father = add;
    }
    else
    {
        add -> child = adds_child ;
        add -> flag_child = 1;
        adds_child -> parent = add;
        adds_child -> father = add;
    }
    //�����Ѿ��ҵ�,���濪ʼ��д��Ϣ
    //������
    printf("name:\n");
    scanf("%s",adds_child -> name);
    //����������
    printf("birthday:\n");
    scanf("%d %d %d",&(adds_child -> birthday[0]) , & (adds_child -> birthday[1]) ,& (adds_child -> birthday[2]));
    //[1][2]Ҫ������
    if(!(adds_child ->birthday[1] > 0 && adds_child ->birthday[1] <= 12) || !(adds_child ->birthday[2] > 0 && adds_child ->birthday[2] <= 31))
    {
        printf("�������ڴ��� \n");
        exit(0);
    }
    //���Ƿ���
    printf("if marry \n");
    scanf("%d",&(adds_child -> marriage) );
    if(adds_child -> marriage )
    {
        printf("name of mate\n");
        scanf("%s",adds_child -> name_of_mate);
    }
    //����ַ
    printf("address:\n");
    scanf("%s",adds_child -> address);
    //���Ǽ���ڼ���
    printf("generation:\n");
    scanf("%d",&(adds_child -> generation));
    if(adds_child ->generation <= 0)
    {
        printf("���ֳ���С�ڵ���0 \n");
        exit(0);
    }        
    //���Ƿ���
    printf("alive:\n");
    scanf("%d",&(adds_child -> alive));
    if(adds_child -> alive == 0)
    {
        printf("death_date :\n");
        scanf("%d %d %d",&(adds_child -> death_date[0]) , &(adds_child -> death_date[1]) , &(adds_child -> death_date[2]));
        if(!(adds_child ->death_date[1] > 0 && adds_child ->death_date[1] <= 12) || !(adds_child ->death_date[2] > 0 && adds_child -> death_date[2] <= 31))
        {
            printf("�������ڴ��� \n");
            exit(0);
        }
    }
    //flag_self �ܶ��Զ���Ч
    adds_child -> flag_self = 1;
    //Ĭ��û�к���;
    return (1);
}

void menu_change()
{
    printf("***********************\n");
    printf("��������Ҫ�޸����ݵ����\n");
    printf("1:����\n");
    printf("2:��������\n");
    printf("3:�������\n");
    printf("4:��ַ\n");
    printf("5:����\n");
    printf("6:�Ƿ���\n");
    printf("7:�Ƿ�ɾ������ڵ�\n");
    printf("***********************\n");
}

int Change_Infomation(Family family,char* name)
{
    Person *change;
    //��λ����
    change = locate(family , name);
    menu_change();
    int i;
    scanf("%d",&i);
    switch (i)
    {
        case 1: 
        {    
            printf("��ǰ������\n");
            printf("������ĺ������\n");
            scanf("%s",change ->name);
            break;
        }

        case 2:
        {
            printf("��ǰ�������ڣ�%d�� %d�� %d��\n",change -> birthday[0] , change -> birthday[1] , change -> birthday[2]);
            printf("������ĺ��������:\n");
            scanf("%d %d %d",&(change -> birthday[0]),&(change -> birthday[1]),&(change -> birthday [2]));
            while(!(change ->birthday[1] > 0 && change ->birthday[1] <= 12) || !( change ->birthday[2] > 0 && change ->birthday[2] <= 31))
            {
                printf("�����ڴ���,����������\n");
                scanf("%d %d %d",&(change -> birthday[0]),&(change -> birthday[1]),&(change -> birthday [2]));    
            }
            break ;
        }

        case 3:
        {   
            if(change -> marriage )
            {
                printf("�ѻ� ��ż��%s\n",change -> name_of_mate);
            }
            else
                printf("δ��\n");
            printf("���������ڵĻ���״��\n");
            scanf("%d",&(change -> marriage));   
            if(change -> marriage )
            {
                printf("��������ż����\n");
                scanf("%s",change -> name_of_mate);
            }
            break;
        }

        case 4:
        {
            printf("��ǰ��ַ��%d\n",change -> address);
            printf("������ı��ĵ�ַ��\n");
            scanf("%s",change -> address);
            break;
        }
        
        case 5:
        {
            printf("���ڵı��֣�%d\n",change -> generation);
            printf("������ĺ�ı���\n");
            scanf("%d",&(change -> generation));
            break;
        }

        case 6:
        {   
            if(change -> alive )
            {
                printf("���� ��ż��%s\n");
            }
            else
                printf("��ǰȥ�����ڣ�%d�� %d�� %d��\n",&(change -> death_date[0]) , &(change -> death_date[1]) , &(change -> death_date[2]));
            printf("������ĺ���Ƿ���:\n");
            scanf("%d",&(change -> alive));
            if(! change -> alive)
            {
                scanf("%d %d %d",&(change -> death_date[0]),&(change -> death_date[1]),&(change -> death_date [2]));
                while(!(change ->death_date[1] > 0 && change ->death_date[1] <= 12) || !( change ->death_date[2] > 0 && change ->death_date[2] <= 31))
                {
                    printf("�����ڴ���,����������\n");
                    scanf("%d %d %d",&(change -> death_date[0]),&(change -> death_date[1]),&(change -> death_date [2]));    
                }
            }
            break;
        }

        case 7 :
        {
            change -> flag_self = 0;
            break;
        }

        default:
        {
            printf("I��ֵ������������\n");
            scanf("%d",&i);
            break;
        }
    }
}

//��������menu
void menu_main()
{
	//��ʾ�˵���
	printf("************************************\n");
	printf("1. ��ʾ����\n");
	printf("2. ��ʾ��n�������˵���Ϣ\n");
	printf("3. ������ѯ�������Ա��Ϣ(���ˡ����ס�����)\n");
	printf("4. ���ճ������ڲ�ѯ��Ա����\n");
	printf("5. ������������ȷ�����ϵ\n");
	printf("6. ĳ��Ա��Ӻ���\n");
	printf("7. ɾ��ĳ��Ա�����仹�к������һ��ɾ����\n");
	printf("8. �޸�ĳ��Ա��Ϣ\n");
	printf("9. ���ݵ��ļ��洢\n");
	printf("10. �˳�����,���洢\n");
	printf("************************************\n");
}

int   Distroy(Family family)
{
    if(!family)
        return (0);
    else
    {
        Distroy(family ->child);
        Distroy(family -> sibling);
        free(family);
        return (0);
    }
    
}

int main()
{
    Family family_tree = 0;
    FILE *file = fopen("family.txt","r");
    Read_Data(&family_tree,file);
    Make_The_Tree_Complete(family_tree);
    fclose(file);
    //����ر�
    int choice;
    while(1)
    {
        menu_main();
        printf("������ѡ��\n");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 :
                {
                    Show_Information(family_tree);
                    break;
                }

            case 2 :
                {
                    int generation;
                    printf("������Ҫ��ѯ�ı���\n");
                    scanf("%d",&generation);
                    Show_Information_By_Generation(family_tree,generation);
                    break;
                }

            case 3 :
                {
                    char name[20];
                    printf("������Ҫ��ѯ������\n");
                    scanf("%s",name);
                    if( -5 == Inquiry_By_Name(family_tree,name))
                    {
                        printf("���޴���");
                    }
                    break;
                }

            case 4 :
                {
                    int birthday[3];
                    printf("������Ҫ��ѯ������\n");
                    scanf("%d%d%d",&(birthday[0]),&(birthday[1]),&(birthday[2]));
                    if( -6 == Inquiry_By_Birthday(family_tree,birthday))
                    {
                        printf("���޴���");
                    }            
                    break;
                }

            case 5 :
                {            
                    char name1[20],name2[20];
                    printf("������Ҫ��ѯ������\n");
                    scanf("%s",name1);
                    scanf("%s",name2);
                    Define_Relationship(family_tree,name1,name2);
                    break;
                }

            case 6 :
                {
                    char name1[20];
                    printf("������Ҫ��Ӻ��ӵ�����\n");
                    scanf("%s",name1);
                    Add_child(family_tree,name1);
                }            
                    break;

            case 7 :
                {
                    Family del;
                    char name1[20];
                    printf("������Ҫɾ��������\n");
                    scanf("%s",name1);
                    del = locate(family_tree,name1);
                    del -> flag_self = 0;
                    //����ɾ��
                    break;
                }
            case 8 :
                {
                    Family del;
                    char name1[20];
                    printf("������Ҫ�޸ĵ�����\n");
                    scanf("%s",name1);
                    Change_Infomation(family_tree,name1);
                    break;
                }

            case 9 :
                {
                    file = fopen("family_save.txt","w");
                    Save_Data(family_tree,file);
                    fclose(file);
                    break;
                }

            case 10 :
                {
                    file = fopen("family_save.txt","w");
                    Save_Data(family_tree,file);
                    fclose(file);
                    Distroy(family_tree);
                    return (0);
                }
            default:
            {
                printf("�����������������");
                scanf("%d",&choice);
                break;
            }
        }
    }
    system("pause");
    return (0);
}

