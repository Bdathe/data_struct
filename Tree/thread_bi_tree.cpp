#include <iostream>
#include <string.h>
#include <string>
using std::cout;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1
#define MAXSIZE 100

typedef int Status;  // Status表示函数的状态
typedef char ElemType; 
typedef enum {Link , Thread} PointerTag;  // Link = 0，表示指向左右孩子指针； Thread = 1，表示指向前驱或者后继的线索

// 线索二叉树结点的结构体表示
typedef struct ThrBiNode {
    ElemType data;  // 结点有效数据
    struct ThrBiNode* lchild;  // 左孩子指针
    struct ThrBiNode* rchild;  // 右孩子指针
    PointerTag lTag;  // 左标志
    PointerTag rTag;  // 右标志
}ThrBiNode, *ThrBiTree;

ElemType Nil = '#';  // 字符型数据以 # 为空

// 访问函数
Status Vist(ElemType e) {
    cout << e << " ";

    return OK;
}

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


//  对线索二叉树的相关操作

// 初始化二叉树，构造空二叉树
Status InitThrBiTree(ThrBiTree& T);
// 先序构造线索二叉树
Status CreatThrBiTree(ThrBiTree& T);
// 中序遍历进行线索化
Status InThreading(ThrBiTree& T);
// 中序遍历二叉树，并将中序线索化，Thrt指向头结点
Status InOrderThreading(ThrBiTree& Thrt, ThrBiTree T);
// 中序遍历线索二叉树,H为头结点
void InOrderTravese_Thr(ThrBiTree H);

int main()
{
    // 创建头结点
    ThrBiNode* head = NULL;
    // 创建树
    ThrBiTree T;
    // 初始化
    InitThrBiTree(T);
    StrAssign(str,"ABDG##H###CE#I##F##");
    CreatThrBiTree(T);

    // 中序遍历线索化
    InOrderThreading(head,T);
    // 中序遍历输出
    cout << "中序遍历输出：" << endl;
    InOrderTravese_Thr(head);

    return 0;
}

// 初始化二叉树，构造空二叉树
Status InitThrBiTree(ThrBiTree& T) {
    T = NULL;

    return OK;
}


// 先序构造线索二叉树,按照前序顺序输入
Status CreatThrBiTree(ThrBiTree& T) {
    ElemType cValue;
    cValue = str[nIndex++];

    if( Nil == cValue ) {
        T = NULL;
    }
    else {
        // 创造新结点
        T = new ThrBiNode;
        if( NULL == T ) {
            exit(-1);
        }
        
        // 生成根节点
        T->data = cValue;

        // 递归构造左子树
        if( T->lchild ) {
            CreatThrBiTree(T->lchild);
            T->lTag = Link;  // 有左子树
        }
        else {
            T->lTag = Thread;  // 无左子树，线索化
        }

        // 递归构造右子树
        if( T->rchild ) {
            CreatThrBiTree(T->rchild);
            T->rTag = Link;  // 有右子树
        }
        else {
            T->rTag = Thread;  // 无右子树，线索化
        }
    }

    return OK;
}

ThrBiTree pre;  // 全局变量，始终指向T的前驱
// 中序遍历进行线索化
Status InThreading(ThrBiTree& T) {

    if( T ) {  // 二叉树存在
        InThreading(T->lchild);  // 左子树线索化
        if( !T->lchild ) {  // 左孩子不存在
            T->lTag = Thread;  // 前驱线索
            T->lchild = pre;  // 左孩子指向谦虚
        }

        if( !pre->rchild ) {  // 前驱没有右孩子，说明当前结点T就是前驱的后继
            pre->rTag = Thread;  // 后继线索
            pre->rchild = T;  // 前驱右孩子指向后继（当前节点T）
        }

        pre = T;  // 保持pre指向下一个T的前驱，也就是当前的T
        if( T->rchild ) {
            InThreading(T->rchild); // 递归右孩子线索化
        }
    }

    return OK;
}


// 中序遍历二叉树，并将中序线索化，Thrt指向头结点
// 线索化后的二叉树，就如同操作一个双向链表。于是我们想到为二叉树增设一个头结点，这样就和双向链表一样，即能够从第一个结点正向开始遍历，也可以从最后一个结点逆向遍历。
Status InOrderThreading(ThrBiTree& Thrt, ThrBiTree T) {

    Thrt = new ThrBiNode;
    if( !Thrt )
        exit(-1);

    // 建立头结点,头结点的左孩子为根节点，右孩子指向自身
    Thrt->lTag = Link;
    Thrt->rTag = Thread;
    Thrt->rchild = Thrt;  // 右孩子指向自身
    if( !T ) {  // 二叉树为空
        Thrt->lchild = Thrt;  //左孩子指向自身
    }
    else {
        Thrt->lchild = T;  // 头结点的左孩子为根节点
        pre = Thrt;  // 头结点Thrt为根节点T的前驱
        // 进行中序遍历线索化
        InThreading(T);
        // 线索化结束后，pre指向最后一个结点
        pre->rTag = Thread;
        pre->rchild = Thrt;  // 最后一个结点的后继指向头结点
    }

    return OK;
}

// 中序遍历线索二叉树
void InOrderTravese_Thr(ThrBiTree H) {
    ThrBiTree p;
    p = H->lchild;  // p指向根节点

    while( p != H ) {  // 空树或者遍历结束时， p == H
        while( p->lTag == Link ) {
            p = p->lchild;
        }
        // 访问左子树根结点
        Vist(p->data);

        // 查看后继
        while( p->rTag == Thread && p->rchild != H ) { 
            // 访问后继结点
            p = p->rchild;
            Vist(p->data);  
        }

        p = p->rchild;  // p跟进至右子树根
    }
}