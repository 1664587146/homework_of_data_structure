/*
    23����4������С�ֵ䣨ѡ���������ң�
    [��������]
    ���ü����ṹ������һ��΢�͵����ֵ䡣
    [����Ҫ��]
    ʵ�����ʵļ��룬���ʵĲ��ҡ�ɾ�����޸ĵȲ�����
*/

//�����ṹ�������ֵ���
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 200

typedef struct Words
{
    char Meaning[MAX];//��˼
    char word[MAX];//��Ӧ�ĵ���

}Words;
//words ֻ�ǽӿ�������Լ���������

typedef struct Key_Node
{
    char KeyValue;//����ڵ�ļ�
    int flag;//�鿴������word�Ƿ񼤻Ϊ����ɾ��׼��
    Words word;
    Key_Node *child,*sibling;
}Key_Node,*Key_Tree;

Key_Tree Insert_And_Seach(Key_Tree *tree,Words word);
void Show_Info(Key_Tree tree);
int Delete_Word(Key_Tree *tree,Words word);
int change(Key_Tree *tree,Words word);
void menu();  

int main()
{
    int state = 1;
    int choice;
    Key_Tree *tree = 0;
    tree =(Key_Tree* ) calloc(1,sizeof(Key_Tree));
    while (state)
    {
        menu();
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
            {
                Words word;
                Key_Tree help;
                printf("�����뵥��\n");
                scanf("%s",word.word);
                help = Insert_And_Seach(tree,word);
                if(help == 0)
                {
                    printf("�Ѽ���\n");
                }
                else
                {
                    Show_Info(help);
                }
                break;
            }
            
            case 2:
            {   
                Words word;
                printf("�����뵥��\n");
                scanf("%s",word.word);
                change(tree,word);
                break;
            }

            case 3 :
            {
                Words word;
                printf("�����뵥��\n");
                scanf("%s",word.word);
                Delete_Word(tree,word);                
                break;
            }

            case 4:
            {
                state = 0;
                break;
            }

            default:
            {   
                printf("�����������������\n");
                scanf("%d",&choice);
                break;
            }
        }
    }
    return 0;
}

void menu()  
{  
	printf("���˵�\n");  
	printf("1:���ҵ���\n");  
	printf("2:�޸ĵ���\n");  
	printf("3:ɾ������\n");
    printf("4:��������\n");
}  


