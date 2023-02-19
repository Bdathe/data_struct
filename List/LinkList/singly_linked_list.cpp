// 单链表
#include <iostream>
using std::cout;
using std::endl;

#define OK 1
#define ERROR 0
#define ILLEGAL -1

typedef int ElemType;  // 数据类型
typedef int Status;  // 函数的状态


/*
    链表结点的结构体表示
*/
typedef struct LNode
{
    ElemType data;  // 数据域
    struct LNode* pNext;  // 指针域
}LNODE,* LinkList;  // LODE 等价于 struct LNode 
                    // * LinkList 等价于 struct LNode * LinkList

// 对链表的操作

// 链表的初始化
Status InitLinkList(LinkList& L);
// 判断链表是否为空
bool IsEmpty(LinkList L);
// 销毁单链表
Status DestoryList(LinkList& L);
// 清空单链表
Status ClearList(LinkList& L);
// 链表长度（有效元素个数）
int GetLength(LinkList L);
// 取出单链表中i位置的元素,返回该元素,i从1开始
ElemType GetElem(LinkList L, int i);
// 按值查找，查找链表中该元素是否存在，如果存在返回结点位置 i 
int SeekElemN(LinkList L, ElemType e);
// 按值查找，查找链表中该元素是否存在，如果存在返回结点指针 p 
LNODE* SeekElemP(LinkList L, ElemType e);
// 插入节点,在第i个结点前，插入一个有效值为e的新结点
Status InsertNode(LinkList &L, int i, ElemType e);
// 删除节点,删除第i个结点，并将删除结点的有效值存储在e中
Status DeleteNode(LinkList &L, int i, ElemType &e);
// 头插法建立链表
Status HeadCreat(LinkList &L,ElemType e);
// 尾插法建立链表
Status BackCreat(LinkList &L, ElemType e);
// 单链表的反转 --- 算法1
Status Reverse_1(LinkList& L);  // 链表反转，就是将链表从1->2->3->4->5这种形式反转成5->4->3->2->1这种形式
// 单链表的反转 --- 算法2
Status Reverse_2(LinkList& L);
// 遍历
void Travese(LinkList L);
// 排序 --- 升序
void Sort(LinkList& L);

int main()
{
    // 创建链表
    LinkList L;
    // 初始化
    InitLinkList(L);
    // 尾插
    BackCreat(L,2);
    BackCreat(L,1);
    BackCreat(L,3);
    Travese(L);

    // 插入结点
    InsertNode(L,1,2);
    InsertNode(L,4,3);
    Travese(L);

    Reverse_2(L);
    Travese(L);

    // // 删除结点
    // ElemType e = 0;
    // DeleteNode(L,2,e);
    // Travese(L);
    // cout << "e = " << e << endl;

    // cout << "the value 3 position is : " << SeekElemN(L,3) << endl;
    // cout << "the value 3 position is : " << SeekElemP(L,3) << endl;
    // cout << "Get position 2 elem is : " << GetElem(L,2) << endl; 
    // cout << "The Length is : " << GetLength(L) << endl;
    // cout << "Is Empty : " << IsEmpty(L) << endl;

    return 0;
}


// 函数的实现

// 链表的初始化
Status InitLinkList(LinkList& L) {
    // 创建一个头结点，头结点中没有数据，头指针指向头结点，头结点的指向为空
    LNODE * headPoniter = new LNODE;
    if( headPoniter == NULL ) {
        exit(-1);  // 异常退出
    }
    else {
        headPoniter->pNext = NULL;
        // 将创建的只有头结点的链表赋值给L
        L = headPoniter;
    }

    return OK;
}

// 判断链表是否为空
bool IsEmpty(LinkList L) {
    // 判断头结点的指向是否为空
    if( L->pNext == NULL ) {
        return true;
    }
    else {
        return false;
    }
}


// 销毁单链表
Status DestoryList(LinkList& L) {
    // 结点全部销毁，包括头结点
    LNODE* p = L;  // 保存头指针

    while( p->pNext != NULL ) {
        L = p->pNext;  // 头指针后移
        delete p;  // 释放p所指向的内存
        p = L;
    }

    // 删除最后一个结点
    delete L;
    L = NULL;
    p = NULL;

    return OK;
}


//  清空单链表
Status ClearList(LinkList& L) {
    // 与销毁类似，不过保留头结点
    LNODE* p = L->pNext;
    LNODE* q = NULL;

    while( p->pNext != NULL ) {
        q = p->pNext;
        delete p;
        p = q;
    }

    // 删除最后一个结点
    delete p;
    p = NULL;
    q = NULL;

    L->pNext = NULL;

    return OK;
}

//  链表长度（有效元素个数）
int GetLength(LinkList L) {

    int len = 0;  // 计数
    LNODE* p = L;  // 保存指针

    while( p->pNext != NULL ) {
        
        len++;
        p = p->pNext;
    }

    return len;
}


