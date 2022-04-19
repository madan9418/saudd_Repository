#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std; 
#include<string.h>
#include<algorithm>
#include<stack>
#define INF 9999999
#define MAX 30
int dist[MAX][MAX];///����
int path[MAX][MAX];///·��
int Stack[MAX];///·��ջ
int top;///ջ��
int counts;///��¼·����

typedef struct VexNode//������Ϣ�ṹ��
{
 int vertex;//������
 char name[20];//��������
 char vertax_message[400];//�������
}VerNode;
typedef struct maps//����ͼ�Ľṹ��
{
VerNode  v[MAX];
int vexnum;//����
int arcnum;//����
int edgs[MAX][MAX];//�ڽӾ���
}AdjList;
int visited[MAX];

void create_vertex(AdjList &GL);//��ʼ��У԰���㼰������Ϣ����
void Init_Creat_maps(AdjList & GL);//��ʼ��У԰����ͼ����
void Dis_menu();//չʾ����˵�
void Dis_map();//չʾУ԰����ͼ
void add_message(AdjList &GL);//���»���ӻ�ɾ��У԰���㼰·����Ϣ����
void find_message(AdjList GL);//��ѯ������Ϣ����
void Floyd(AdjList GL);//�������������·��
void Floyd_print(int s, int e,AdjList GL);//��ӡ���·��
void Dfs_allpaths(int s,int e,AdjList GL);//��ѯ������֮������·������


int main()
 {      AdjList graph;
        int key;
		int start,end;
        create_vertex(graph);
        Init_Creat_maps(graph);
	
		while(1)
	{
		      Dis_menu();
		      cin>>key;
		      if(key==1)
		  {
               Dis_map();
		       find_message(graph);
		     
		  }
              if(key==2)
		  {
		      printf("���������ľ��㣨�����ʽ����\n");
		      scanf("%d",&start);
		      printf("�����������յ㣨�����ʽ����\n");
		      scanf("%d",&end);
		      Floyd(graph); 
		      printf("��%s��%s�����·���ǣ�%d�� ",graph.v[start].name,graph.v[end].name,dist[start][end]);
		      printf("%s->",graph.v[start].name);
	       	  Floyd_print(start,end,graph);
		      printf("%s\n",graph.v[end].name);
		    
		   }
		      if(key==3)
		  {
			  printf("���������ľ��㣨�����ʽ����\n");
		      scanf("%d",&start);
		      printf("�����������յ㣨�����ʽ����\n");
		      scanf("%d",&end);
			  counts=0;
			  top=0;
		      Dfs_allpaths(start,end,graph);
		  
		  }
		      if(key==4)
		  {
		      add_message(graph);
		   
		  }
		      if(key==5)
		  {
		      printf("ʹ�ý�����");
		      break;
		 }
			  if(key>5||key<1)
			  {
			  printf("�����������������룡");
			  continue;
			  }
	}
 
		return 0;
 }

 

