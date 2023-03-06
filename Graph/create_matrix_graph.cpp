// 邻接矩阵的创建
#include <iostream>
#include <queue>
using std::queue;
using std::cout;
using std::cin;

#define OK 1
#define ERROR 0
#define MAXVEX 100  // 顶点的最大数量
#define GRAPH_INFINITY 65535  // 表示权值为 ∞ 

typedef int Status;
typedef char VertexType;  // 顶点的数据类型
typedef int EdgeType;  // 边权值的类型

typedef struct {
    VertexType vexs[MAXVEX];  // 顶点表
    EdgeType arc[MAXVEX][MAXVEX];  // 邻接矩阵
    int numNodes;  // 图的顶点数
    int numEdges;  // 图的边数
}MGraph;

bool visited[MAXVEX];  // 遍历访问标志的数组

// 建立无向图的邻接矩阵表示
Status CreateMGraph(MGraph &G);
// 邻接矩阵的深度优先递归算法
void DFS(MGraph G, int i);
// 邻接矩阵深度遍历操作
Status DFSTravese(MGraph G);
// 邻接矩阵的广度遍历操作
Status BFSTravese(MGraph G);
// 最小生成树算法---Prim算法
Status MiniSpanTreePrim(MGraph G);

int main() {
    MGraph G;
    CreateMGraph(G);
    cout << "深度优先遍历：" << std::endl;
    DFSTravese(G);
    cout << std::endl << "广度优先遍历：" << std::endl;
    BFSTravese(G);
    cout << std::endl << "最小权值依次为：" << std::endl;
    MiniSpanTreePrim(G);

    return 0;
}


// 建立无向图的邻接矩阵表示
Status CreateMGraph(MGraph &G) {
    EdgeType w_elem{0};  // 存储权值
    // 存储边的两个顶点的下标
    int i_index{0};
    int j_index{0};

    cout << "请输入顶点数和边数：" << std::endl;
    cin >> G.numNodes >> G.numEdges;

    // 读入顶点信息，建立顶点表
    cout << "请按顺序输入顶点的信息：" << std::endl;
    for( int index = 0; index < G.numNodes; index++ ) {
        cin >> G.vexs[index];
    }

    // 初始化邻接矩阵
    for( int i = 0; i < G.numNodes; i++ ) {
        for( int j = 0; j < G.numNodes; j++ ) {
            G.arc[i][j] = GRAPH_INFINITY;
        }
    }

    // 读入图的numEdges条边，建立邻接矩阵
    for( int k = 0; k < G.numEdges; k++ ) {
        cout << "请输入边(Vi,Vj)上的下标i、下标j和权值w：" << std::endl;
        cin >> i_index >> j_index >> w_elem;

        G.arc[i_index][j_index] = w_elem;
        G.arc[j_index][i_index] = G.arc[i_index][j_index];  // 因为是无向图，矩阵对称
    }

    return OK;
}


// 邻接矩阵的深度优先递归算法
void DFS(MGraph G, int i) {
    // 该顶点已被访问，标志改变
    visited[i] = true;
    cout << G.vexs[i] << " ";  // 打印输出顶点

    for( int j = 0; j < G.numNodes; j++ ) {
        if( G.arc[i][j] == 1 && !visited[j] ) {  // 查找与i顶点联通而且未被访问顶点
            DFS(G,j);
        }
    }
}

// 邻接矩阵深度遍历操作
Status DFSTravese(MGraph G) {
    // 初始化所有顶点都是未访问状态
    for( int i = 0; i < G.numNodes; i++ ) {
        visited[i] = false;
    }

    // 遍历
    for( int j = 0; j < G.numNodes; j++ ) {
        if( !visited[j] ) {  // 对未访问的顶点调用DFS
            DFS(G,j);
        }
    }

    return OK;
}

// 邻接矩阵的广度遍历操作
Status BFSTravese(MGraph G) {
    // 创建辅助队列
    queue<VertexType> Q;
    // // 初始化所有顶点都是未访问状态
    for( int i = 0; i < G.numNodes; i++ ) {
        visited[i] = false;
    }

    // 遍历
    for( int j = 0; j < G.numNodes; j++ ) {
        if( !visited[j] ) {  // 顶点未被访问过，进行处理
            visited[j] = true;
            cout << G.vexs[j] << " ";  // 打印
            Q.push(visited[j]);  // 该顶点入队

            while( !Q.empty() ) {  // 队列不为空
                // 将队首元素出队
                Q.pop();

                for( int k = 0; k < G.numNodes; k++ ) {
                    // 判断其他顶点若与当前顶点存在边而且没有被访问过
                    if( G.arc[j][k] == 1 && !visited[j] ) {
                        visited[k] = true;
                        cout << G.vexs[k] << " ";  // 打印该顶点
                        Q.push(visited[k]);  // 该元素入队
                    }
                }
            }
        }
    }

    return OK;
}


// 最小生成树算法---Prim算法
Status MiniSpanTreePrim(MGraph G) {
    
    int lowcost[MAXVEX];  // 记录当前顶点集合到剩下的点的最低权值，“0”表示已访问过的点，无需访问
    int adjvex[MAXVEX];  // 记录当前被更新的最低权值来自于哪个点，相当于记录是边的起始点，lowcost的下标表示的是最低权值的终止点

    lowcost[0] = 0;  // 从V0开始生成最小树， lowcost[0] = 0; 表示V0已经加入最小生成树中
    adjvex[0] = 0;  // 由于从V0开始，所以最低权值来自V0点，所以边的起点记录为0

    // 循环除下标为0以外的全部顶点，将与V0相关的边的权值全部存到lowcost中
    for( int i = 0; i < G.numNodes; ++i ) {

        lowcost[i] = G.arc[0][i];  // 将与V0相关的边的权值存入
        adjvex[i] = 0;  // 初始化都为V0下标  
    }

    int min{0};  // 存储最小权值
    
    for( int j = 1; j < G.numNodes; ++j ) {

        min = GRAPH_INFINITY;  // 初始化最小权值为 ∞
        int m = 1;
        int k = 0;
         // 循环V0以外的其他顶点，找到V0与其他顶点间存在的最小权值是哪个顶点
        while( m < G.numNodes ) {
            
            if( lowcost[m] != 0 && lowcost[m] < min ) {
                // 顶点未被加入到最小生成树中(lowcost[m] != 0) 而且 权值小于min
                min = lowcost[m];  // min保存新的最小权值
                k = j;  // 最小权值的顶点下标存入k
            }

            ++m;
        }

        // 经过循环之后，可以得到当前被更新的最低权值是多少(lowcost[k])，来自于哪个点，在k中存着
        cout << lowcost[k] << " ";  // 打印最小权值，也可以存起来
        
        lowcost[k] = 0;  // 将当前顶点的权值设为0，表示当前顶点加入了最小生成树中，任务完成，接下来以该顶点为边的起点
        // 循环与顶点k相关顶点（未被加入生成树中的顶点）的边权值，更新lowcost数组，将小权值存入
        for( int x = 1; x < G.numNodes; ++x ) {
            
            // 如果起点为k的边的权值小于这些顶点未被加入生成树的权值，进行替换
            if( lowcost[x] != 0 && G.arc[k][x] < lowcost[x]) {
                
                lowcost[x] = G.arc[k][x];  // 将较小的权值存入lowcost下标相应位置
                adjvex[x] = k;  // 将下标为k的顶点存入adjvex
            }
        } 
    }

    return OK;
}