// 取出单链表中i位置的元素,返回该元素,i从1开始
ElemType GetElem(LinkList L, int i) {
    // 判断i是否合理
    if( i < 1 || i > GetLength(L) ) {
        cout << "取出元素的位置不合理！" << "\n";
        return ILLEGAL;
    }
    else {
        // 定位到i结点
        int j = 0;
        LNODE* p = L;

        while( p->pNext != NULL && j < i ) {
            j++;
            p = p->pNext;
        }

        return p->data;
    }
}

// 按值查找，查找链表中该元素是否存在，如果存在返回结点位置 i 
int SeekElemN(LinkList L, ElemType e) {
    // 遍历
    LNODE* p = L;
    int pos = 0;  // 记录位置
    while( p->pNext != NULL ) {
        p = p->pNext;
        pos++;

        if( p->data == e ) {
            return pos;
        }
    }

    return 0;
}

// 按值查找，查找链表中该元素是否存在，如果存在返回结点指针 p 
LNODE* SeekElemP(LinkList L, ElemType e) {
    // 遍历
    LNODE* p = L;
    while ( p->pNext != NULL ) {
        p = p->pNext;
        
        if( p->data == e ) {
            return p;
        }
    }
    
    return NULL;
}

// 插入节点,在第i个结点前，插入一个有效值为e的新结点
Status InsertNode(LinkList &L, int i, ElemType e) {
    // 判断插入位置是否合理
    if( i < 1 || i > GetLength(L) ) {
        return ERROR;
    }
    else {
        // 定位i结点的前一个结点
        LNODE* p = L;
        int j = 0;

        while( p->pNext != NULL && j < i - 1 ) {
            p = p->pNext;
            j++;
        }

        // 创建新结点并插入新结点
        LNODE* newNode = new LNODE;
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
Status DeleteNode(LinkList &L, int i, ElemType &e) {
    // 判断删除位置是否合理
    if( i < 1 || i > GetLength(L) ) {
        return ERROR;
    }
    else {
        // 定位i结点的前一个结点
        LNODE* p = L;
        int j = 0;

        while( p->pNext != NULL && j < i - 1 ) {
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

//头插法建立链表
Status HeadCreat(LinkList &L,ElemType e) {
    // 创建新结点
    LNODE* newNode = new LNODE;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->data = e;
        newNode->pNext = L->pNext;  // 新结点指向首结点
    }

    // 头结点指向新结点
    L->pNext = newNode;

    return OK;
}

//尾插法建立链表
Status BackCreat(LinkList &L, ElemType e) {
    // 创建新结点
    LNODE* newNode = new LNODE;
    if( newNode == NULL ) {
        exit(-1);
    }
    else {
        newNode->data = e;
        newNode->pNext = NULL;
    }

    // 遍历到尾结点
    LNODE* p = L;
    while( p->pNext != NULL ) {
        p = p->pNext;
    }

    // 尾插
    p->pNext = newNode;

    return OK;
}

// 单链表的反转 --- 算法1
/*
    用头节点插入法新建链表。反转链表，有创建链表的两种方式（头节点插入法，尾节点插入法）知道
    头结点插入法形成的链表是和输入顺序相反的，尾节点插入法形成的链表是和输入顺序相同的，所以
    其中一种方法是，遍历原链表，然后用原链表的输出元素顺序用头结点插入法新建链表，这样新建的
    链表就是反转后的链表。
*/
Status Reverse_1(LinkList& L) {
    // 创建新链表
    LinkList L1;
    InitLinkList(L1);

    // 遍历
    LNODE* p = L->pNext;

    while( p != NULL ) {
        // 头插法重新建立
        HeadCreat(L1,p->data);
        p = p->pNext;
    }

    L = L1;

    return OK;
}


// 单链表的反转 --- 算法2
/*
    就地反转链表。遍历链表，将当前链表的头结点下一个的下一个节点插入到头结点的下一个节点中
    这样就能就地反转了 如1->2->3->4->5先转成2->1->3->4->5，然后在转成3->2->1->4->5这样
    知道最后一个节点就可以就地反转了
*/
Status Reverse_2(LinkList& L) {

    ElemType e = 0;  // 保存删除的节点的有效值
    int i = 2;
    while( i <= GetLength(L) ) {
       DeleteNode(L,i,e);
       InsertNode(L,1,e);
       i++;
    }

    return OK;
}

// 遍历
void Travese(LinkList L) {
    LNODE* p = L->pNext;

    while( p != NULL ) {
        cout << p->data << " ";
        p = p->pNext;
    }
    cout << endl;

    return;
}

// 排序 --- 升序
void Sort(LinkList& L ){
    // 选择排序
    //用指针指向结点表示移动
    LNODE *p, *q;
    int i,j;

    for( i = 0, p = L->pNext; i < GetLength(L) - 1; i++, p = p->pNext )
    {
        //保存最小值的位置
        LNODE * min = p;
        for( j = i + 1, q = p->pNext; j < GetLength(L); j++, q = q->pNext )
        {
            if( min->data > q->data )
            {
                min = q;
            }
        }

        if( min != p )
        {
            ElemType temp = min->data;
            min->data = p->data;
            p->data = temp;
        }
    }

    return;
}