void create_vertex(AdjList &GL)
{
	//Ԥ�ó�ʼʱ����ͼ�ľ�����Ϣ
	GL.v[1].vertex=1;
    strcpy(GL.v[1].name,"������");
	strcpy(GL.v[1].vertax_message,"λ������������,�������ѧԺ(һ����¥��,�����ѧԺ(��¥)�ڴ˰칫��");
	GL.v[2].vertex=2;
    strcpy(GL.v[2].name,"������");
	strcpy(GL.v[2].vertax_message,"��Ҫ����ë��ݡ�����ݡ���Ӿ�ݡ�������̨��ݡ�ƹ����ݵȡ�");
	GL.v[3].vertex=3;
    strcpy(GL.v[3].name,"��е��");
	strcpy(GL.v[3].vertax_message,"λ��ͼ������࣬���繤��ѧԺ���Զ���ѧԺ�����Ͽ�ѧ�빤��ѧԺ�ڴ˰칫��");
	GL.v[4].vertex=4;
    strcpy(GL.v[4].name,"ͼ���");
	strcpy(GL.v[4].vertax_message,"λ��ѧУչ����������Ȫ���棬���鿯���ġ����ġ��������������ء�����ѧϰ�ļ��еء�");
	GL.v[5].vertex=5;
    strcpy(GL.v[5].name,"��ѧ�������");
	strcpy(GL.v[5].vertax_message,"ѧ������������ҵ����У��ί��Уʷ�ݡ�Уѧ�������ϻᡢУ�������ϻᡢУ��ѧ�������š�����˼�����ġ��������ϻ��ڴ˰칫��");
	GL.v[6].vertex=6;
    strcpy(GL.v[6].name,"����¥");
	strcpy(GL.v[6].vertax_message,"λ��ѧУ���ţ���ѧУ���ֻ��ز��š�ֱ��������λ�칫�������漰��ѧ������Ĳ����н��񴦡��Ʋƴ��ȡ�");
	GL.v[7].vertex=7;
    strcpy(GL.v[7].name,"����¥");
	strcpy(GL.v[7].vertax_message,"λ������¥���ࡣ");
	GL.v[8].vertex=8;
    strcpy(GL.v[8].name,"�ݷ��");
	strcpy(GL.v[8].vertax_message,"λ��ѧУ�����ǡ�");
	GL.v[9].vertex=9;
    strcpy(GL.v[9].name,"�������");
	strcpy(GL.v[9].vertax_message,"�����칫��");
	GL.v[10].vertex=10;
    strcpy(GL.v[10].name,"����糡");
	strcpy(GL.v[10].vertax_message,"ѧУ���ջ�ٰ쳡����");
 

}
void Init_Creat_maps(AdjList & GL)
{
	//��ʼ����ͼ
    int i,j;
	GL.vexnum=10;///10������
	GL.arcnum=8;///8��˫��·��
	for(i=1; i<=MAX; i++) ///��ʼ���ڽӾ���
    {
		for(j=1; j<=MAX; j++)
        {
            GL.edgs[i][j]=INF;
        }
    }
 
    GL.edgs[1][3]=GL.edgs[3][1]=210;
    GL.edgs[1][4]=GL.edgs[4][1]=300;
    GL.edgs[2][7]=GL.edgs[7][2]=400;
    GL.edgs[2][4]=GL.edgs[4][2]=420;
    GL.edgs[3][4]=GL.edgs[4][3]=80;
    GL.edgs[4][5]=GL.edgs[5][4]=780;
	GL.edgs[1][7]=GL.edgs[7][1]=30;
	GL.edgs[1][2]=GL.edgs[2][1]=20;
  
}
void Dis_menu()
{
    printf("\n");
    printf("       ************��ӭʹ���򺽵�����ѯϵͳ***********\n\n");
    printf("       *****   1.�򺽾�����Ϣ��ѯ           ******************\n");
    printf("       *****   2.������֮�����·��ѯ       ******************\n");
    printf("       *****   3.�����������·����ѯ       ******************\n");
    printf("       *****   4.�����·����Ϣ��ɾ��������(����) ******************\n");
	printf("       *****   5.�˳�ϵͳ                   ******************\n");
    printf("       *******************************************************\n");
    return ;
}
void Dis_map()
{
    printf("\n                          *��У԰�����ͼһ��*\n\n");
    printf("                                                                   12����    \n");
    printf("                                 ��������      ��������            ��    \n");
    printf("                                    ��          ��-----------------|     \n");
    printf("                                    |------------|                 |     \n");
    printf("                                    |            |                 |   \n");
    printf("                                   �ۻ�е��    ��ͼ���  ������糡|      \n");
    printf("                                   ��           ��         ��      �� �ݴ�ѧ�������       \n");
    printf("      ���ݷ�¥��--------------------|---------- |-----------|-------|          \n");
    printf("                |                               |          ��-------|    \n");
    printf("                |                               |        11������   |  \n");
    printf("                |                               ��ẽ�����      |            \n");
    printf("                ��߾���¥                       |                  |             \n");
    printf("                |--------------------------------|                  |            \n");
    printf("                |                                |-------------- 13����        \n");
    printf("                |                                                            \n");
    printf("                �������¥                                                \n\n");
}

void add_message(AdjList &GL)
{
	int num,p,q,num1,num2,p1,q1;
	VerNode *t;
	t=GL.v;
	while(1)
	   {
	     num=-1;
	     printf("********************************************************************************************\n");
	     printf("���롮1�����ӣ����£�������Ϣ�����롮2�����ӣ����£�·����Ϣ�����롮3��ɾ��������Ϣ�����롮4��ɾ��·����Ϣ��\n");
	     printf("���롮0�����˳�\n");
	     printf("********************************************************************************************\n");
	     cin>>num;
	 if(num==0)
	  {
	       break;
	  }
	 if(num==1)
	 {
	    printf("����������Ҫ������Ϣ�ľ���ı�ţ��������ƣ�������ܣ�\n");
		printf("ע�⣺�������Ϊ�����ľ�������Ҫ��ԭ�������ϵ�������������\n");
		scanf("%d",&num1);
		if(num1>GL.vexnum)
		{
			GL.vexnum+=1;
		}
		GL.v[num1].vertex=num1;
		cin>>GL.v[num1].name;
		cin>>GL.v[num1].vertax_message;
		continue;
	}
	if(num==2)
	{
		GL.arcnum+=1;
	    printf("����������·������ϸ��Ϣ���䳤�ȣ��þ����ű�ʾ����\n");
		cout<<"���磺1 2 "<<endl;
	    cout<<"      200    "<<endl;
		scanf("%d %d",&p,&q);
		cin>>GL.edgs[p][q];//���볤��
	    GL.edgs[q][p]=GL.edgs[p][q];//·��Ϊ˫��·��
		continue;
	}
	if(num==3)
	{
		printf("������Ҫɾ����Ϣ�ľ���ı�ţ�\n");
		scanf("%d",&num2);
		strcpy(GL.v[num2].name,"0");//��0����ɾ��
	    strcpy(GL.v[num2].vertax_message,"0");//��0����ɾ��
		continue;
	}
	if(num==4)
	{
	   printf("������ɾ����·�����þ����ű�ʾ����\n");
	   scanf("%d %d",&p1,&q1);
	   GL.edgs[p1][q1]=INF;
	   GL.edgs[q1][p1]=INF;
	   continue;
	}
	}

}



