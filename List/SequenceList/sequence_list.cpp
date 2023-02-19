// 顺序表
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
    顺序表的结构体表示
*/
typedef struct {
    ElemType* elem;  // 动态数组
    int length;  // 顺序表的有效长度
}SqList;

// 对顺序表的相关操作

// 顺序表初始化,建立一个空表L
Status InitSqlist(SqList& L);
// 销毁线性表
Status DestorySqlist(SqList& L);
// 清空线性表
Status ClearSqlist(SqList& L);
// 判断表是否为空
bool IsEmpty(SqList L);
// 判断表是否满
bool IsFull(SqList L);
//返回线性表的元素个数
int Getlength(SqList L);
// 在表的第i个位置插入新元素e,i从1开始
Status InsertElem(SqList& L, int i, ElemType e);
// 尾插
Status PushBack(SqList& L,ElemType e);
// 删除线性表中的第i个位置的元素，并用e返回
Status DeleteElem(SqList &L, int i, ElemType &e);
//L中查找与给定值e相等的元素，若成功返回元素在表中的序号（表中的第一个序号为1），否则返回0
int SeekElem(SqList L, ElemType e);
//将线性表的第i个位置元素返回
ElemType GetElem(SqList L, int i);
//遍历
void Travese(SqList L);
// 排序 --- 升序
void Sort(SqList& L);
// 有序表的合并 --- 已知线性表La和Lb中的数据元素按值非递减有序排列，将La和Lb归并成一个新的线性表Lc，且Lc中的元素仍按值非递减排列
void MeregeList(SqList La, SqList Lb, SqList& Lc);
// 线性表的合并 --- La = La ∪ Lb
void Union(SqList& La ,SqList Lb);

int main()
{
    // 创建顺序表
    SqList L;
    SqList L1;
    SqList L2;
    // 初始化
    InitSqlist(L);
    InitSqlist(L1);
    InitSqlist(L2);
    // 插入元素
    InsertElem(L,1,5);
    InsertElem(L,2,6);
    InsertElem(L,3,1);
    InsertElem(L1,1,9);
    InsertElem(L1,2,6);
    InsertElem(L1,3,0);
   
    Union(L,L1);
    Travese(L);

    return 0;
}

// 顺序表初始化,建立一个空表L
Status InitSqlist(SqList& L) {
    // 构造数组
    L.elem = new ElemType[MAXSIZE];
    if( L.elem == NULL ) {
        exit(-1);
    }
    else {
        // 有效长度为0
        L.length = 0;
    }

    return OK;
}

// 销毁线性表
Status DestorySqlist(SqList& L) {
    // 释放分配的数组的空间
    delete []L.elem;
    // 有效长度置为0
    L.length = 0;

    return OK;
}

// 清空线性表
Status ClearSqlist(SqList& L) {
    // 长度置为0
    L.length = 0;

    return OK;
}

// 判断表是否为空
bool IsEmpty(SqList L) {
    if( L.length == 0 ) {
        return true;
    }
    else {
        return false;
    }
}


// 判断表是否满
bool IsFull(SqList L) {
    if( L.length == MAXSIZE ) {
        return true;
    }
    else {
        return false;
    }
}

//返回线性表的元素个数
int Getlength(SqList L) {
    return L.length;
}


// 在表的第i个位置插入新元素e,i从1开始
Status InsertElem(SqList& L, int i, ElemType e) {
    // 检查表是否满，满了不能插入
    if( IsFull(L) ) {
        return ILLEGAL;
    }
    // 检查插入位置i是否合理
    else if( i < 1 || i > L.length + 1 ) { 
        return ILLEGAL;
    }
    // 插入
    else {
        // 移动 i 位置和 i 位置之后的元素，腾出位置 i
        // 切记序号从1开始，下标从0开始
        int index = L.length - 1;
        while( index >= i - 1 ) {  // 位置 i 的下标为 i - 1 
            L.elem[index + 1] = L.elem[index];
            index--;
        }

        // 插入
        L.elem[i - 1] = e;

        // 有效长度加1
        L.length++;

        return OK;
    }
}

// 尾插
Status PushBack(SqList& L,ElemType e) {
     // 检查表是否满，满了不能插入
    if( IsFull(L) ) {
        return ILLEGAL;
    }

    L.elem[L.length] = e;
    L.length++;

    return OK;
}

