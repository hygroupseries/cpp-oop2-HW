// lab1_method1.cpp
#include <iostream>
using namespace std;

// 先声明类，保证后面模板特化能找到类型
class Student;
class Teacher;

// 主模板：默认行为（可省略，仅用于占位）
template<typename T>
struct CreditTraits {
    using CreditType = float;  // 默认返回 float
    static constexpr float factor = 4.0f;
};

// Student 特化：学生用 float 返回，系数为 4
template<>
struct CreditTraits<Student> {
    using CreditType = float;
    static constexpr float factor = 4.0f;
};

// Teacher 特化：老师用 int 返回，系数为 3
template<>
struct CreditTraits<Teacher> {
    using CreditType = int;
    static constexpr int factor = 3;
};

// 再给出完整定义（如果需要）
class Student {};
class Teacher {};

// 模板函数：利用 traits 获取类型信息
template<typename User>
typename CreditTraits<User>::CreditType calculateCredits(int hour) {
    return CreditTraits<User>::factor * hour;
}

int main() {
    int hour;
    cout << "请输入小时数: ";
    cin >> hour;

    cout << "Student credits: " << calculateCredits<Student>(hour) << endl;
    cout << "Teacher credits: " << calculateCredits<Teacher>(hour) << endl;

    return 0;
}

