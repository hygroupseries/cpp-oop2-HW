// lab3_complete.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <string>

using namespace std;

// 学生类定义
class Student {
private:
    string id;      // 学号
    string name;    // 姓名
    double score;   // 成绩

public:
    // 构造函数
    Student() : id(""), name(""), score(0.0) {}
    Student(const string& id, const string& name, double score)
        : id(id), name(name), score(score) {}

    // Getter 方法
    string getId() const { return id; }
    string getName() const { return name; }
    double getScore() const { return score; }

    // Setter 方法
    void setId(const string& id) { this->id = id; }
    void setName(const string& name) { this->name = name; }
    void setScore(double score) { this->score = score; }

    // 重载输入运算符（用于从文件读取）
    friend istream& operator>>(istream& is, Student& student) {
        is >> student.id >> student.name >> student.score;
        return is;
    }

    // 重载输出运算符（用于格式化显示）
    friend ostream& operator<<(ostream& os, const Student& student) {
        os << left << setw(12) << student.id
           << setw(15) << student.name
           << setw(8) << fixed << setprecision(2) << student.score;
        return os;
    }

    // 重载比较运算符（按学号排序）
    bool operator<(const Student& other) const {
        return id < other.id;
    }

    // 重载等于运算符（用于查找）
    bool operator==(const Student& other) const {
        return id == other.id;
    }
};

// 学生管理系统类
class StudentManagementSystem {
private:
    vector<Student> students;  // 存储学生信息
    string filename = "students.txt";  // 数据文件名

public:
    // 1. 从文件加载数据（使用输入迭代器）
    void loadFromFile() {
        ifstream fin(filename);
        if (!fin) {
            cout << "错误：无法打开文件 " << filename << endl;
            return;
        }

        // 清空现有数据
        students.clear();

        // 使用输入迭代器读取数据
        copy(istream_iterator<Student>(fin),
             istream_iterator<Student>(),
             back_inserter(students));

        fin.close();
        cout << "数据加载成功！共加载 " << students.size() << " 条记录。\n";
    }

    // 2. 保存数据到文件（使用输出迭代器）
    void saveToFile() {
        ofstream fout(filename);
        if (!fout) {
            cout << "错误：无法创建文件 " << filename << endl;
            return;
        }

        // 使用输出迭代器写入数据
        copy(students.begin(), students.end(),
             ostream_iterator<Student>(fout, "\n"));

        fout.close();
        cout << "数据保存成功！共保存 " << students.size() << " 条记录。\n";
    }

    // 3. 显示所有学生信息（使用只读迭代器）
    void displayAllStudents() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        cout << "\n" << string(40, '=') << "\n";
        cout << "所有学生信息：" << endl;
        cout << string(40, '=') << "\n";
        cout << setw(12) << "学号" << setw(15) << "姓名" << setw(8) << "成绩" << endl;
        cout << string(40, '-') << "\n";

        for (auto it = students.cbegin(); it != students.cend(); ++it) {
            cout << *it << endl;
        }
        cout << string(40, '=') << "\n";
    }

    // 4. 按学号查找并修改成绩（使用随机访问迭代器 + 二分查找）
    void binarySearchById() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        string targetId;
        cout << "请输入要查找的学号：";
        cin >> targetId;

        // 先按学号排序（确保二分查找有效）
        sort(students.begin(), students.end());

        // 二分查找
        auto it = lower_bound(students.begin(), students.end(), Student(targetId, "", 0.0));
        if (it != students.end() && it->getId() == targetId) {
            cout << "\n找到学生信息：" << endl;
            cout << string(40, '=') << "\n";
            cout << setw(12) << "学号" << setw(15) << "姓名" << setw(8) << "成绩" << endl;
            cout << string(40, '-') << "\n";
            cout << *it << endl;
            cout << string(40, '=') << "\n";

            char choice;
            cout << "是否修改成绩？Y 修改，N 返回主菜单：";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                double newScore;
                cout << "请输入新成绩：";
                cin >> newScore;
                it->setScore(newScore);
                cout << "成绩修改成功！\n";
            }
        } else {
            cout << "未找到该学号的学生。\n";
        }
    }

    // 5. 显示不及格学生信息（使用反向迭代器）
    void displayFailedStudents() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        // 按成绩排序（升序），然后反向遍历（降序）
        sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
            return a.getScore() < b.getScore();
        });

        bool hasFailed = false;
        cout << "\n不及格学生信息（按成绩从高到低）：" << endl;
        cout << string(40, '=') << "\n";
        cout << setw(12) << "学号" << setw(15) << "姓名" << setw(8) << "成绩" << endl;
        cout << string(40, '-') << "\n";

        for (auto rit = students.rbegin(); rit != students.rend(); ++rit) {
            if (rit->getScore() < 60.0) {
                cout << *rit << endl;
                hasFailed = true;
            }
        }

        if (!hasFailed) {
            cout << "没有不及格学生。\n";
        }
        cout << string(40, '=') << "\n";
    }

    // 显示菜单
    void showMenu() {
        cout << "\n" << string(40, '=') << "\n";
        cout << "学生成绩管理系统" << endl;
        cout << "1. 从文件加载数据" << endl;
        cout << "2. 显示所有学生信息" << endl;
        cout << "3. 按学号查找修改学生成绩" << endl;
        cout << "4. 显示不及格学生信息" << endl;
        cout << "5. 保存数据到文件" << endl;
        cout << "0. 退出系统" << endl;
        cout << string(40, '=') << "\n";
        cout << "请选择操作：";
    }

    // 运行系统
    void run() {
        int choice;
        do {
            showMenu();
            cin >> choice;

            switch (choice) {
                case 1:
                    loadFromFile();
                    break;
                case 2:
                    displayAllStudents();
                    break;
                case 3:
                    binarySearchById();
                    break;
                case 4:
                    displayFailedStudents();
                    break;
                case 5:
                    saveToFile();
                    break;
                case 0:
                    cout << "感谢使用学生管理系统！" << endl;
                    break;
                default:
                    cout << "无效选择，请重新输入！" << endl;
            }
        } while (choice != 0);
    }
};

// 主函数
int main() {
    StudentManagementSystem system;
    system.run();
    return 0;
}