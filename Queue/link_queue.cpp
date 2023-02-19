// 链队
#include <iostream>
using std::cout;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1

typedef int ElemType;  // 数据类型
typedef int Status;  // 函数的状态

/*
    链队结点的结构体表示
*/
typedef struct QueueNode {
    ElemType data;  // 数据域
    struct QueueNode* pNext;  // 指针域
}QNode,*QueuePtr;

// 队头和队尾确定一个链队
typedef struct {
    QueuePtr front;  // 队头指针,指向头结点
    QueuePtr rear;  // 队尾指针，指向尾结点
}LinkQueue;

// 对链队的相关处理

// 链队的初始化
Status InitQueue(LinkQueue& Q);
// 销毁链队
Status DestoryQueue(LinkQueue& Q);
// 清空链队
Status ClearQueue(LinkQueue& Q);
// 判断是否队空
bool IsEmpty(LinkQueue Q);
// 获取队长
int GetLength(LinkQueue Q);
// 入队
Status EnQueue(LinkQueue& Q, ElemType e);
// 出队
ElemType DeQueue(LinkQueue& Q);
// 取队头元素
ElemType GetHead(LinkQueue Q);
// 遍历
void Travese(LinkQueue Q);

int main()
{
    // 创建链队
    LinkQueue Q;
    // 初始化
    InitQueue(Q);
    // 入队
    EnQueue(Q,1);
    EnQueue(Q,3);
    EnQueue(Q,5);
    Travese(Q);
    cout << "Head = " << GetHead(Q) << endl;
    cout << "Length = " << GetLength(Q) << endl;
    cout << DeQueue(Q) << " ";
    cout << DeQueue(Q) << " ";
    cout << DeQueue(Q) << endl;
    
    cout << "Is empty : " << IsEmpty(Q) << endl;

    return 0;
}

// 链队的初始化
Status InitQueue(LinkQueue& Q) {
    // 队头指针和队尾指针都指向头结点，头结点指针域指向为空
    // 创建头结点
    QNode* newNode = new QNode;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->pNext = NULL;
    }

    Q.front = newNode;
    Q.rear = newNode;

    return OK;
}

// 销毁链队
Status DestoryQueue(LinkQueue& Q) {
    // 从队头结点开始，依次释放所有结点
    QNode* p = Q.front;
    while( p->pNext != NULL ) {
        Q.front = p->pNext;
        delete p;
        p = Q.front;
    }

    // 删除最后一个结点
    delete p;
    p = NULL;
    Q.front = NULL;
    Q.rear = NULL;

    return OK;
}


// 清空链队
Status ClearQueue(LinkQueue& Q) {
    // 依次释放除了头结点的其他结点
    QNode* p = Q.front->pNext;

    while( p->pNext != NULL ) {
        Q.front = p->pNext;
        delete p;
        p = Q.front;
    }

    // 删除最后一个结点
    delete p;
    p = NULL;
    Q.rear = Q.front;
    Q.front->pNext = NULL;

    return OK;
}

// 获取队长
int GetLength(LinkQueue Q) {
    QNode* p = Q.front;
    int len = 0;  // 计数

    while( p->pNext != NULL ) {
        len++;
        p = p->pNext;
    }

    return len;
}

// 判断是否队空
bool IsEmpty(LinkQueue Q) {
    if( Q.front == Q.rear ) {
        return true;
    }
    else {
        return false;
    }
}


// 入队
Status EnQueue(LinkQueue& Q, ElemType e) {
    // 将新结点尾插
    // 创建新结点
    QNode* newNode = new QNode;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->pNext = NULL;
        newNode->data = e;
    }

    // 插入
    Q.rear->pNext = newNode;
    Q.rear = newNode;

    return OK;
}

// 出队
ElemType DeQueue(LinkQueue& Q) {
    // 判断是否队空
    if( IsEmpty(Q) ) {
        exit(-1);
    }

    // 头删，删除首结点
    // 保存首结点
    QNode* p = Q.front->pNext;
    ElemType e = p->data;
    // 头结点指针域指向首届点的下一个结点
    Q.front->pNext = Q.front->pNext->pNext;

    // 删除
    delete p;
    p = NULL;

    return e;
}

// 取队头元素
ElemType GetHead(LinkQueue Q) {
    if( IsEmpty(Q) ) {
        exit(-1);
    }

    return Q.front->pNext->data;
}

// 遍历
void Travese(LinkQueue Q) {
    QNode* p = Q.front;
    while( p->pNext != NULL ) {
        p = p->pNext;
        cout << p->data << " ";
    }

    cout << endl;

    return;
}