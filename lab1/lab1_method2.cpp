// lab1_method2.cpp
#include <iostream>
using namespace std;

// 主模板：定义类型别名
template<typename T>
struct CreditTraits {
    typedef float CreditType;
    static constexpr float factor = 4.0f;
};

// Student 特化
template<>
struct CreditTraits<Student> {
    typedef float CreditType;
    static constexpr float factor = 4.0f;
};

// Teacher 特化
template<>
struct CreditTraits<Teacher> {
    typedef int CreditType;
    static constexpr int factor = 3;
};

// 类定义
class Student {};
class Teacher {};

// 函数模板：使用 typename 和 :: 访问类型
template<typename T>
typename CreditTraits<T>::CreditType calculateCredits(int hour) {
    return CreditTraits<T>::factor * hour;
}

int main() {
    int hour;
    cout << "请输入小时数: ";
    cin >> hour;

    cout << "Student credits: " << calculateCredits<Student>(hour) << endl;
    cout << "Teacher credits: " << calculateCredits<Teacher>(hour) << endl;

    return 0;
}