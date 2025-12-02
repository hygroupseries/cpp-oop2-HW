// lab5_complete.cpp
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
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
    map<string, Student> students;  // 使用 map 存储学生，key 为学号
    string filename = "students.txt";  // 数据文件名

public:
    // 1. 从文件加载数据到 map
    void loadFromFile() {
        ifstream fin(filename);
        if (!fin) {
            cout << "错误：无法打开文件 " << filename << endl;
            return;
        }

        // 清除现有数据
        students.clear();

        // 读取数据并存入 map
        string line;
        while (fin >> line) {
            Student s;
            stringstream ss(line);
            ss >> s.id >> s.name >> s.score;
            students[s.id] = s;
        }

        fin.close();
        cout << "数据加载成功！共加载 " << students.size() << " 条记录。\n";
    }

    // 2. 将 map 中的数据写入文件
    void saveToFile() {
        ofstream fout(filename);
        if (!fout) {
            cout << "错误：无法创建文件 " << filename << endl;
            return;
        }

        // 遍历 map 并将学生信息写入文件
        for (const auto& pair : students) {
            fout << pair.second.getId() << " " << pair.second.getName() << " " << pair.second.getScore() << endl;
        }

        fout.close();
        cout << "数据保存成功！共保存 " << students.size() << " 条记录。\n";
    }

    // 3. 显示所有学生信息（遍历 map）
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

        for (const auto& pair : students) {
            cout << pair.second << endl;
        }
        cout << string(40, '=') << "\n";
    }

    // 4. 在 map 中按学号查找并修改学生成绩
    void findAndModifyStudent() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        string targetId;
        cout << "请输入要查找的学号：";
        cin >> targetId;

        // 使用 map 的 find 方法查找学生
        auto it = students.find(targetId);
        if (it != students.end()) {
            cout << "\n找到学生信息：" << endl;
            cout << string(40, '=') << "\n";
            cout << setw(12) << "学号" << setw(15) << "姓名" << setw(8) << "成绩" << endl;
            cout << string(40, '-') << "\n";
            cout << it->second << endl;
            cout << string(40, '=') << "\n";

            char choice;
            cout << "是否修改成绩？Y 修改，N 返回主菜单：";
            cin >> choice;

            if (choice == 'Y' || choice == 'y') {
                double newScore;
                cout << "请输入新成绩：";
                cin >> newScore;
                it->second.setScore(newScore);
                cout << "成绩修改成功！\n";
            }
        } else {
            cout << "未找到该学号的学生。\n";
        }
    }

    // 5. 使用 set 存储并打印不及格学生名单
    void displayFailedStudents() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        // 创建 set 存储不及格学生（自动去重 + 排序）
        set<Student> failedSet;

        // 遍历 map，将不及格学生添加到 set 中
        for (const auto& pair : students) {
            if (pair.second.getScore() < 60.0) {
                failedSet.insert(pair.second);
            }
        }

        // 输出表头
        cout << "\n不及格学生信息（按成绩从高到低）：" << endl;
        cout << string(40, '=') << "\n";
        cout << setw(12) << "学号" << setw(15) << "姓名" << setw(8) << "成绩" << endl;
        cout << string(40, '-') << "\n";

        // 遍历 set 显示不及格学生
        for (const auto& s : failedSet) {
            cout << s << endl;
        }

        if (failedSet.empty()) {
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
                    findAndModifyStudent();
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