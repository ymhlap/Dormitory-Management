#include <iostream>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

class Student
{
protected:
    char name[20] = {}; // 姓名
    int ID = 0; // 学号
    char sex = '\0'; // 性别 m_男，f_女
    char grade[20] = {}; // 班级
    short age = 0; // 年龄
public:
    Student() = default;
    Student(char n[20], int id, char ssex, char ggrade[20], short aage)
    {
        strcpy(name, n);
        ID = id;
        sex = ssex;
        strcpy(grade, ggrade);
        age = aage;
    }
    Student(const Student& st);
    void setAge(int age)
    {
        this->age = age;
    }
    void getName(char* n)
    {
        strcpy(n, name);
    }
    int getID()
    {
        return ID;
    }
    char getSex()
    {
        return sex;
    }
    void getGrade(char* g)
    {
        strcpy(g, grade);
    }
    int getAge()
    {
        return age;
    }
    void print()
    {
        cout << "姓名：" << name << endl;
        cout << "学号：" << ID << endl;
        cout << "性别：" << (sex == 'm' ? "男" : (sex == 'f' ? "女" : "")) << endl;
        cout << "班级：" << grade << endl;
        cout << "年龄：" << age << endl;
    }
    Student& operator=(const Student& stu);
};
Student::Student(const Student& st)
{
    strcpy(name, st.name);
    ID = st.ID;
    sex = st.sex;
    strcpy(grade, st.grade);
    age = st.age;
}
Student& Student::operator=(const Student& stu)
{
    if (this != &stu)
    {
        strcpy(name, stu.name);
        ID = stu.ID;
        sex = stu.sex;
        strcpy(grade, stu.grade);
        age = stu.age;
    }
    return *this;
}

class Bed
{
protected:
    Student stu;
    int bedID = 0; // 床位号
    int flag = 0; // 床位是否入住标记，0——空闲，1——已入住
public:
    Bed() = default;
    Bed(int ID) :bedID(ID), flag(0) {}
    Bed(Student stu1, int ID) :stu(stu1), bedID(ID) {}
    void setStudent(Student stu1)
    {
        stu = stu1;
    }
    void setFlag(int f)
    {
        flag = f;
    }
    void setBedID(int ID)
    {
        bedID = ID;
    }
    Student getStudent()
    {
        return stu;
    }
    int getFlag()
    {
        return flag;
    }
    int getBedID()
    {
        return bedID;
    }
    void print()
    {
        cout << "床位号：" << bedID << endl;
        cout << "被占用：" << (flag == 1 ? "Yes" : "No") << endl;
        if (flag == 1) {
            cout << "学生信息：" << endl;
            stu.print();
        }
    }
    Bed& operator=(const Bed& sbed);
};
Bed& Bed::operator=(const Bed& sbed)
{
    if (this != &sbed)
    {
        stu = sbed.stu;
        bedID = sbed.bedID;
        flag = sbed.flag;
    }
    return *this;
}

class Dorm
{
protected:
    int ID = 0; // 房间号
    int number = 0; // 定额人数
    int remains = 0; // 剩余空床位数
    char sex = 'v'; // 房间性别属性, m_男，f_女，初始为v_无性别
    Bed* BedList = nullptr; // 宿舍床位表，规模是number
public:
    Dorm() = default;
    Dorm(int id, int num) :ID(id), number(num), remains(num), sex('v')
    {
        BedList = new Bed[num];
        for (int i = 0; i < num; i++)
        {
            BedList[i].setBedID(i + 1);
        }
    }
    Dorm(const Dorm& d);
    ~Dorm() { delete[] BedList; }
    void setSex(char sex)
    {
        this->sex = sex;
    }
    int getID()
    {
        return ID;
    }
    int getNumber()
    {
        return number;
    }
    int getRemains()
    {
        return remains;
    }
    char getSex()
    {
        return sex;
    }
    bool add(Student& stu)
    {
        if (remains == 0 || (sex != 'v' && sex != stu.getSex()))
        {
            return false;
        }
        for (int i = 0; i < number; i++)
        {
            if (BedList[i].getFlag() == 0)
            {
                BedList[i].setStudent(stu);
                BedList[i].setFlag(1);
                remains--;
                if (sex == 'v')
                {
                    sex = stu.getSex();
                }
                return true;
            }
        }
        return false;
    }
    bool checkOut(int studentID)
    {
        for (int i = 0; i < number; i++)
        {
            if (BedList[i].getFlag() == 1 && BedList[i].getStudent().getID() == studentID)
            {
                BedList[i].setFlag(0);
                remains++;
                if (remains == number)
                {
                    sex = 'v';
                }
                return true;
            }
        }
        return false;
    }
    void print()
    {
        cout << "宿舍号：" << ID << endl;
        cout << "床位的数量：" << number << endl;
        cout << "剩余的床位：" << remains << endl;
        cout << "性别：" << sex << endl;
        for (int i = 0; i < number; i++)
        {
            cout << "床位 " << i + 1 << ":" << endl;
            BedList[i].print();
            cout << endl;
        }
    }
    void print(int j)
    {
        cout << "宿舍 " << getID() << " 床位 " << j + 1 << ":" << endl;
        BedList[j].print();
    }
    int searchID(int id)
    {
        for (int i = 0; i < number; i++)
        {
            if (BedList[i].getFlag() == 1 && BedList[i].getStudent().getID() == id)
            {
                return i;
            }
        }
        return -1;
    }
    Bed& getBed(int index)
    {
        return BedList[index];
    }
    Dorm& operator=(const Dorm& dorm);
    Bed& operator[](int index);
};
Dorm::Dorm(const Dorm& d) : ID(d.ID), number(d.number), remains(d.remains), sex(d.sex)
{
    BedList = new Bed[number];
    for (int i = 0; i < number; i++)
    {
        BedList[i] = d.BedList[i];
    }
}
Dorm& Dorm::operator=(const Dorm& dorm)
{
    if (this != &dorm) {
        ID = dorm.ID;
        number = dorm.number;
        remains = dorm.remains;
        sex = dorm.sex;
        delete[] BedList;
        BedList = new Bed[number];
        for (int i = 0; i < number; i++) {
            BedList[i] = dorm.BedList[i];
        }
    }
    return *this;
}
Bed& Dorm::operator[](int index)
{
    return BedList[index];
}