void find_message(AdjList GL)
{
	 int number;
     printf("����ͼ�ɲ�ѯ�ľ����У�\n");
     for(int i=1;i<=GL.vexnum;i++)
     {
	     printf("%d:%s\n",GL.v[i].vertex,GL.v[i].name);
     }
   
     while(1)
  {
        printf("������Ҫ��ѯ�ľ���ı�ţ�\n");
		printf("����0���˳�\n\n");
        cin>>number;
		    if(number==0)
		  {
		          break;
		  }
		   else if(number>GL.vexnum||number<0)
		  {
		         printf("�����������������룺\n");
		         continue;
		  }
		   else
		  {
			     printf("%d: %s\n",GL.v[number].vertex,GL.v[number].name);
			     printf("%s\n",GL.v[number].vertax_message);
		  }
   }

}

void Floyd(AdjList GL) //��������
{
    int i,j,k;
	for(i=1; i<=GL.vexnum; i++) //��ʼ��������·������
    {
		for(j=1; j<=GL.vexnum; j++)
        {
            dist[i][j]=GL.edgs[i][j];
            if(i!=j&&dist[i][j]<INF)
            {
                path[i][j]=i;
            }
            else
            {
                path[i][j]=-1;//-1�����ɴ�
            }
        }
    }
    //printf("%d\n",GL.);
	for(k=1; k<=GL.vexnum; k++)
    {
		for(i=1; i<=GL.vexnum; i++)
        {
			for(j=1; j<=GL.vexnum; j++)
            {
                if(dist[i][j]>(dist[i][k]+dist[k][j]))
                {
                    dist[i][j]=dist[i][k]+dist[k][j];//����
                    path[i][j]=k;         //path���ڼ�¼���·���ϵĽ��
                }
            }
        }
    }
    return ;
}
void Floyd_print(int s, int e,AdjList GL)
{
    if(path[s][e]==-1||path[s][e]==e||path[s][e]==s)//�ݹ���ֹ����
    {
        return;
    }
    else
    {
        Floyd_print(s,path[s][e],GL);//���м����Ϊ�յ������ӡ·��
        printf("%s->",GL.v[path[s][e]].name);//��ӡ�м侰������
        Floyd_print(path[s][e],e,GL);//���м����Ϊ��������ӡ·��
    }
}

void Dfs_allpaths(int s,int e,AdjList GL)
{
    int dis=0;
    int i,j;
    Stack[top]=s;
    top++;  //�����ջ
    visited[s]=1;//�����ջ
	for(i=1; i<=GL.vexnum; i++)
    {
        if(GL.edgs[s][i]>0 && GL.edgs[s][i]!=INF && !visited[i])
        {
            //��������ɴ���δ������
            if(i==e)//DFS�����յ㣬��ӡ·��
            {
                printf("��%d��·:",++counts);
                for(j=0; j<top; j++)
                {
                    printf("%s->",GL.v[Stack[j]].name);
                    if(j<top-1)//ͳ��·������
                    {
                        dis=dis+GL.edgs[Stack[j]][Stack[j+1]];
                    }
                }
                dis=dis+GL.edgs[Stack[top-1]][e];
                printf("%s\n",GL.v[e].name);//��ӡ�յ�
                printf("�ܳ����ǣ�%dm\n\n",dis);
            }
            else//�����յ����DFS
            {
                Dfs_allpaths(i,e,GL);
                top--;//֧·ȫ������һ��,�����ջ
                visited[i]=0;//��ջ����Ϊ�ѳ�ջ�������´η���
            }
        }
    }
}





 

 