#include <iostream>
#include <algorithm>
#include <vector>
using std::for_each;
using std::vector;
using std::cout;
using std::endl;

//打印函数
void My_Print(int val);
//打印仿函数 --- 仿函数必须是成员函数
class MyPrint
{
public:
    void operator()(int val)  // 重载小括号
    {
        cout << val << " ";
    }

};

// 排序算法

// 冒泡排序 --- 升序
void BubbleSort(vector<int>& v);
// 选择排序 --- 升序
void SelectSort(vector<int>& v);
// 插入排序 --- 升序
void InsertSort(vector<int>& v);

int main()
{
    vector<int> v;
    v.push_back(2);
    v.push_back(0);
    v.push_back(3);
    // BubbleSort(v);
    // SelectSort(v);
    InsertSort(v);

    for_each(v.begin(), v.end(), MyPrint());
    cout << endl;
    for_each(v.begin(), v.end(), My_Print);

    return 0;
}

// 打印函数
void My_Print(int val)
{
    cout << val << " ";
    return;
}


// 冒泡排序 --- 升序
/*
    1、比较相邻的元素。如果第一个比第二个大，就交换它们两个；
    2、对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对，这样在最后的元素应该会是最大的数；
    3、针对所有的元素重复以上的步骤，除了最后一个；
       重复步骤1~3，直到排序完成。
*/
void BubbleSort(vector<int>& v) {
    for( int i = 0; i < v.size() - 1; i++ ) {  // i < v.size() - 1 ： 需要比较元素数量-1轮，因为最后的元素一定是最小的，不需要进行比较
        for( int j = 0; j < v.size() - i - 1; j++ ) {  // j < v.size() - i - 1 ： 每一轮需要减去之前排好序的，不需要进行比较
            if( v[j] > v[j + 1] ) {  // 升序
                // 交换
                int temp = v[j + 1];
                v[j + 1] = v[j];
                v[j] = temp;
            }
        }
    }

    return;
}



// 选择排序 --- 升序
/*
    1、在未排序序列中找到最小（大）元素，存放到排序序列的起始位置
    2、从剩余未排序元素中继续寻找最小（大）元素，然后放到已排序序列的末尾。
       重复第二步，直到所有元素均排序完毕。
*/
void SelectSort(vector<int>& v) {
    int min;  // 存储遍历到的最小值的下标
    for( int i = 0; i < v.size() - 1; i++ ) {
        min = i;  // 初始默认最小值下标为 i
        for( int j = i; j < v.size(); j++ ) {
            if( v[min] > v[j] ) {
                // 变更最小值下标
                min = j;
            }
        }

        // 检查最小值下标是否变更
        if( min != i ) {
            // 交换
            int temp = v[min];
            v[min] = v[i];
            v[i] = temp;
        }
    }

    return;
}

// 插入排序 --- 升序
/*
    1、把待排序的数组分成已排序和未排序两部分，初始的时候把第一个元素认为是已排好序的。
    2、从第二个元素开始，在已排好序的子数组中寻找到该元素合适的位置并插入该位置。
       重复上述过程直到最后一个元素被插入有序子数组中。
*/
void InsertSort(vector<int>& v) {
    int val = 0;
    int position = 0;

    for( int i = 0; i < v.size() - 1; i++ ) {
        val = v[i];
        position = i;

        while( position > 0 && v[position - 1] > val ) {
            // 插入
            v[position] = v[position - 1];
            position--;
        }

        v[position] = val;
    }

    return;
}