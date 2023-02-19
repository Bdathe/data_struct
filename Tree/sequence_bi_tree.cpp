// 顺序二叉树
#include <iostream>
#include <string>
#include <math.h>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1
#define MAXSIZE 100  // 分配的最大空间
#define MAX_TREE_SIZE 100  // 二叉树的最大结点数

typedef int ElemType;  // 数据类型
typedef int Status;  // 函数的状态

ElemType Nil = 0;  // 设整形0为空，一种状态

// 该函数可以确定子树双亲的下标
int GetParentIndex(int i) {
    if( 0 == i % 2 )
        return (i-2)/2;
    else
        return (i-1)/2;
}

// 访问函数
Status Visit(ElemType e) {
    cout << e  << " ";

    return OK;
}

/*
    二叉树的结构体定义
*/
typedef ElemType SqBiTree[MAX_TREE_SIZE];  // 0号位置存储根节点

typedef struct {
    int level;  // 该节点在二叉树的层数
    int order;  // 该节点在level层从左到右的序号（按满二叉树编号）
}Position;

// 顺序二叉树的相关操作

// 初始化二叉树，构造空二叉树
Status InitBiTree(SqBiTree T);  // 这里不需要&，因为传入的数组名本身就是地址，而我们的数组也是在栈区创建的，长度是固定的，所以不需要引用传入
// 按层序次序输入二叉树结点的值，构造顺序二叉树
Status CreatBiTree(SqBiTree T);
// 判断二叉树是否为空,空返回true，否则返回true
bool IsEmpty(SqBiTree T);
// 得到书树的结点数
int GetNodeCount(SqBiTree T);
// 获取二叉树的深度
int GetDepth(SqBiTree T);
// 获取根节点有效值,返回0表示树不存在
ElemType GetRoot(SqBiTree T);
// 获取有第i个结点的双亲
ElemType GetParent(SqBiTree T,int i);
// 返回i结点的左孩子
ElemType LiftChild(SqBiTree T, int i);
// 返回i结点的右孩子
ElemType RightChild(SqBiTree T, int i);
// 先序遍历，i为下标序号，并不是结点序号
Status PreOrderTravese(SqBiTree T, int i);
// 中序遍历，i为下标序号，并不是结点序号
Status InOrderTravese(SqBiTree T, int i);
// 后序遍历，i为下标序号，并不是结点序号
Status PostOrderTravese(SqBiTree T,int i);


int main()
{
    std::string str;
    // 创造树
    SqBiTree T;
    InitBiTree(T);
    CreatBiTree(T);

    IsEmpty(T) ? str = "为空" : str = "不为空" ;
    cout << "树是否为为空：" <<  str << endl;
    cout << "树的结点数：" << GetNodeCount(T) << endl;
    cout << "树的深度：" << GetDepth(T) << endl;
    cout << "根节点的有效值：" << GetRoot(T) << endl;
    cout << "第5个结点的双亲：" << GetParent(T,5) << endl;
    cout << "第4个结点的左孩子：" << LiftChild(T,4) << endl;
    cout << "第3个结点的右孩子：" << RightChild(T,3) << endl;
    
    // 遍历
    cout << endl << "先序遍历：" << endl;
    PreOrderTravese(T,0);
    cout << endl << "中序遍历：" << endl;
    InOrderTravese(T,0);
    cout << endl << "后续遍历：" << endl;
    PostOrderTravese(T,0);

    return 0;
}

// 初始化二叉树，构造空二叉树
Status InitBiTree(SqBiTree T) {
    for( int i = 0; i < MAXSIZE; i++ ) {
        T[i] = Nil;  // 赋初值为空
    }

    return OK;
}


// 按层序次序输入二叉树结点的值，构造顺序二叉树
Status CreatBiTree(SqBiTree T) {
    int i = 0;
    cout << "请按层序输入结点的值，0表示空结点,以-1结束结点数 <= " << MAX_TREE_SIZE << endl;

    int nValue = 0;  // 存储用户的输入
    while( i < MAX_TREE_SIZE && cin >> nValue && nValue != -1 ) {  // 用户有输入，树中有结点可以存储这个值，而且输入的值不为-1
        if( Nil != T[i] && 0 != i && Nil == T[GetParentIndex(i)] ) {  // 此节点不为空,无双亲且不是根节点
            cout << "出现无双亲的非根节点:" << T[i] << "输入有误！" << endl;
            exit(-1);
        }
        else {
            T[i] = nValue;
            i++;
        }
    }

    // 存储-1表示结束
    T[i] = -1;

    return 0;
}

