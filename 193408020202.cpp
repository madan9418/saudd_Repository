#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std; 
#include<string.h>
#include<algorithm>
#include<stack>
#define INF 9999999
#define MAX 30
int dist[MAX][MAX];///距离
int path[MAX][MAX];///路径
int Stack[MAX];///路径栈
int top;///栈顶
int counts;///记录路径数

typedef struct VexNode//景点信息结构体
{
 int vertex;//景点编号
 char name[20];//景点名称
 char vertax_message[400];//景点介绍
}VerNode;
typedef struct maps//景点图的结构体
{
VerNode  v[MAX];
int vexnum;//点数
int arcnum;//边数
int edgs[MAX][MAX];//邻接矩阵
}AdjList;
int visited[MAX];

void create_vertex(AdjList &GL);//初始化校园景点及景点信息函数
void Init_Creat_maps(AdjList & GL);//初始化校园景点图函数
void Dis_menu();//展示程序菜单
void Dis_map();//展示校园景点图
void add_message(AdjList &GL);//更新或添加或删除校园景点及路径信息函数
void find_message(AdjList GL);//查询景点信息函数
void Floyd(AdjList GL);//弗洛伊德求最短路径
void Floyd_print(int s, int e,AdjList GL);//打印最短路径
void Dfs_allpaths(int s,int e,AdjList GL);//查询两景点之间所有路径函数


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
		      printf("请输入起点的景点（编号形式）：\n");
		      scanf("%d",&start);
		      printf("请输入起点的终点（编号形式）：\n");
		      scanf("%d",&end);
		      Floyd(graph); 
		      printf("从%s到%s的最短路径是：%d米 ",graph.v[start].name,graph.v[end].name,dist[start][end]);
		      printf("%s->",graph.v[start].name);
	       	  Floyd_print(start,end,graph);
		      printf("%s\n",graph.v[end].name);
		    
		   }
		      if(key==3)
		  {
			  printf("请输入起点的景点（编号形式）：\n");
		      scanf("%d",&start);
		      printf("请输入起点的终点（编号形式）：\n");
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
		      printf("使用结束！");
		      break;
		 }
			  if(key>5||key<1)
			  {
			  printf("输入有误！请重新输入！");
			  continue;
			  }
	}
 
		return 0;
 }

 

