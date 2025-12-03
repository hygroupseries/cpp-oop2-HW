#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

// ------------------------- Student 类 -------------------------
class Student {
private:
    string id;
    string name;
    double score;

public:
    Student() : id(""), name(""), score(0) {}
    Student(const string& id, const string& name, double score)
        : id(id), name(name), score(score) {}

    // getters
    string getId() const { return id; }
    string getName() const { return name; }
    double getScore() const { return score; }

    // setters
    void setId(const string& id) { this->id = id; }
    void setName(const string& name) { this->name = name; }
    void setScore(double score) { this->score = score; }

    // operator>>
    friend istream& operator>>(istream& is, Student& s) {
        is >> s.id >> s.name >> s.score;
        return is;
    }

    // operator<<
    friend ostream& operator<<(ostream& os, const Student& s) {
        os << left << setw(12) << s.id
           << setw(15) << s.name
           << setw(8) << fixed << setprecision(2) << s.score;
        return os;
    }

    // 排序用：按成绩从高到低排（用于不及格学生）
    bool operator<(const Student& other) const {
        return score > other.score;  // 高分排前面
    }
};

// ------------------------- 学生管理系统 -------------------------
class StudentManagementSystem {
private:
    map<string, Student> students;
    string filename = "students.txt";

public:

    // ========== 1. 从文件加载 ==========
    void loadFromFile() {
        ifstream fin(filename);
        if (!fin) {
            cout << "错误：无法打开文件 " << filename << endl;
            return;
        }

        students.clear();

        Student s;
        while (fin >> s) {  // 使用 operator>>
            students[s.getId()] = s;
        }

        fin.close();
        cout << "数据加载成功！共加载 " << students.size() << " 条记录。\n";
    }

    // ========== 2. 保存到文件 ==========
    void saveToFile() {
        ofstream fout(filename);
        if (!fout) {
            cout << "错误：无法创建文件 " << filename << endl;
            return;
        }

        for (auto& p : students) {
            fout << p.second.getId() << " "
                 << p.second.getName() << " "
                 << p.second.getScore() << endl;
        }

        fout.close();
        cout << "数据保存成功！共保存 " << students.size() << " 条记录。\n";
    }

    // ========== 3. 显示所有学生 ==========
    void displayAllStudents() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        cout << "\n" << string(40, '=') << "\n";
        cout << "学号          姓名           成绩\n";
        cout << string(40, '-') << "\n";

        for (auto& p : students) {
            cout << p.second << endl;
        }

        cout << string(40, '=') << "\n";
    }

    // ========== 4. 查找并修改 ==========
    void findAndModifyStudent() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        string id;
        cout << "请输入学号：";
        cin >> id;

        auto it = students.find(id);
        if (it == students.end()) {
            cout << "未找到该学生。\n";
            return;
        }

        cout << "\n找到学生信息：\n";
        cout << it->second << endl;

        cout << "是否修改成绩？(Y/N): ";
        char c;
        cin >> c;
        if (c == 'Y' || c == 'y') {
            double newScore;
            cout << "新成绩：";
            cin >> newScore;
            it->second.setScore(newScore);
            cout << "修改成功！\n";
        }
    }

    // ========== 5. 不及格学生 ==========
    void displayFailedStudents() {
        if (students.empty()) {
            cout << "暂无学生信息。\n";
            return;
        }

        set<Student> failed;

        for (auto& p : students) {
            if (p.second.getScore() < 60)
                failed.insert(p.second);
        }

        cout << "\n不及格学生（成绩高→低）：\n";
        cout << string(40, '-') << "\n";

        for (auto& s : failed) {
            cout << s << endl;
        }

        if (failed.empty())
            cout << "无不及格学生。\n";

        cout << string(40, '=') << "\n";
    }

    // ========== 菜单 ==========
    void showMenu() {
        cout << "\n"
             << "1. 从文件加载数据\n"
             << "2. 显示所有学生\n"
             << "3. 查找并修改成绩\n"
             << "4. 显示不及格学生\n"
             << "5. 保存数据\n"
             << "0. 退出\n"
             << "请输入选项：";
    }

    void run() {
        int choice;
        do {
            showMenu();
            cin >> choice;
            switch (choice) {
                case 1: loadFromFile(); break;
                case 2: displayAllStudents(); break;
                case 3: findAndModifyStudent(); break;
                case 4: displayFailedStudents(); break;
                case 5: saveToFile(); break;
                case 0: cout << "退出系统。\n"; break;
                default: cout << "无效输入！\n";
            }
        } while (choice != 0);
    }
};

// ------------------------- main -------------------------
int main() {
    StudentManagementSystem sys;
    sys.run();
    return 0;
}

