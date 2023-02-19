#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 255 /* 存储空间初始分配量 */

typedef int Status;		/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;	/* ElemType类型根据实际情况而定，这里假设为int */

/*
    字符串的结构体定义
    方法一：
    typedef struct {
        char ch[MAXSIZE+1];  // '/0'为结束标志
        int length;
    }String;
*/
// 方法二：
typedef char String[MAXSIZE+1];  // 0号位置存储字符串的长度

// 字符串的相关处理
// 初始化字符串,生成一个其值为char *的字符串
Status InitStr(String& S,const char* ch);
// 清空字符串
Status ClearStr(String& S);
// 字符串是否为空
bool IsEmpty(String S);
// 返回字符串长度
int GetLength(String S);
// 由串T复制得串S
Status StrCopy(String& S,String T);
// 遍历输出字符串
void Put(String S);
// 字符串匹配算法 --- BF暴力破解法,返回值为字串T在主串S的第pos个字符的位置，若不存在返回0
int Index_BF(String S, String T);
// 字符串匹配算法 --- KMP
int Index_KMP(String S, String T);
// Next数组的求解
int* GetNext(String T);

int main() 
{
    String S;
    String T;
    InitStr(S,"Hello world!");
    InitStr(T,"world");

    cout << "S:" ;
    Put(S);
    cout << "T:" ;
    Put(T);

    cout << "字符串T出现在字符串S的第" << Index_BF(S,T) << "个位置上" << endl;
    cout << "字符串T出现在字符串S的第" << Index_KMP(S,T) << "个位置上" << endl;

    return 0;
}

// 初始化字符串,生成一个其值为char *的字符串
Status InitStr(String& S,const char* chars) {
    if( strlen(chars) > MAXSIZE ) {  // 初始化的字符串的长度大于最大存储空间
        return ERROR;  
    }
    else {  // 初始化
        S[0] = strlen(chars);  // 存储长度
       
        for( int i = 1; i <= S[0]; i++ ) {
            S[i] = chars[i - 1];
        }
    }

    return OK;
}

// 返回字符串长度
int GetLength(String S) {
    return S[0];
}

// 字符串是否为空
bool IsEmpty(String S) {
    if( S[0] == 0 ) {
        return true;
    }
    else {
        return false;
    }
}

// 由串T复制得串S
Status StrCopy(String& S,String T) {
    S[0] = T[0];

    for( int i = 1; i <= T[0]; i++ ) {
        S[i] = T[i];
    }

    return OK;
}

// 遍历输出字符串
void Put(String S) {
    for( int i = 1; i <= S[0]; i++ ) {
        cout << S[i];
    }

    cout << endl;

    return;
}

// 字符串匹配算法 --- BF暴力破解法
int Index_BF(String S, String T) {
    int i = 1;  // i存储S字符串的下标位置
    int j = 1;  // j存储T字符串的下标位置

    while( i <= S[0] && j <= T[0] ) {  // 当i小于S的长度而且j小于T的长度，循环继续

        if( S[i] == T[j] ) {  // 相等继续向后匹配
            i++;
            j++;
        }
        else {

            i = i - j + 2;  // i退回到上次匹配首位的下一位
            j = 1;  // j退回到字串T的首位
        }
    }

    if( j > T[0] )  // 说明匹配成功
        return i - T[0];
    else
        return 0;

}

// 字符串匹配算法 --- KMP
int Index_KMP(String S, String T) {
    int i = 1;  // i记录主串下标位置
    int j = 1;  // j记录字串下标位置

    // 求next数组
    int* next = GetNext(T);

    while( i <= S[0] && j <= T[0] ) {  // 当i小于S的长度而且j小于T的长度，循环继续

        if( j == 0 || S[i] == T[j] ) {  // 相等继续向后匹配,与朴素算法增加了j=0判断, j == 0 表示j已经在最左边了，不可能再移动了，这时候要应该是i指针后移，i++，i后移，j++，j==1，还在最左边
            i++;
            j++;
        }                      // abacmm
                               // abad
        else {
            // i不需要回溯
            j = next[j];  // j回溯
        }
    }

    if (j > T[0]) 
		return i-T[0];
	else 
		return 0;
}

// next数组的求解  next[j]的值 = 第j位字符前面的j-1位字符组成的字符串前后缀重合字符数+1  +1的原因是本代码中字符串的下标从1开始
int* GetNext(String T) {
    int* next = new int[T[0]];  // 创建next数组，长度为模式串长度

    next[1] = 0;
    int i = 1;  // 主串正在匹配的字符位置，也是next数组的索引
    int j = 0;  // 回溯

    while( i < T[0] ) {
        if( j ==0 || T[i] == T[j] ) {  // j == 0代表没有重合，字串回到0+1=1位置  
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }

    return next;
}