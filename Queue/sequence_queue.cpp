// 顺序队
#include <iostream>
using std::cout;
using std::endl;

#define MAXSIZE 100  // 顺序表最大容量
#define OK 1
#define ERROR 0
#define ILLEGAL -1

typedef int ElemType;  // 数据类型
typedef int Status;  // 函数的状态

/*
    顺序队列的结构体定义
*/
typedef struct {
    ElemType* elem;  // 动态数组
    int front;  // 头指针
    int rear;  // 尾指针,指向尾元素的后一个预留的空位置
}SqQueue;

// 对队列的相关操作

// 队列的初始化
Status InitQueue(SqQueue& Q);
// 队列长度（有效元素个数）
int GetLength(SqQueue Q);
// 队列是否为空
bool IsEmpty(SqQueue Q);
// 队列是否满
bool IsFull(SqQueue Q);
// 循环队列的入队
Status EnQueue(SqQueue& Q, ElemType e);
// 循环队列的出队,返回值为出队元素
ElemType DeQueue(SqQueue& Q);
// 取队头元素
ElemType GetHead(SqQueue Q);
// 遍历队列
void Travese(SqQueue Q);


int main()
{
    // 创建队列
    SqQueue Q;
    // 初始化
    InitQueue(Q);
    // 入队
    EnQueue(Q,1);
    EnQueue(Q,3);
    EnQueue(Q,5);
    Travese(Q);

    cout << "Length = " << GetLength(Q) << endl;
    cout << "Head = " << GetHead(Q) << endl;

    cout << DeQueue(Q) << " ";
    cout << DeQueue(Q) << " ";
    cout << DeQueue(Q) << endl;

    cout << "Is Empty : " << IsEmpty(Q) << endl;

    return 0;
}

// 队列的初始化
Status InitQueue(SqQueue& Q) {
    // 给数组分配空间
    Q.elem = new ElemType[MAXSIZE];
    if( Q.elem == NULL ) {
        exit(-1);
    }
    else {
        // 头指针和尾指针置为0，队列为空
        Q.front = 0;  
        Q.rear = 0;
    }

    return OK;
}

// 队列长度（有效元素个数）
int GetLength(SqQueue Q) {
    // ( 尾指针 - 首指针 + 最大容量 ) % 最大容量 = 循环队列的长度
    int len = (Q.rear - Q.front + MAXSIZE) % MAXSIZE;

    return len;
}

// 队列是否为空
bool IsEmpty(SqQueue Q) {
    
    if( Q.rear == Q.front ) {
        return true;
    }
    else {
        return false;
    }
}

// 队列是否满
bool IsFull(SqQueue Q) {

    if( ( Q.rear + 1 ) % MAXSIZE == Q.front ) {
        return true;
    }
    else {
        return false;
    }
}

// 循环队列的入队
Status EnQueue(SqQueue& Q, ElemType e) {
    // 判断是否队列满
    if( IsFull(Q) ) {
        return ERROR;
    }
    else {

        // 新元素加入队尾
        Q.elem[Q.rear] = e;
        // 队尾指针 + 1
        Q.rear = ( Q.rear + 1 ) % MAXSIZE;
    }

    return OK;
}

// 循环队列的出队
ElemType DeQueue(SqQueue& Q) {
    // 判断队列是否为空
    if( IsEmpty(Q) ) {
        return ERROR;
    }
    else {
        ElemType e = Q.elem[Q.front];
        Q.front = ( Q.front + 1 ) % MAXSIZE;

        return e;
    }
}

// 取队头元素
ElemType GetHead(SqQueue Q) {
    // 判断队列是否为空
    if( IsEmpty(Q) == true ) {
        exit(-1);
    }

    return Q.elem[Q.front];
}

// 遍历队列
void Travese(SqQueue Q) {
    
    for( int i = 0; i < GetLength(Q); i++ ) {

        cout << Q.elem[i] << " ";
    }

    cout << endl;

    return;
}