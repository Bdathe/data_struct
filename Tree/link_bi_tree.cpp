// 链式二叉树
#include <iostream>
#include <string.h>
#include <string>
using std::cout;
using std::cin;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1
#define MAXSIZE 100

typedef int Status;  // Status是函数的类型，表示函数的状态，返回值为ERROR，OK等
typedef char ElemType;  // 结点有效值的数据类型设为char
ElemType Nil = '#';  // 字符型以#表示空

/************************用于构造二叉树**********************************/
int nIndex = 1;
typedef char String[MAXSIZE];  // 构造字符数组,0号位置存储字符串长度
String str;

// 字符串初始化
Status StrAssign(String S,const char *chars) {
    if( strlen(chars) > MAXSIZE ) {
        return ERROR;
    }
    else {
        S[0] = strlen(chars);
        for( int i = 1; i <= S[0]; i++ ) {
            S[i] = chars[i - 1];  // char数组中的第一个字符在0号位置
        }

        return OK;
    }
}

/**********************************************************************/

// 二叉树结点的结构体
typedef struct BiNode {
    ElemType data;  // 数据域，结点的数据
    struct BiNode* lchild;  // 左孩子指针
    struct BiNode* rchild;  // 右孩子指针
}BiNode,*LinkBiTree;

// 对链式二叉树的相关操作

// 初始化二叉树
Status InitBiTree(LinkBiTree& T);
// 判断二叉树是否为空，空返回true，否则返回false
bool IsEmpty(LinkBiTree T);
// 销毁二叉树
Status Destory(LinkBiTree& T);
// 创建二叉树 --- 前序创造（按前序输入二叉树各结点的值,#表示空结点）
Status CreatBiTree(LinkBiTree& T);
// 获取二叉树的深度
int GetDepth(LinkBiTree T);
// 返回根节点的有效值
ElemType GetRoot(LinkBiTree T);
// 获取结点数量
int GetNodeCount(LinkBiTree T);
// 前序遍历
void PreOrderTravese(LinkBiTree T);
// 中序遍历
void InOrderTravese(LinkBiTree T);
// 后序遍历
void PostOrderTravese(LinkBiTree T);

int main()
{
    std::string sStr;

    // 创建二叉树
    LinkBiTree T;
    // 初始化
    InitBiTree(T);
    // 创建二叉树
    StrAssign(str,"ABDG##H###CE#I##F##");
    CreatBiTree(T);

    cout << endl << "先序遍历" << endl;
    PreOrderTravese(T);
    cout << endl << "中序遍历" << endl;
    InOrderTravese(T);
    cout << endl << "后序遍历" << endl;
    PostOrderTravese(T);
    
    IsEmpty(T) ? sStr = "空" : sStr = "不为空";
    cout << endl << "二叉树是否为空：" << sStr << endl;
    cout << "树的深度为：" << GetDepth(T) << endl;
    cout << "根节点数据：" << GetRoot(T) << endl;
    cout << "结点数量：" << GetNodeCount(T) << endl;


    return 0;
}

// 初始化二叉树
Status InitBiTree(LinkBiTree& T) {
    T = NULL;  // 头指针指向为NULL
    return OK;
}

// 判断二叉树是否为空，空返回true，否则返回false
bool IsEmpty(LinkBiTree T) {
    if( NULL == T ) 
        return true;
    else
        return false;
}

// 销毁二叉树 --- 后序销毁
Status Destory(LinkBiTree& T) { 
    if( IsEmpty(T) ) {
        cout << "销毁失败，该二叉树不存在！" << endl;
        return ERROR;
    }
    else {
        if( T->lchild )  // 左孩子存在
            Destory(T->lchild);  // 销毁左孩子子树
        if( T->rchild )  // 右孩子存在
            Destory(T->rchild);  // 销毁右孩子子树

        delete T;  // 释放根节点
        T = NULL;  // 空指针赋值NULL

        return OK;
    }
}

// 创建二叉树 --- 前序创造（按前序输入二叉树各结点的值,#表示空结点）
Status CreatBiTree(LinkBiTree& T) {
    ElemType cValue;  // 存储用户的输入
    cValue = str[nIndex++];  // 也可以直接 cin >> cValue;
    
    if( cValue == '#' ) {
        T = NULL;
    }
    else {
        // 申请新结点
        T = new BiNode;
        if(  NULL == T ) {
            exit(-1);  
        }

        T->data = cValue;  // 生成根节点
        CreatBiTree(T->lchild);  // 构造左子树
        CreatBiTree(T->rchild);  // 构造右子树
    }

    return OK;
}

// 获取二叉树的深度
int GetDepth(LinkBiTree T) {
    int m = 0;  // 存储左子树的深度
    int n = 0;  // 存储右子树的深度

    if( IsEmpty(T) ) {
        return 0;  // 空树深度为0
    }
    else {
        // 整个二叉树的深度为根结点的左子树深度和右子树深度最大的那个加上1
        if( NULL != T->lchild ) {
            m = GetDepth(T->lchild);  // 递归求左子树深度
        }

        if( NULL != T->rchild ) {
            n = GetDepth(T->rchild);  // 递归求右子树深度
        }
        
        // 比较哪一个深度大
        if( m > n ) 
            return m + 1;
        else 
            return n + 1;
    }
}


// 返回根节点的有效值
ElemType GetRoot(LinkBiTree T) {
    if( IsEmpty(T) ) {
        return Nil;
    }
    else {
        return T->data;
    }
}

// 获取结点数量
int GetNodeCount(LinkBiTree T) {
    // 结点数量 = 根节点 + 左子树下的结点 + 右子树下的结点

    int m = 0;  // 存储左子树下的结点数量
    int n = 0;  // 存储右子树下的结点数量

    if( IsEmpty(T) ) {
        return 0;  // 空树结点数量为0
    }
    else {
        if( T->lchild ) {  // 左子树存在
            m = GetNodeCount(T->lchild);
        }

        if( T->rchild ) {  // 右子树存在
            n = GetNodeCount(T->rchild);
        }

        return m + n + 1;
    }
}

// 前序遍历
void PreOrderTravese(LinkBiTree T) {
    if( IsEmpty(T) ) 
        return;
    
    // 访问根节点
    cout << T->data << " ";
    // 然后先序遍历左节点
    PreOrderTravese(T->lchild);
    // 最后先序遍历右节点
    PreOrderTravese(T->rchild);
}


// 中序遍历
void InOrderTravese(LinkBiTree T) {
    if( IsEmpty(T) ) 
        return;
    
    // 先中序遍历左节点
    InOrderTravese(T->lchild);
    // 再访问根节点
    cout << T->data << " ";
    // 最后中序遍历右节点
    InOrderTravese(T->rchild);
}


// 后序遍历
void PostOrderTravese(LinkBiTree T) {
    if( IsEmpty(T) ) 
        return;
    
    // 先后序遍历左节点
    PostOrderTravese(T->lchild);
    // 最后后序遍历右节点
    PostOrderTravese(T->rchild);
    // 再访问根节点
    cout << T->data << " ";
    
}
   