// 判断二叉树是否为空,空返回true，否则返回true
bool IsEmpty(SqBiTree T) {
    if( Nil == T[0] )  // 根节点为空，则树为空
        return true;
    else 
        return false;
}

// 得到书树的结点数
int GetNodeCount(SqBiTree T) {
    int count = 0;  // 计数
    int i = 0;
    while( T[i] != -1 ) {
        if( T[i] != 0 ) {
            count++;
        }
        i++;
    }

    return count;
}

// 获取二叉树的深度
int GetDepth(SqBiTree T) {
    // k层树最大结点为 (2^k) - 1
    int depth = 1;  // 存储树的深度,初始默认为1
    int len = GetNodeCount(T);  // 存储树的结点数

    // 如果该深度下最大结点数小于该树的结点总数，则说明树的深度比当前深度深，深度递增
    while( (int)pow(2,depth) - 1 < len ) {
        depth++;
    }

    return depth;
}

// 获取根节点有效值
ElemType GetRoot(SqBiTree T) {
    if( IsEmpty(T) )
        return ERROR;
    else
        return T[0];
}

// 获取结点的双亲
ElemType GetParent(SqBiTree T, int i) {
    // i是否合理
    if( i > GetNodeCount(T) )
        return ERROR;

    if( IsEmpty(T) ) 
        return ERROR;
    else
        return T[GetParentIndex(i-1)];
}

// 返回i结点的左孩子
ElemType LiftChild(SqBiTree T, int i) {
    if( IsEmpty(T) || Nil == T[i] ) {  // 空树或者i结点为空
        return ERROR;
    }
    else {
        if( T[2*i - 1] == 0 || T[2*i - 1] == -1 )  // 不存在
            return ERROR;  
        else
            return T[2*i - 1];
        
    }
}

// 返回i结点的右孩子
ElemType RightChild(SqBiTree T, int i) {
    if( IsEmpty(T) || Nil == T[i] ) {  // 空树或者i结点为空
        return ERROR;
    }
    else {
        // 判断右孩子是否存在
        if( T[2*i] == 0 || T[2*i] == -1 )  // 不存在
            return ERROR;  
        else
            return T[2*i];
    }
}

// 先序遍历，i为下标序号，并不是结点序号
Status PreOrderTravese(SqBiTree T, int i) {

    if( IsEmpty(T) ) {
        return ERROR;
    }
    else {
        // 首先访问根节点
        Visit(T[i]);
        // 先序遍历左孩子
        if( T[2*i + 1] != Nil && T[2*i + 1] != -1) {  // 左孩子存在
            PreOrderTravese(T,2*i + 1);
        }
        // 先序遍历右孩子
        if( T[2*i + 2] != Nil && T[2*i + 2] != -1) {  // 右孩子存在
            PreOrderTravese(T,2*i + 2);
        }
    }

    return OK;
   
}

// 中序遍历，i为下标序号，并不是结点序号
Status InOrderTravese(SqBiTree T, int i) {
    if( IsEmpty(T) ) {
        return ERROR;
    }
    else {
        //  中序遍历左子树
        if( T[2*i + 1] != Nil && T[2*i + 1] != -1) {  // 左孩子存在
            InOrderTravese(T, 2*i + 1);
        }

        // 访问根节点
        Visit(T[i]);

        // 中序遍历右子树
        if( T[2*i + 2] != Nil && T[2*i + 2] != -1) {  // 右孩子存在
            InOrderTravese(T,2*i + 2);
        }
    }

    return OK;
}

// 后序遍历，i为下标序号，并不是结点序号
Status PostOrderTravese(SqBiTree T,int i) {
     if( IsEmpty(T) ) {
        return ERROR;
    }
    else {
        // 后序遍历左子树
        if( T[2*i + 1] != Nil && T[2*i + 1] != -1) {  // 左孩子存在
            PostOrderTravese(T, 2*i + 1);
        }

        // 后序遍历右子树
         if( T[2*i + 2] != Nil && T[2*i + 2] != -1) {  // 右孩子存在
            PostOrderTravese(T,2*i + 2);
        }

        // 访问根结点
        Visit(T[i]);
    }

    return OK;
}