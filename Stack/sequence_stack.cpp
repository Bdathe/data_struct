// 顺序栈
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
    顺序栈的结构体定义
*/
typedef struct {
    ElemType* elem;  // 动态数组
    int top;  // 栈顶指向
}SqStack;


// 对顺序栈的相关操作

// 栈的初始化
Status InitStack(SqStack& S);
// 判断栈是否为空
bool IsEmpty(SqStack S);
// 判断栈是否满
bool IsFull(SqStack S);
// 压栈
Status Push(SqStack& S , ElemType e);
// 出栈,返回值为出栈元素
ElemType Pop(SqStack& S);
// 遍历栈
void Travese(SqStack S);
// 清空栈
Status ClearStack(SqStack& S);

int main()
{
    // 创建顺序栈
    SqStack S;
    // 初始化
    InitStack(S);
    // 压栈
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


// 栈的初始化
Status InitStack(SqStack& S) {
    // 构造动态数组
    S.elem = new ElemType[MAXSIZE];
    if( S.elem == NULL ) {
        exit(-1);  // 异常退出
    }

    // 栈顶指向为 -1 ，代表空栈
    S.top = -1;

    return OK;
}


// 判断栈是否为空
bool IsEmpty(SqStack S) {
    if( S.top == -1 ) {
        return true;
    }
    else {
        return false;
    }
}


// 判断栈是否满
bool IsFull(SqStack S) {
    if( S.top == MAXSIZE - 1 ) {
        return true;
    }
    else {
        return false;
    }
}


// 压栈
Status Push(SqStack& S , ElemType e) {
    // 判断是否栈满
    if( IsFull(S) ) {
        return ERROR;
    }
    else {
        // 栈顶指向上移
        S.top++;
        // 将元素e赋给栈顶
        S.elem[S.top] = e;
    }

    return OK;
}

// 出栈,返回值为出栈元素
ElemType Pop(SqStack& S) {
    // 判断是否栈空
    if( IsEmpty(S) ) {
        
        return ERROR;
    }
    else {
        // 栈顶指向下移
        S.top--;
        // 返回出栈元素
        return S.elem[S.top + 1];
    }
}


// 遍历栈
void Travese(SqStack S) {
    // 创建新的栈顶指向用来遍历
    int index = S.top;

    // 循环遍历
    while ( index != -1 ) {
        
        cout << S.elem[index] << " ";
        index--;
    }

    cout << endl;
    
    return;
}

// 清空栈
Status ClearStack(SqStack& S) {
    S.top = -1;

    return OK;
}