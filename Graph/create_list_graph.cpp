// 邻接表的创建
#include <iostream>
#include <queue>
using std::queue;
using std::cout;
using std::cin;

#define OK 1
#define ERROR 0
#define MAXVEX 100  // 顶点的最大数量

typedef int Status;
typedef char VertexType;  // 顶点的数据类型
typedef int EdgeType;  // 边权值的类型

// 边表结点
typedef struct EdgeNode {
    int adjvex;  //邻接点域，存储该顶点对应的下标
    EdgeType info;  // 用于存储权值，对于非网图可以不需要
    struct EdgeNode *next;  // 链域，指向下一个邻接点  
}EdgeNode;

// 顶点表结点
typedef struct VertexNode {
    VertexType data;  // 顶点数据域，存储顶点信息
    EdgeNode *first;  // 边表头结点
}VertexNode, AdjList[MAXVEX];  // AdjList x等价于 VertexNode x[MAXVEX]

// 邻接表
typedef struct {
    AdjList adjList;
    int numNode;  // 图的顶点数
    int numEdge;  // 图的边数
}GraphAdjList;

bool visited[MAXVEX];  // 遍历访问标志的数组

// 构建图的邻接表结构
Status CreatLGraph(GraphAdjList &G);
// 邻接表的深度优先递归算法
void DFS(GraphAdjList G, int i);
// 邻接表的深度遍历操作
Status DFSTravese(GraphAdjList &G);
// 邻接表的广度优先遍历操作
Status BFSTravese(GraphAdjList G);

int main() {
    GraphAdjList G;
    CreatLGraph(G);
    cout << "深度优先遍历：" << std::endl;
    DFSTravese(G);
    cout << std::endl << "广度优先遍历：" << std::endl;
    BFSTravese(G);

    return 0;
}

// 构建图的邻接表结构
Status CreatLGraph(GraphAdjList &G) {
    // 存储边的顶点序号
    int i_index{0};
    int j_index{0};
    // 边表结点的指针
    EdgeNode *e{nullptr};

    cout << "请输入顶点数和边数：" << std::endl;
    cin >> G.numNode >> G.numEdge;

    // 读入顶点信息建立顶点表
    cout << "请依次输入各顶点：" << std::endl;
    for( int i = 0; i < G.numNode; i++ ) {
        // 输入顶点信息
        cin >> G.adjList[i].data;
        // 将边表置为空表
        G.adjList[i].first = nullptr;
    }

    // 建立边表
    for( int j = 0; j < G.numEdge; j++ ) {
        cout << "请输入边(Vi,Vj)上的顶点序号：" << std::endl;
        cin >> i_index >> j_index;

        // 申请结点，生成边表结点
        e = new EdgeNode;
        // 邻接序号为j
        e->adjvex = j_index;
        // 然后让i序号顶点指向 j结点
        // e的指针指向当前顶点指向的结点，可以保证始终指向边表的最后一个结点，头插法
        e->next = G.adjList[i_index].first;;
        // 将顶点的指针指向e
        G.adjList[i_index].first = e;

        // 申请结点，生成边表结点
        e = new EdgeNode;
        // 邻接序号为i
        e->adjvex = i_index;
        // e的指针指向当前顶点指向的结点
        e->next = G.adjList[j_index].first;;
        // 将顶点的指针指向e
        G.adjList[j_index].first = e;
    }

    return OK;
}

// 邻接表的深度优先递归算法
void DFS(GraphAdjList G, int i) {
    EdgeNode *p;  // 边表结点
    // 该结点已被访问，标志改变
    visited[i] = true;
    cout << G.adjList[i].data << " ";  // 输出顶点有效值

    p = G.adjList[i].first;  // 将p指向与该顶点相连的第一个点
    while( p ) {  // 该点存在
        if( !visited[p->adjvex] ) {  // 而且没被访问过
            DFS(G,p->adjvex);
        }
        p = p->next;
    }
}


// 邻接表的深度遍历操作
Status DFSTravese(GraphAdjList &G) {
    // 初始化所有的顶点都是未访问状态
    for( int i = 0; i < G.numNode; i++ ) {
        visited[i] = false;
    }

    // 遍历
    for( int j = 0; j < G.numNode; j++ ) {
        if( !visited[j] ) {  // 对未访问的顶点调用DFS
            DFS(G,j);
        }
    }

    return OK;
}

// 邻接表的广度优先遍历操作
Status BFSTravese(GraphAdjList G) {
    EdgeNode * p;
    queue<VertexType> Q;  // 辅助队列

    // 初始化所有的顶点都是未访问状态
    for( int i = 0; i < G.numNode; i++ ) {
        visited[i] = false;
    }

    // 遍历
    for( int j = 0; j < G.numNode; j++ ) {
        if( !visited[j] ) {  //该结点未被访问

            visited[j] = true;
            cout << G.adjList[j].data << " ";  // 打印结点
            Q.push(G.adjList[j].data);  // 入队


            while ( Q.empty() ) {  // 队列不为空
                Q.pop();  // 首元素出队
                p = G.adjList[j].first;  // 找到当前顶点边表顶点的链表头指针

                while( p ) {  //与顶点相连的存在

                    if( !visited[p->adjvex] ) {  // 此顶点未被访问
                        visited[p->adjvex] = true;
                        cout << G.adjList[p->adjvex].data << " "; // 打印顶点
                        Q.push(G.adjList[p->adjvex].data);  // 入队
                    }

                    p = p->next;  // 指向下一个邻接点
                }
            }
            
        }
    }

    return OK;
}