void create_vertex(AdjList &GL)
{
	//预置初始时景点图的景点信息
	GL.v[1].vertex=1;
    strcpy(GL.v[1].name,"艺术馆");
	strcpy(GL.v[1].vertax_message,"位于体育馆西侧,设计艺术学院(一到四楼）,计算机学院(五楼)在此办公。");
	GL.v[2].vertex=2;
    strcpy(GL.v[2].name,"体育馆");
	strcpy(GL.v[2].vertax_message,"主要有羽毛球馆、篮球馆、游泳馆、健身房、台球馆、乒乓球馆等。");
	GL.v[3].vertex=3;
    strcpy(GL.v[3].name,"机械馆");
	strcpy(GL.v[3].vertax_message,"位于图书馆西侧，机电工程学院，自动化学院，材料科学与工程学院在此办公。");
	GL.v[4].vertex=4;
    strcpy(GL.v[4].name,"图书馆");
	strcpy(GL.v[4].vertax_message,"位于学校展翼大道音乐喷泉后面，是书刊查阅、借阅、资料索引、下载、读书学习的集中地。");
	GL.v[5].vertex=5;
    strcpy(GL.v[5].name,"大学生活动中心");
	strcpy(GL.v[5].vertax_message,"学生处、招生就业处、校团委、校史馆、校学生会联合会、校社团联合会、校大学生艺术团、网络思政中心、爱心联合会在此办公。");
	GL.v[6].vertex=6;
    strcpy(GL.v[6].name,"行政楼");
	strcpy(GL.v[6].vertax_message,"位于学校正门，是学校部分机关部门、直属附属单位办公场所，涉及到学生事务的部门有教务处、计财处等。");
	GL.v[7].vertex=7;
    strcpy(GL.v[7].name,"经管楼");
	strcpy(GL.v[7].vertax_message,"位于行政楼北侧。");
	GL.v[8].vertex=8;
    strcpy(GL.v[8].name,"逸夫馆");
	strcpy(GL.v[8].vertax_message,"位于学校西北角。");
	GL.v[9].vertex=9;
    strcpy(GL.v[9].name,"航空宇航馆");
	strcpy(GL.v[9].vertax_message,"三航办公。");
	GL.v[10].vertex=10;
    strcpy(GL.v[10].name,"蓝天剧场");
	strcpy(GL.v[10].vertax_message,"学校文艺活动举办场所。");
 

}
void Init_Creat_maps(AdjList & GL)
{
	//初始景点图
    int i,j;
	GL.vexnum=10;///10个景点
	GL.arcnum=8;///8条双向路径
	for(i=1; i<=MAX; i++) ///初始化邻接矩阵
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
    printf("       ************欢迎使用沈航导游咨询系统***********\n\n");
    printf("       *****   1.沈航景点信息查询           ******************\n");
    printf("       *****   2.两景点之间最短路查询       ******************\n");
    printf("       *****   3.两景点间所有路径查询       ******************\n");
    printf("       *****   4.景点和路径信息的删除或增加(更新) ******************\n");
	printf("       *****   5.退出系统                   ******************\n");
    printf("       *******************************************************\n");
    return ;
}
void Dis_map()
{
    printf("\n                          *沈航校园景点地图一览*\n\n");
    printf("                                                                   12北区    \n");
    printf("                                 ①艺术馆      ②体育馆            ◎    \n");
    printf("                                    ◎          ◎-----------------|     \n");
    printf("                                    |------------|                 |     \n");
    printf("                                    |            |                 |   \n");
    printf("                                   ③机械馆    ④图书馆  ⑩蓝天剧场|      \n");
    printf("                                   ◎           ◎         ◎      ◎ ⑤大学生活动中心       \n");
    printf("      ⑧逸夫楼◎--------------------|---------- |-----------|-------|          \n");
    printf("                |                               |          ◎-------|    \n");
    printf("                |                               |        11青阳湖   |  \n");
    printf("                |                               ◎⑨航空宇航馆      |            \n");
    printf("                ◎⑦经管楼                       |                  |             \n");
    printf("                |--------------------------------|                  |            \n");
    printf("                |                                |-------------- 13南区        \n");
    printf("                |                                                            \n");
    printf("                ◎⑥行政楼                                                \n\n");
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
	     printf("输入‘1’增加（更新）景点信息，输入‘2’增加（更新）路径信息，输入‘3’删除景点信息，输入‘4’删除路径信息：\n");
	     printf("输入‘0’则退出\n");
	     printf("********************************************************************************************\n");
	     cin>>num;
	 if(num==0)
	  {
	       break;
	  }
	 if(num==1)
	 {
	    printf("请依次输入要增加信息的景点的编号，景点名称，景点介绍：\n");
		printf("注意：如果景点为新增的景点编号需要在原来基础上递增！！！！！\n");
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
	    printf("请输入增加路径的详细信息及其长度（用景点编号表示）：\n");
		cout<<"例如：1 2 "<<endl;
	    cout<<"      200    "<<endl;
		scanf("%d %d",&p,&q);
		cin>>GL.edgs[p][q];//输入长度
	    GL.edgs[q][p]=GL.edgs[p][q];//路径为双向路径
		continue;
	}
	if(num==3)
	{
		printf("请输入要删除信息的景点的编号：\n");
		scanf("%d",&num2);
		strcpy(GL.v[num2].name,"0");//置0代表删除
	    strcpy(GL.v[num2].vertax_message,"0");//置0代表删除
		continue;
	}
	if(num==4)
	{
	   printf("请输入删除的路径（用景点编号表示）：\n");
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
     printf("景点图可查询的景点有：\n");
     for(int i=1;i<=GL.vexnum;i++)
     {
	     printf("%d:%s\n",GL.v[i].vertex,GL.v[i].name);
     }
   
     while(1)
  {
        printf("请输入要查询的景点的编号：\n");
		printf("输入0则退出\n\n");
        cin>>number;
		    if(number==0)
		  {
		          break;
		  }
		   else if(number>GL.vexnum||number<0)
		  {
		         printf("输入有误，请重新输入：\n");
		         continue;
		  }
		   else
		  {
			     printf("%d: %s\n",GL.v[number].vertex,GL.v[number].name);
			     printf("%s\n",GL.v[number].vertax_message);
		  }
   }

}

void Floyd(AdjList GL) //弗洛伊德
{
    int i,j,k;
	for(i=1; i<=GL.vexnum; i++) //初始化距离与路径矩阵
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
                path[i][j]=-1;//-1代表不可达
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
                    dist[i][j]=dist[i][k]+dist[k][j];//更新
                    path[i][j]=k;         //path用于记录最短路径上的结点
                }
            }
        }
    }
    return ;
}
void Floyd_print(int s, int e,AdjList GL)
{
    if(path[s][e]==-1||path[s][e]==e||path[s][e]==s)//递归终止条件
    {
        return;
    }
    else
    {
        Floyd_print(s,path[s][e],GL);//将中间点作为终点继续打印路径
        printf("%s->",GL.v[path[s][e]].name);//打印中间景点名字
        Floyd_print(path[s][e],e,GL);//将中间点作为起点继续打印路径
    }
}

void Dfs_allpaths(int s,int e,AdjList GL)
{
    int dis=0;
    int i,j;
    Stack[top]=s;
    top++;  //起点入栈
    visited[s]=1;//标记入栈
	for(i=1; i<=GL.vexnum; i++)
    {
        if(GL.edgs[s][i]>0 && GL.edgs[s][i]!=INF && !visited[i])
        {
            //表明两点可达且未被访问
            if(i==e)//DFS到了终点，打印路径
            {
                printf("第%d条路:",++counts);
                for(j=0; j<top; j++)
                {
                    printf("%s->",GL.v[Stack[j]].name);
                    if(j<top-1)//统计路径长度
                    {
                        dis=dis+GL.edgs[Stack[j]][Stack[j+1]];
                    }
                }
                dis=dis+GL.edgs[Stack[top-1]][e];
                printf("%s\n",GL.v[e].name);//打印终点
                printf("总长度是：%dm\n\n",dis);
            }
            else//不是终点接着DFS
            {
                Dfs_allpaths(i,e,GL);
                top--;//支路全被访问一遍,顶点出栈
                visited[i]=0;//出栈点标记为已出栈，允许下次访问
            }
        }
    }
}





 

 