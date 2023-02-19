// 双向循环链表
#include <iostream>
using std::cout;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1

typedef int ElemType;  // 数据类型
typedef int Status;  // 函数的状态

/*
    双向循环链表的结构体表示
*/
typedef struct Node {
    ElemType data;  // 数据域
    struct Node* pPrev;  // 指针域 --- 前驱结点
    struct Node* pNext;  // 指针域 --- 后继结点
}LNode,*DoubleCircularLinkedList;

// 双向链表的相关处理
// 双向链表的初始化
Status InitList(DoubleCircularLinkedList& L);
// 判断链表是否为空
bool IsEmpty(DoubleCircularLinkedList L);
// 获得链表有效长度
int GetLength(DoubleCircularLinkedList L);
// 尾插
Status PushBack(DoubleCircularLinkedList& L, ElemType e);
// 尾删,删除的值返回
ElemType PopBack(DoubleCircularLinkedList& L);
// 头插
Status PushFront(DoubleCircularLinkedList& L, ElemType e);
// 头删，删除的值返回
Status PopFront(DoubleCircularLinkedList& L);
// 在i结点前面插入一个结点
Status InsertNode(DoubleCircularLinkedList& L, int i, ElemType e);
// 删除i结点，返回值为i结点的有效值
ElemType DeleteNode(DoubleCircularLinkedList L, int i);
// 遍历
void Travese(DoubleCircularLinkedList L);

int main()
{
    // 创建双向循环链表
    DoubleCircularLinkedList L;
    // 初始化
    InitList(L);
    // 尾插
    PushBack(L,1);
    PushBack(L,3);
    PushBack(L,5);
    PushFront(L,2);

    cout << PopBack(L) << endl;
    cout << PopFront(L) << endl;
    InsertNode(L,1,3);
    cout << DeleteNode(L,2) << endl;
    cout << "The length is : " << GetLength(L) << endl;
    Travese(L);


    cout << "Is empty is : " << IsEmpty(L) << endl;

    return 0;
}

// 双向循环链表的初始化
Status InitList(DoubleCircularLinkedList& L) {
    // 申请头结点
    LNode* headNode = new LNode;
    if( headNode == NULL ) {
        exit(-1);
    }
    else {
        headNode->pPrev = NULL;
        headNode->pNext = NULL;
    }

    // 因为为带头的双向循环链表,因此初始化头结点时，头结点的prev,next指针都指向自已
    headNode->pPrev = headNode;
    headNode->pNext = headNode;

    L = headNode;

    return OK;
}

// 判断链表是否为空
bool IsEmpty(DoubleCircularLinkedList L) {
    if( L->pPrev == L || L->pNext == L ) {
        return true;
    }
    else {
        return false;
    }
}

// 获得链表有效长度
int GetLength(DoubleCircularLinkedList L) {
    int len = 0;  // 计数
    LNode* p = L;
    while( p->pNext != L ) {
        p = p->pNext;
        len++;
    }

    return len;
}

// 尾插
Status PushBack(DoubleCircularLinkedList& L, ElemType e) {
    // 申请新结点
    LNode* newNode = new LNode;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->pNext = NULL;
        newNode->pPrev = NULL;
        newNode->data = e;
    }

    // 尾插
    // 新结点的前驱指向尾结点，后继指向头结点
    newNode->pPrev = L->pPrev;  // 通过头结点的prev找到尾结点
    newNode->pNext = L;

    // 尾结点的后继指向新结点
    L->pPrev->pNext = newNode;
    //头结点的前驱指向新结点
    L->pPrev = newNode;

    return OK;
}

// 尾删,删除的值返回
ElemType PopBack(DoubleCircularLinkedList& L) {
    // 保存尾结点
    LNode* tail = L->pPrev;
    ElemType e = tail->data;

    // 尾结点的前一个结点的后继指向头结点
    tail->pPrev->pNext = L;
    // 头结点的前驱指向尾结点的前一个结点
    L->pPrev = tail->pPrev;

    // 删除尾结点
    delete tail;
    tail = NULL;

    return e;
}

// 头插
Status PushFront(DoubleCircularLinkedList& L, ElemType e) {
    // 申请新结点
    LNode* newNode = new LNode;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->pNext = NULL;
        newNode->pPrev = NULL;
        newNode->data = e;
    }

    // 头插
    // 新结点的后继指向首结点
    newNode->pNext = L->pNext;
    // 新结点的前驱指向头结点
    newNode->pPrev = L;
    // 首结点的前驱指向新结点
    L->pNext->pPrev = newNode;
    // 头结点的后继指向新结点
    L->pNext = newNode;

    return OK;
}

// 头删，删除的值返回
Status PopFront(DoubleCircularLinkedList& L) {
    // 保存首结点
    LNode* first = L->pNext;
    ElemType e = first->data;

    // 首结点的下一个结点的的前驱指向头结点
    first->pNext->pPrev = L;
    // 头结点的后继指向首结点的下一个结点
    L->pNext = first->pNext;

    // 释放首结点
    delete first;
    first = NULL;

    return e;
}

// 在i结点前面插入一个结点
Status InsertNode(DoubleCircularLinkedList& L, int i, ElemType e) {
    // 判断i是否合理
    if( i < 1 || i > GetLength(L) ) {
        return ERROR;
    }

    // 定位到i结点的前一个结点
    LNode* p = L;
    int j = 0;

    while( p->pNext != L && j < i - 1 ) {
        j++;
        p = p->pNext;
    }

    // 申请新结点
    LNode* newNode = new LNode;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->pNext = NULL;
        newNode->pPrev = NULL;
        newNode->data = e;
    }

    // 插入
    // 新结点的后继为i结点，前驱为i-1结点
    newNode->pNext = p->pNext;
    newNode->pPrev = p;
    // i结点的前驱为新结点，i-1的后继结点为新结点
    p->pNext->pPrev = newNode;
    p->pNext = newNode;
    
    return OK;
}

// 删除i结点，返回值为i结点的有效值
ElemType DeleteNode(DoubleCircularLinkedList L, int i ) {
     // 判断i是否合理
    if( i < 1 || i > GetLength(L) ) {
        return ERROR;
    } 

     // 定位到i结点的前一个结点
    LNode* p = L;
    int j = 0;

    while( p->pNext != L && j < i - 1 ) {
        j++;
        p = p->pNext;
    }

    // 保存i结点
    LNode* temp = p->pNext;
    ElemType e = temp->data;

    // i-1结点的后继为i+1,i+1结点的前驱为i-1结点
    p->pNext = temp->pNext;
    temp->pNext->pPrev = temp->pPrev;

    // 删除i结点
    delete temp;
    temp = NULL;

    return e;
}

// 遍历
void Travese(DoubleCircularLinkedList L) {
    LNode* p = L->pNext;
    while( p != L ) {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << endl;

    return;
}