// 删除线性表中的第i个位置的元素，并用e返回
Status DeleteElem(SqList &L, int i, ElemType &e) {
    // 判断表是否为空
    if( IsEmpty(L) ) {
        return ILLEGAL;
    }
    // 判断删除位置是否合理
    else if(i < 1 || i > L.length) {
        return ILLEGAL;
    }
    // 删除
    else {
        // 保存i位置的元素
        e = L.elem[i - 1];
        // 覆盖删除
        int index = i - 1;
        while( index < L.length - 1 ) {
            L.elem[index] = L.elem[index + 1];
            index++;
        }

        // 有效长度-1
        L.length--;

        return OK;
    }
}

//L中查找与给定值e相等的元素，若成功返回元素在表中的序号（表中的第一个序号为1），否则返回0
int SeekElem(SqList L, ElemType e) {
    // 表是否为空
    if( IsEmpty(L) ) {
        return ERROR;
    }
    else {
        // 遍历
        for(int i = 0; i < L.length - 1; i++) {
            if( L.elem[i] == e ) {
                return i + 1;
            }
        }
    }

    return ERROR;
}

//将线性表的第i个位置元素返回
ElemType GetElem(SqList L, int i) {
    // 判断表是否空
    if( IsEmpty(L) ) {
        return ILLEGAL;
    }
    // 判断i是否合法
    else if( i < 1 || i > L.length ) {
        return ILLEGAL;
    }
    else {
        // 返回
        return L.elem[i-1];
    }

    return ILLEGAL;
}

//遍历
void Travese(SqList L) {
    for( int i = 0; i < L.length; i++ ) {
        cout << L.elem[i] << " ";
    }

    cout << endl;

    return;
}

// 排序 --- 升序
void Sort(SqList& L) {
    // 选择排序
    int min = 0;  // 存储最小值下标

    for( int i = 0; i < L.length - 1; i++ ) {
        min = i;

        for( int j = i; j < L.length; j++ ) {
            if( L.elem[min] > L.elem[j] ) {
                min = j;
            }
        }

        if( min != i ) {
            // 交换
            ElemType temp = L.elem[min];
            L.elem[min] = L.elem[i];
            L.elem[i] = temp;
        }
    }

    return;
}

// 有序表的合并 --- 已知线性表La和Lb中的数据元素按值非递减有序排列，将La和Lb归并成一个新的线性表Lc，且Lc中的元素仍按值非递减排列
/*
    1、创建一个空表Lc
    2、将La和Lb排序变成有序表，依次从La或Lb中摘取元素值较小的结点插入到Lc表的最后，直至一个表为空为止
    3、继续将La或Lb其中一个表的剩余结点插在Lc的最后
*/
void MeregeList(SqList La, SqList Lb, SqList& Lc) {
    // 将La和Lb变成有序表
    Sort(La);
    Sort(Lb);
    
    // 新表长度为待合并两表长度之和
    Lc.length = La.length + Lb.length;
    Lc.elem = new ElemType[Lc.length];  // 分配空间

    // pa、pb、pc分别指向La，Lb，Lc的第一个元素 ， paLast和pbLast分别指向La、Lb的最后一个元素
    ElemType* pa = La.elem;
    ElemType* pb = Lb.elem;
    ElemType* pc = Lc.elem;
    ElemType* paLast = La.elem + La.length - 1;
    ElemType* pbLast = Lb.elem + Lb.length - 1;

    // 遍历La和Lb摘取较小的元素
    while( pa <= paLast && pb <= pbLast ) {  // 两表都非空
        if( *pa <= *pb ) {
            // 将*pa插入表Lc
            *pc = *pa;
            pc++;
            pa++;
        }
        else {
            // 将*pb插入表Lc
            *pc = *pb;
            pc++;
            pb++;
        }
    }

    while( pa <= paLast ) {  // Lb表到达表尾,将La中的剩余元素插入Lc
        *pc = *pa;
        pc++;
        pa++;
    }

    while( pb <= pbLast ) {  // La表到达表尾,将ba中的剩余元素插入Lc
        *pc = *pb;
        pc++;
        pb++;
    }

    return;
}


// 线性表的合并 --- La = La ∪ Lb
/*
    依次取出Lb中的每个元素，执行以下操作：
    1、在La中查找该元素
    2、如果找不到，将其插入到La后
*/
void Union(SqList& La ,SqList Lb) {
    // 遍历Lb
    int Lb_Len = Lb.length;
    ElemType e = 0;
    for( int i = 1; i <= Lb_Len; i++ ) {
        // 在La中查找该元素
        e = GetElem(Lb,i);
        if( SeekElem(La,e) == 0 ) {
            // 没查到
            // 尾插
            InsertElem(La,La.length + 1, e);
        }
    }

    return;
}