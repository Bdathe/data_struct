// 递归的应用
#include <iostream>

// 阶乘n!
int Factorial(int n);
// 斐波那契数列求值f(n)=f(n-1)+f(n-2)
int FibonacciSequence(int n);
// 递归实现全排列 --- 未实现
int Perm();

int main()
{
    std::cout << "阶乘：" << Factorial(10) << std::endl;
    std::cout << "斐波那契数列：" << FibonacciSequence(0) << std::endl;
    return 0;
}

// 阶乘n!
int Factorial(int n) {
    if( n == 0 ) {
        return 1;
    }
    else {
        return n * Factorial(n-1);
    }
}

// 斐波那契数列求值f(n)=f(n-1)+f(n-2)
int FibonacciSequence(int n) {
    if( n == 0 ) {
        return 0;
    }
    else if( n == 1 ) {
        return 1;
    }
    else {
        return FibonacciSequence(n-1) + FibonacciSequence(n-2);
    }
}