class collegeDormSet
{
protected:
    Dorm* dormList = nullptr; // 宿舍列表
    int size = 0; // 当前宿舍总数
    int bedNumber = 0; // 总床位数
public:
    collegeDormSet() = default;
    collegeDormSet(int n) :size(n), bedNumber(0)
    {
        dormList = new Dorm[n];
        for (int i = 0; i < n; i++)
        {
            dormList[i] = Dorm(i + 1, 4);
            bedNumber += 4;
        }
    }
    ~collegeDormSet()
    {
        delete[] dormList;
    }
    collegeDormSet(const collegeDormSet& d);
    int getSize()
    {
        return size;
    }
    bool add(Student& stu)
    {
        for (int i = 0; i < size; i++)
        {
            if (dormList[i].add(stu))
            {
                return true;
            }
        }
        return false;
    }
    bool checkOut(int studentID)
    {
        for (int i = 0; i < size; i++)
        {
            if (dormList[i].checkOut(studentID))
            {
                return true;
            }
        }
        return false;
    }
    int getBedNumber()
    {
        return bedNumber;
    }
    int studentTotalNumber()
    {
        int total = 0;
        for (int i = 0; i < size; i++)
        {
            total += dormList[i].getNumber() - dormList[i].getRemains();
        }
        return total;
    }
    int Search(int studentID, int& bed)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < dormList[i].getNumber(); j++)
            {
                if (dormList[i].getBed(j).getFlag() == 1 && dormList[i].getBed(j).getStudent().getID() == studentID)
                {
                    bed = j + 1;
                    return i;
                }
            }
        }
        return -1;
    }
    double occupancy()
    {
        return (double)studentTotalNumber() / bedNumber;
    }
    void print(int d, int bed)
    {
        dormList[d].print(bed - 1);
    }
    void print(int i)
    {
        dormList[i].print();
    }
    void print()
    {
        cout << "全宿舍：" << size << endl;
        cout << "全床位：" << bedNumber << endl;
        cout << "全学生：" << studentTotalNumber() << endl;
        cout << "入住率：" << occupancy() * 100 << "%" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "宿舍 " << i + 1 << ":" << endl;
            dormList[i].print();
            cout << endl;
        }
    }
};
collegeDormSet::collegeDormSet(const collegeDormSet& d) : size(d.size), bedNumber(d.bedNumber)
{
    dormList = new Dorm[size];
    for (int i = 0; i < size; i++)
    {
        dormList[i] = d.dormList[i];
    }
}

void menu()
{
    cout << " 学生宿舍管理 " << endl;
    cout << "               " << endl;
    cout << "=======================" << endl;
    cout << "1. 学生入住" << endl;
    cout << "2. 学生退房" << endl;
    cout << "3. 查询学生住宿" << endl;
    cout << "4. 统计" << endl;
    cout << "5. 输出学校宿舍整体信息" << endl;
    cout << "0. 退出" << endl;
    cout << "=======================" << endl;
}

int main()
{
    collegeDormSet hyit(3);
    Student stu;
    int select;
    while (1)
    {
        menu();
        cout << "请输入选择：";
        cin >> select;
        switch (select)
        {
        case 1:
        {
            char name[20];
            int ID;
            char sex;
            char grade[20];
            short age;
            cout << "请输入入住学生的姓名、学号、性别(m/f)、班级、年龄：" << endl;
            cin >> name >> ID >> sex >> grade >> age;
            stu = Student(name, ID, sex, grade, age);
            if (hyit.add(stu) == true)
            {
                cout << "学生入住成功！" << endl;
            }
            else
            {
                cout << "学生入住失败！" << endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 2:
        {
            int ID;
            cout << "请输入退房学生的学号：";
            cin >> ID;
            if (hyit.checkOut(ID) == true)
            {
                cout << "学生退房成功！" << endl;
            }
            else
            {
                cout << "学生退房失败！" << endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            int ID, d, bed;
            cout << "请输入要查询的学生的学号：";
            cin >> ID;
            d = hyit.Search(ID, bed);
            if (d >= 0)
            {
                cout << "该学生住校！" << endl;
                hyit.print(d, bed);
            }
            else
            {
                cout << "该学生没有住校！" << endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 4:
        {
            cout << "统计结果：" << endl;
            cout << "学校总床位数：" << hyit.getBedNumber() << endl;
            cout << "学校入住率：" << hyit.occupancy() * 100 << "%" << endl;
            system("pause");
            system("cls");
            break;
        }
        case 5:
        {
            cout << "学校宿舍整体信息：" << endl;
            hyit.print();
            system("pause");
            system("cls");
            break;
        }
        case 0:
        {
            return 0;
        }
        }
    }
    return 0;
}