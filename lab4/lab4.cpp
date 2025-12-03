// lab4_complete.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// 1. Descending 类：用于降序排序
class Descending {
public:
    bool operator()(int a, int b) const {
        return a > b;  // 大于号表示降序
    }
};

// 2. Power 类：用于计算幂（base^exp）
class Power {
public:
    long long operator()(int base, int exp) const {
        if (exp == 0) return 1;
        if (exp < 0) return 0; // 不处理负指数
        long long result = 1;
        for (int i = 0; i < exp; ++i) {
            result *= base;
        }
        return result;
    }
};

// 3. Accumulator 类：用于累加求和
class Accumulator {
private:
    long long sum = 0;
public:
    void operator()(int x) {
        sum += x;
    }

    long long getSum() const {
        return sum;
    }
};

int main() {
    // 测试数据
    vector<int> data = {9, 6, 3, 2, 1};

    // ========== 排序 ==========
    cout << "********************** 排序 **********************" << endl;
    sort(data.begin(), data.end(), Descending{});  // 使用函数对象降序排序
    cout << "排序后的数据为：" << endl;
    for (int x : data) {
        cout << x << " ";
    }
    cout << endl;

    // ========== 计算指数 ==========
    cout << "********************** 计算指数 **********************" << endl;
    Power p;
    cout << "2的3次方=" << p(2, 3) << endl;
    cout << "4的6次方=" << p(4, 6) << endl;
    cout << "9的9次方=" << p(9, 9) << endl;

    // ========== 累加输出 ==========
    cout << "********************** 累加输出 **********************" << endl;
    Accumulator acc;
    acc = for_each(data.begin(), data.end(), acc);  // 使用函数对象累加
    cout << acc.getSum() << endl;

    return 0;
}
