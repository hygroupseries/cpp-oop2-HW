// lab6_complete.cpp
#include <iostream>
#include <stack>
#include <deque>
#include <string>
#include <vector>

using namespace std;

// ========================
// 第一部分：STL 栈的基本操作演示
// ========================
void demonstrateSTLStack() {
    cout << "1. 入栈操作：10 40 30 20 50" << endl;
    stack<int> st;
    int elements[] = {10, 40, 30, 20, 50};
    for (int x : elements) {
        st.push(x);
    }

    cout << "2. 当前栈顶元素：" << st.top() << endl;
    cout << "3. 当前栈大小：" << st.size() << endl;
    cout << "4. 栈是否为空：" << (st.empty() ? "是" : "否") << endl;

    cout << "5. 出栈操作：";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    cout << "6. 栈是否为空：" << (st.empty() ? "是" : "否") << endl;
    cout << "7. 当前栈大小：" << st.size() << endl;
}

// ========================
// 第二部分：自定义栈适配器 MyStack
// ========================
template<typename T, typename Container = deque<T>>
class MyStack {
private:
    Container container;

public:
    // 构造函数
    MyStack() = default;

    // 入栈操作
    void push(const T& value) {
        container.push_back(value);
    }

    // 出栈操作
    void pop() {
        if (!container.empty()) {
            container.pop_back();
        }
    }

    // 访问栈顶元素
    T& top() {
        return container.back();
    }

    const T& top() const {
        return container.back();
    }

    // 判断栈是否为空
    bool empty() const {
        return container.empty();
    }

    // 获取栈的大小
    size_t size() const {
        return container.size();
    }

    // 显示栈内容（用于调试）
    void display() const {
        if (empty()) {
            cout << "空栈" << endl;
            return;
        }
        vector<T> temp;
        Container tempContainer = container;
        while (!tempContainer.empty()) {
            temp.push_back(tempContainer.back());
            tempContainer.pop_back();
        }
        reverse(temp.begin(), temp.end());
        cout << "栈内容（从底到顶）: ";
        for (const auto& x : temp) {
            cout << x << " ";
        }
        cout << endl;
    }
};

// ========================
// 第三部分：浏览器历史记录模拟
// ========================
class BrowserHistory {
private:
    MyStack<string> backStack;     // 后退栈（存储访问路径）
    MyStack<string> forwardStack;  // 前进栈（存储可前进页面）
    string currentPage;            // 当前页面

public:
    // 构造函数，初始化浏览器，设置首页
    BrowserHistory(const string& homepage) {
        currentPage = homepage;
        cout << "初始化浏览器，主页：" << homepage << endl;
    }

    // 访问新页面
    void visit(const string& url) {
        // 将当前页面存入后退栈
        backStack.push(currentPage);

        // 清空前进栈（访问新页面后无法再“前进”到旧分支）
        while (!forwardStack.empty()) {
            forwardStack.pop();
        }

        // 访问新页面
        currentPage = url;
        cout << "访问新页面：" << url << endl;
    }

    // 后退操作
    void back() {
        if (backStack.empty()) {
            cout << "无法后退！" << endl;
            return;
        }

        // 当前页面存入前进栈
        forwardStack.push(currentPage);

        // 从后退栈取出上一页
        currentPage = backStack.top();
        backStack.pop();

        cout << "后退到：" << currentPage << endl;
    }

    // 前进操作
    void forward() {
        if (forwardStack.empty()) {
            cout << "无法前进！" << endl;
            return;
        }

        // 当前页面存入后退栈
        backStack.push(currentPage);

        // 从前进栈取出下一页
        currentPage = forwardStack.top();
        forwardStack.pop();

        cout << "前进到：" << currentPage << endl;
    }

    // 显示当前状态
    void displayStatus() {
        cout << "当前页面：" << currentPage << endl;
        cout << "后退栈大小：" << backStack.size() << endl;
        cout << "前进栈大小：" << forwardStack.size() << endl;
    }
};

// ========================
// 主函数
// ========================
int main() {
    cout << "==================== 演示STL栈的基本操作 ====================" << endl;
    demonstrateSTLStack();

    cout << "\n==================== 浏览器历史记录模拟 ====================" << endl;
    BrowserHistory browser("homepage.com");

    browser.visit("page1.com");
    browser.visit("page2.com");
    browser.visit("page3.com");

    browser.back();
    browser.back();
    browser.forward();
    browser.visit("page4.com");
    browser.back();
    browser.forward();

    browser.displayStatus();

    return 0;
}