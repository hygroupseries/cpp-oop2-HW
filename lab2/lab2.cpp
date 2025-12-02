// lab2_complete.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

// 类模板定义
template<typename T>
class Student {
public:
    Student(string name, string id, string course, T score)
        : m_name(name), m_id(id), m_course(course), m_score(score) {}

    // 获取姓名
    string getName() const { return m_name; }

    // 成绩等级划分
    string setGrade() const {
        if (m_score >= 90) return "优秀";
        else if (m_score >= 80) return "良好";
        else if (m_score >= 70) return "中等";
        else if (m_score >= 60) return "及格";
        else return "不及格";
    }

    // 重载小于运算符（用于排序）
    bool operator<(const Student<T>& other) const {
        return m_score < other.m_score;
    }

    // 友元函数：重载输出运算符
    friend ostream& operator<<(ostream& os, const Student<T>& s);

private:
    string m_name;
    string m_id;
    string m_course;
    T m_score;
};

// 友元函数实现
template<typename T>
ostream& operator<<(ostream& os, const Student<T>& s) {
    os << "Name: " << s.m_name << ", ID: " << s.m_id 
       << ", Course: " << s.m_course << ", Score: " << s.m_score
       << ", Grade: " << s.setGrade();
    return os;
}

// 统计等级人数并输出不及格名单
template<typename T>
void gradeLevelSet(vector<Student<T>>& students) {
    map<string, int> count = {
        {"优秀", 0}, {"良好", 0}, {"中等", 0}, {"及格", 0}, {"不及格", 0}
    };
    vector<string> failList;

    for (const auto& s : students) {
        string grade = s.setGrade();
        count[grade]++;
        if (grade == "不及格") {
            failList.push_back(s.getName());
        }
    }

    // 输出统计结果
    cout << "优秀学生数量:" << count["优秀"] << endl;
    cout << "良好学生数量:" << count["良好"] << endl;
    cout << "中等学生数量:" << count["中等"] << endl;
    cout << "及格学生数量:" << count["及格"] << endl;
    cout << "不及格学生数量:" << count["不及格"] << endl;

    // 输出不及格名单
    cout << "不及格学生名单:" << endl;
    for (size_t i = 0; i < failList.size(); ++i) {
        if (i > 0) cout << " ";
        cout << failList[i];
    }
    cout << endl;
}

int main() {
    vector<Student<float>> students;

    // 添加测试数据（与图片一致）
    students.push_back(Student<float>("xiaomin", "1234", "math", 60.3));
    students.push_back(Student<float>("xiaomin", "1234", "math", 80.5));
    students.push_back(Student<float>("xiaomin", "1235", "math", 70.5));
    students.push_back(Student<float>("xiaomin", "1230", "math", 90.5));
    students.push_back(Student<float>("xiao", "1239", "math", 40.5));
    students.push_back(Student<float>("xiao", "1236", "math", 90.5));
    students.push_back(Student<float>("xi", "1237", "math", 85.5));
    students.push_back(Student<float>("xi", "12300", "math", 65.5));
    students.push_back(Student<float>("aoming", "12323", "math", 52.5));
    students.push_back(Student<float>("ming", "12356", "math", 88.5));

    // 按成绩升序排序
    sort(students.begin(), students.end());

    // 统计并输出
    gradeLevelSet(students);
    cout << "\n学生成绩排序结果：" << endl;
    for (const auto& s : students) {
        cout << s << endl;
    }

    return 0;
}