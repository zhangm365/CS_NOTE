


//如何建立一个图


#include <bits/stdc++.h>


//--------------用邻接矩阵表示图的存储----------------------

const int MaxSize = 20;

typedef int Vertex;    //顶点下标

typedef int WeightType;

typedef struct MNode * PtrToMNode;

struct MNode
{
    int Nv;    //顶点数
    int Ne;    //边数
    WeightType AdjMatrix[MaxSize][MaxSize];   //邻接矩阵

};

typedef PtrToMNode MGraph;


/* 边的定义 */
typedef struct ENode * PtrToENode;

struct ENode
{
    Vertex V1, V2;  //边<V1, V2>
    WeightType Weight;  //权重
};

typedef PtrToENode Edge;


//创建没有边的空图：有VertexNum个顶点, 但是没边
MGraph CreateGraph(MGraph G, int VertexNum)
{
    
    Vertex V, M;
    G = (MGraph)malloc(sizeof(struct MNode));

    for(V = 0; V < VertexNum; V++)    
        for (M = 0; M < VertexNum; M++)        
            G->AdjMatrix[V][M] = 0;
        
        
    G->Ne = VertexNum;
    G->Nv = 0;  

    return G;

}


//向图中插入一条边
void InsertEdge(MGraph G, Edge E)
{
    /* 插入边<V1, V2> */
    G->AdjMatrix[E->V1][E->V2] = E->Weight;

    /* 若是无向边, 还需插入边<V2, V1> */

    G->AdjMatrix[E->V2][E->V1] = E->Weight;

}


//完整的建立一个图MGraph

MGraph BuildGraph()
{

    MGraph G;
    int VertexNum;
    //输入顶点数和边数
    scanf("%d", &VertexNum);     
    G = CreateGraph(G, VertexNum);
    scanf("%d", &(G->Ne));
    if(G->Ne != 0)
    {
        Edge E;
        E = (Edge)malloc(sizeof(struct ENode));
        for(int i = 0; i < G->Ne; ++i)
        {//输入边的结点和权重
            scanf("%d %d %d", &(E->V1), &(E->V2), &(E->Weight));
            InsertEdge(G, E);
        }

    }

    return G;

}


//------------------邻接表存储图------------------------------

typedef struct AdjVNode * PtrToAdjVNode;

struct AdjVNode    //邻接结点
{
    Vertex V;   //邻接点下标
    WeightType Weight;  //权重
    PtrToAdjVNode next; //指针域

};

typedef struct VNode    //顶点表头结点表示
{
    PtrToAdjVNode FirstEdge;    //指向第一个结点的指针

}AdjList[MaxSize];  //AdjList是邻接表类型

typedef struct GNode* PtrToGNode;

//图结点的定义
struct GNode
{
    int Nv;     //顶点数
    int Ne;     //边数
    AdjList G;     //邻接表, G为指针数组

};

typedef PtrToGNode LGraph;


LGraph CreateLGraph(LGraph LG, int VertexNum)
{//创建边为VertexNum的空的邻接表

    LG = (LGraph)malloc(sizeof(struct GNode));
    LG->Nv = VertexNum;  
    LG->Ne = 0; 
    for(int i = 0 ; i < LG->Nv; ++i)
    {
        LG->G[i].FirstEdge = NULL; 
    } 

    return LG;

}

void InsertEdge(LGraph LG, Edge E)
{//在邻接表中插入一条边

    PtrToAdjVNode NewNode;
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->V = E->V2;
    NewNode->Weight = E->Weight;
    //将V2插入到V1的表头 【头插法插入一个结点】
    NewNode->next = LG->G[E->V1].FirstEdge;
    LG->G[E->V1].FirstEdge = NewNode;

    //如果为无向图
    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->V = E->V1;
    NewNode->Weight = E->Weight;
    //头插法插入一个结点
    NewNode->next = LG->G[E->V2].FirstEdge;
    LG->G[E->V2].FirstEdge = NewNode;

}


void BuildLGraph(LGraph LG)
{



}


