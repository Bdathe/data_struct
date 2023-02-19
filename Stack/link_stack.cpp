// 链栈
#include <iostream>
using std::cout;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1

typedef int ElemType;  // 数据类型
typedef int Status;  // 函数的状态

/*
    链栈的结构体表示
*/
typedef struct StackNode {
    ElemType data;  // 数据域
    struct StackNode* pNext;  // 指针域
}StackNode, *LinkStack;

// 对链栈的相关操作

// 初始化链栈
Status InitStack(LinkStack& S);
// 判断栈是否为空
Status IsEmpty(LinkStack S);
// 栈中有效元素数量
int GetLength(LinkStack S);
// 压栈
Status Push(LinkStack& S, ElemType e);
// 出栈，返回值为出栈元素
ElemType Pop(LinkStack& S);
// 遍历栈
void Travese(LinkStack S);
// 清空栈
Status ClearStack(LinkStack& S);

int main()
{
    // 创建链栈
    LinkStack S;
    // 初始化
    InitStack(S);
    // 入栈 
    Push(S,1);
    Push(S,3);
    Push(S,5);
    Travese(S);

    // cout << Pop(S) << " ";
    // cout << Pop(S) << " ";
    // cout << Pop(S) << endl;

    ClearStack(S);
    cout << "Is empty : " << IsEmpty(S) << endl;

    return 0;
}


// 初始化链栈
Status InitStack(LinkStack& S) {
    // 创建头节点
    StackNode* headNode = new StackNode;
    if( headNode == NULL ) {
        exit(-1);
    }
    else {
        headNode->pNext = NULL;
    }

    // 将头指针 赋值给 S ，完成创建操作
    S = headNode;

    return OK;
}

// 判断栈是否为空
Status IsEmpty(LinkStack S) {
    if( S->pNext == NULL ) {
        return true;
    }
    else {
        return false;
    }
}

// 栈中有效元素数量
int GetLength(LinkStack S) {

    int len = 0;  // 计数
    // 遍历
    StackNode* p = S;
    while( p->pNext != NULL ) {
        len++;
        p = p->pNext;
    }

    return len;
}

// 压栈
Status Push(LinkStack& S, ElemType e) {
    // 创建新结点
    StackNode* newNode = new StackNode;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->data = e;
        newNode->pNext = NULL;
    }

    // 定位到尾结点
    StackNode* p = S;
    while( p->pNext != NULL ) {
        p = p->pNext;
    }

    // 入栈
    p->pNext = newNode;

    return OK;
}

// 出栈，返回值为出栈元素
ElemType Pop(LinkStack& S) {
    // 定位到尾结点的前一个结点
    int index = 0;
    StackNode* p = S;
    while( p->pNext != NULL && index < GetLength(S) - 1) {
        p = p->pNext;
        index++;
    }

    // 保存要删除的结点
    StackNode* q = p->pNext;
    ElemType e = q->data;

    // 删除
    p->pNext = NULL;
    delete q;
    q = NULL;

    return e;
}

// 遍历栈
void Travese(LinkStack S) {
    StackNode* p = S;
    while( p->pNext != NULL ) {

        p = p->pNext;
        cout << p->data << " ";
    }

    cout << endl;

    return;
}

// 清空栈
Status ClearStack(LinkStack& S) {
    // 清除其余结点，保留头结点
    StackNode* p = S->pNext;
    StackNode* q = NULL;

    while( p->pNext != NULL ) {

        q = p->pNext;
        delete p;
        p = q;
    }

    // 删除最后一个结点
    delete p;
    p = NULL;
    q = NULL;

    S->pNext = NULL;

    return OK;
}