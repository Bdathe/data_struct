// 循环链表 --- 为了操作方便，使用尾指针来操纵循环链表
#include <iostream>
using std::cout;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1

typedef int ElemType;  // 数据类型
typedef int Status;  // 函数的状态

/*
    循环链表的结构体表示
*/
typedef struct Node {
    ElemType data;  // 数据域
    struct Node* pNext;  // 指针域
}LNode,*CircularLinkList;

// 循环链表的相关操作
// 循环链表的初始化
Status InitList(CircularLinkList& L);
// 判断循环链表是否为空
bool IsEmpty(CircularLinkList L);
// 清空循环链表
Status ClearLinkList(CircularLinkList& L);
// 链表长度（有效元素个数）
int GetLength(CircularLinkList L);
// 取出单链表中i位置的元素,返回该元素,i从1开始
ElemType GetElem(CircularLinkList L, int i);
// 插入节点,在第i个结点前，插入一个有效值为e的新结点
Status InsertNode(CircularLinkList &L, int i, ElemType e);
// 删除节点,删除第i个结点，并将删除结点的有效值存储在e中
Status DeleteNode(CircularLinkList &L, int i, ElemType &e);
// 尾插法建立链表
Status BackCreat(CircularLinkList &L, ElemType e);
// 遍历
void Travese(CircularLinkList L);


int main()
{
    // 创建循环链表
    CircularLinkList L;
    // 初始化
    InitList(L);
    // 头插法建立链表
    BackCreat(L,1);
    BackCreat(L,3);
    BackCreat(L,5);

    ElemType e;

    InsertNode(L,2,2);
    DeleteNode(L,2,e);
    Travese(L);

    cout << "e = " << e << endl;
    cout << "The length is : " << GetLength(L) << endl;
    cout << "Is empty : " << IsEmpty(L) << endl;
    ClearLinkList(L);
    cout << "Is empty : " << IsEmpty(L) << endl;


    return 0;
}

// 循环链表的初始化
Status InitList(CircularLinkList& L) {
    // 创造头结点，尾指针指向头结点
    LNode* pRear = new LNode;
    if( pRear == NULL ) {
        exit(-1);
    }

    pRear->pNext = pRear;  // 首尾相连
    L = pRear;

    return OK;
}

// 判断循环链表是否为空
bool IsEmpty(CircularLinkList L) {
    // 保存头结点
    if( L->pNext == L ) {
        return true;
    }
    else {
        return false;
    }
}


// 清空循环链表
Status ClearLinkList(CircularLinkList& L) {
    if( IsEmpty(L) ) {
        return OK;
    }

    // 保留头结点，其余结点全部释放
    // 保存头结点
    LNode* pHead = L->pNext;

    // 与释放单链表的结点步骤一致
    LNode* p = pHead->pNext;
    LNode* q = NULL;
    while( p->pNext != L->pNext ) {
        q = p->pNext;
        delete p;
        p = q;
    }

    // 释放最后一个结点
    delete p;
    p = NULL;
    q = NULL;
    
    // 首尾相连
    pHead->pNext = pHead;
    L = pHead;  // 尾指针指向头结点

    return OK;
}

// 链表长度（有效元素个数）
int GetLength(CircularLinkList L) {
    int len = 0;  // 计数
    // 存储头结点
    LNode* p = L->pNext;
    while( p->pNext != L->pNext ) {  // L->pNext为头结点
        len++;
        p = p->pNext;
    }

    return len;
}

// 取出单链表中i位置的元素,返回该元素,i从1开始
ElemType GetElem(CircularLinkList L, int i) {
    // 判断i是否合理
    if( i < 1 || i > GetLength(L) ) {
        cout << "取出元素的位置不合理！" << "\n";
        return ILLEGAL;
    }
    else {
        // 定位到i结点
        int j = 0;
        LNode* p = L->pNext;

        while( p->pNext != L->pNext && j < i ) {
            j++;
            p = p->pNext;
        }

        return p->data;
    }
}

// 插入节点,在第i个结点前，插入一个有效值为e的新结点
Status InsertNode(CircularLinkList &L, int i, ElemType e) {
    // 判断i是否合理
    if( i < 1 || i > GetLength(L) ) {
        return ERROR;
    }
    else {
        // 定位到i结点的前一个结点
        LNode* p = L->pNext;
        int j = 0;

        while( p->pNext != L->pNext && j < i - 1 ) {
            j++;
            p = p->pNext;
        }

        // 创造新的结点并插入
        LNode* newNode = new LNode;
        if(newNode == NULL) {
            exit(-1); //异常退出
        }
        else {
            newNode->data = e;
            newNode->pNext = p->pNext;
            p->pNext = newNode;
        }
    }

    return OK;
}

// 删除节点,删除第i个结点，并将删除结点的有效值存储在e中
Status DeleteNode(CircularLinkList &L, int i, ElemType &e) {
     // 判断删除位置是否合理
    if( i < 1 || i > GetLength(L) ) {
        return ERROR;
    }
    else {
        // 定位i结点的前一个结点
        LNode* p = L->pNext;
        int j = 0;

        while( p->pNext != L->pNext && j < i - 1 ) {
            p = p->pNext;
            j++;
        }

        // 保存i结点
        LNode* temp = p->pNext;
        e = temp->data;

        // i前一个结点的指针域指向i下一个结点
        p->pNext = p->pNext->pNext;

        // 删除i结点
        delete temp;
        temp = NULL;

        return OK;
    }
}


// 尾插法建立链表
Status BackCreat(CircularLinkList &L, ElemType e) {
    // 创建新结点
    LNode* newNode = new LNode;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->data = e;
        newNode->pNext = L->pNext;  // 首尾相连
    }

    // 尾插
    L->pNext = newNode;
    L = newNode;  // 尾指针指向新插入的尾结点

    return OK;
}


// 遍历
void Travese(CircularLinkList L) {
    LNode* p = L->pNext->pNext;  // 保存首结点

    while( p != L->pNext ) {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << endl;

    return;

}