Key_Tree Insert_And_Seach(Key_Tree *tree,Words word)
//���ң��������
//��������
//���Һ�û�д�ӡ��Ϣ����ӡ��Ϣ������
{
    if(*tree == 0 )
    //�ǿÿ���
    {
        int key_position = 0;
        //key��λ�� nuaaΪ�� keyΪn�� key_position = 0��
        Key_Tree help_point1,help_point2;//����ָ��
        *tree = (Key_Tree)calloc(1,sizeof(Key_Node));
        if(*tree)
        {
            (*tree) -> KeyValue = word.word[0];//�����ֵ
            help_point1 = help_point2 = *tree;
            if(key_position + 1== strlen(word.word))
            //���word�Ĺؼ��ֶ�����
            {
                printf("ԭ���ʱ���û���������\n");
                help_point2 -> flag = 1;//����tree��words
                //��word��ֵ��words��
                strcpy( help_point2 ->word.word ,word.word);
                printf("��������˼\n");
                scanf("%s",help_point2 ->word.Meaning);
                return(0);
            }
            else
            {
                help_point1 = *tree;
                while (key_position < strlen(word.word))
                //���������ʵ�key����
                {
                    help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                    if(help_point2)
                    {
                        help_point1 -> child = help_point2;
                        key_position ++;
                        help_point2 -> KeyValue = word.word[key_position];
                        if(key_position + 1== strlen(word.word))
                        //���word�Ĺؼ��ֶ�����
                        {
                            printf("ԭ���ʱ���û���������\n");
                            help_point2 -> flag = 1;//����tree��words
                            //��word��ֵ��words��
                            strcpy( help_point2 ->word.word ,word.word);
                            printf("��������˼\n");
                            scanf("%s",help_point2 ->word.Meaning);
                            return ( 0 );
                        }
                        else
                        {
                            help_point1 = help_point1 -> child;//��������
                        }
                        
                    }
                }
            }
        }
    }
    else
    //������ǿ���
    { 
        int key_position = 0;
        //key��λ�� nuaaΪ�� keyΪn�� key_position = 0��
        Key_Tree help_point1,help_point2;//����ָ��
        help_point1 = *tree;//help_point1 ->��ֵ
        while (key_position < strlen(word.word))
        //��ʼ���һ��߼���
        {
            while ( help_point1 -> KeyValue != word.word[key_position] && help_point1 ->sibling != 0 )
            {
                help_point1 = help_point1 ->sibling;//ͬ���ֵܲ�ͬkeyvalue�Ĳ���
                if (help_point1 -> KeyValue == word.word[key_position])
                {
                    break;
                }
            }
            //���ֱ���ҵ�
            if(key_position + 1 == strlen(word.word) && help_point1 -> KeyValue == word.word[key_position])
            {
                
                if(help_point1 ->flag == 0)//ɾ���Ժ��ټ���
                {
                    printf("ԭ���ʱ���û���������\n");
                    help_point1 -> flag = 1;//����tree��words
                    //��word��ֵ��words��
                    strcpy( help_point1 ->word.word ,word.word);
                    printf("��������˼\n");
                    scanf("%s",help_point1 ->word.Meaning);
                    return (0);
                }
                else
                {
                    return(help_point1);
                }
            }
            if (help_point1 -> KeyValue == word.word[key_position])
            //����е�����������
            {
                if(help_point1 -> child )
                //����к���
                {
                    key_position ++;
                    help_point1 = help_point1 -> child;
                    //�ҵ�
                    if(key_position + 1 == strlen(word.word))
                    {
                        
                        if(help_point1 ->flag == 0)//ɾ���Ժ��ټ���
                        {
                            printf("ԭ���ʱ���û���������\n");
                            help_point1 -> flag = 1;//����tree��words
                            //��word��ֵ��words��
                            strcpy( help_point1 ->word.word ,word.word);
                            printf("��������˼\n");
                            scanf("%s",help_point1 ->word.Meaning);
                            return (0);
                        }
                        else
                        {
                            return(help_point1);
                        }
                    }
                }
                else
                //û�п�ʼ��ӣ���ǰ������
                {
                    while (key_position  < strlen(word.word))
                    //����������ʣ��key����
                    {
                        help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                        if(help_point2)
                        {
                            help_point1 -> child = help_point2;
                            help_point2 -> KeyValue = word.word[key_position];
                            key_position ++;
                            if(key_position + 1 == strlen(word.word))
                            //���word�Ĺؼ��ֶ�����
                            {
                                printf("ԭ���ʱ���û���������\n");
                                help_point2 -> flag = 1;//����tree��words
                                //��word��ֵ��words��
                                strcpy( help_point2 ->word.word ,word.word);
                                printf("��������˼\n");
                                scanf("%s",help_point2 ->word.Meaning);
                                return (0);
                            }
                            else
                            {
                                help_point1 = help_point1 -> child;//��������
                            }
                        }
                    }
                    return(0);
                }
            }

            else
            //û���� ��ʼ�������
            //ͬʱһ��Ҳû�к���
            {
                help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                if(help_point2)
                {
                    help_point1 -> sibling = help_point2;
                    help_point2 -> KeyValue = word.word[key_position];
                    key_position ++;
                    if(key_position == strlen(word.word))
                    //���word�Ĺؼ��ֶ�����
                    {
                        printf("ԭ���ʱ���û���������\n");
                        help_point2 -> flag = 1;//����tree��words
                        //��word��ֵ��words��
                        strcpy( help_point2 ->word.word ,word.word);
                        printf("��������˼\n");
                        scanf("%s",help_point2 ->word.Meaning);
                        return (0);
                    }
                    help_point1 = help_point1 -> sibling;
                }
                while (key_position < strlen(word.word))
                //����������ʣ��key����
                {
                    help_point2 = (Key_Tree)calloc(1,sizeof(Key_Node));
                    if(help_point2)
                    {
                        help_point1 -> child = help_point2;
                        help_point2 -> KeyValue = word.word[key_position];
                        key_position ++;
                        if(key_position  == strlen(word.word))
                        //���word�Ĺؼ��ֶ�����
                        {
                            printf("ԭ���ʱ���û���������\n");
                            help_point2 -> flag = 1;//����tree��words
                            //��word��ֵ��words��
                            strcpy( help_point2 ->word.word ,word.word);
                            printf("��������˼\n");
                            scanf("%s",help_point2 ->word.Meaning);
                            return (0);
                        }
                        else
                        {
                            help_point1 = help_point1 -> child;//��������
                        }
                    }
                }
            }
        }
        //���ʱ���ҵ����ڣ��������ڽڵ�
    }
}

void Show_Info(Key_Tree tree)
//��Ϊ�Ǻ��������ʹ������û��tree��������
{        
    if(tree -> flag )
    {            
        printf("��ǰ��Ϣ����\n");
        printf("%s����˼��%s\n",tree -> word.word,tree ->word .Meaning);
    }
    else
    {
        printf("��ǰ�ڵ�����Ϣ\n");        
    }
    
}

int Delete_Word(Key_Tree *tree,Words word)
//����Ҫ��֤�У��û�ȷ������Ϊû���Զ�������ɾ����ûʲô��˼,�������ῼ��
//��Ҫ�㷨��ɾ��
{
    Key_Tree help;
    if(help = Insert_And_Seach(tree,word))
        help -> flag = 0;
    else
    {
        help = Insert_And_Seach(tree,word);
        help -> flag = 0;
    }
    return (1);
}

int change(Key_Tree *tree,Words word)
//����Ҫ��֤�У��û�ȷ������Ϊû���Զ��������޸ģ�ûʲô��˼
//��Ҫ�㷨ֱ���޸�
{
    Key_Tree help;
    help = Insert_And_Seach(tree,word);
    Show_Info(help);
    printf("�Ƿ��޸�\n1����\n2:����\n");
    int choice;
    scanf("%d" , &choice);
    if (choice == 1)
    {
        printf("��������˼\n");
        scanf("%s",help ->word.Meaning);
        return (3);
    }
    if (choice == 2)
    {
        return (3);
    }
}

