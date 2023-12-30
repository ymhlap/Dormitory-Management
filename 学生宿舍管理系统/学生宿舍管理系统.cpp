#include <iostream>
#include <cstring>
#pragma warning(disable:4996)
using namespace std;

class Student
{
protected:
    char name[20] = {}; // ����
    int ID = 0; // ѧ��
    char sex = '\0'; // �Ա� m_�У�f_Ů
    char grade[20] = {}; // �༶
    short age = 0; // ����
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
        cout << "������" << name << endl;
        cout << "ѧ�ţ�" << ID << endl;
        cout << "�Ա�" << (sex == 'm' ? "��" : (sex == 'f' ? "Ů" : "")) << endl;
        cout << "�༶��" << grade << endl;
        cout << "���䣺" << age << endl;
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
    int bedID = 0; // ��λ��
    int flag = 0; // ��λ�Ƿ���ס��ǣ�0�������У�1��������ס
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
        cout << "��λ�ţ�" << bedID << endl;
        cout << "��ռ�ã�" << (flag == 1 ? "Yes" : "No") << endl;
        if (flag == 1) {
            cout << "ѧ����Ϣ��" << endl;
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
    int ID = 0; // �����
    int number = 0; // ��������
    int remains = 0; // ʣ��մ�λ��
    char sex = 'v'; // �����Ա�����, m_�У�f_Ů����ʼΪv_���Ա�
    Bed* BedList = nullptr; // ���ᴲλ����ģ��number
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
        cout << "����ţ�" << ID << endl;
        cout << "��λ��������" << number << endl;
        cout << "ʣ��Ĵ�λ��" << remains << endl;
        cout << "�Ա�" << sex << endl;
        for (int i = 0; i < number; i++)
        {
            cout << "��λ " << i + 1 << ":" << endl;
            BedList[i].print();
            cout << endl;
        }
    }
    void print(int j)
    {
        cout << "���� " << getID() << " ��λ " << j + 1 << ":" << endl;
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
    Dorm* dormList = nullptr; // �����б�
    int size = 0; // ��ǰ��������
    int bedNumber = 0; // �ܴ�λ��
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
        cout << "ȫ���᣺" << size << endl;
        cout << "ȫ��λ��" << bedNumber << endl;
        cout << "ȫѧ����" << studentTotalNumber() << endl;
        cout << "��ס�ʣ�" << occupancy() * 100 << "%" << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "���� " << i + 1 << ":" << endl;
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
    cout << " ѧ��������� " << endl;
    cout << "               " << endl;
    cout << "=======================" << endl;
    cout << "1. ѧ����ס" << endl;
    cout << "2. ѧ���˷�" << endl;
    cout << "3. ��ѯѧ��ס��" << endl;
    cout << "4. ͳ��" << endl;
    cout << "5. ���ѧУ����������Ϣ" << endl;
    cout << "0. �˳�" << endl;
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
        cout << "������ѡ��";
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
            cout << "��������סѧ����������ѧ�š��Ա�(m/f)���༶�����䣺" << endl;
            cin >> name >> ID >> sex >> grade >> age;
            stu = Student(name, ID, sex, grade, age);
            if (hyit.add(stu) == true)
            {
                cout << "ѧ����ס�ɹ���" << endl;
            }
            else
            {
                cout << "ѧ����סʧ�ܣ�" << endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 2:
        {
            int ID;
            cout << "�������˷�ѧ����ѧ�ţ�";
            cin >> ID;
            if (hyit.checkOut(ID) == true)
            {
                cout << "ѧ���˷��ɹ���" << endl;
            }
            else
            {
                cout << "ѧ���˷�ʧ�ܣ�" << endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 3:
        {
            int ID, d, bed;
            cout << "������Ҫ��ѯ��ѧ����ѧ�ţ�";
            cin >> ID;
            d = hyit.Search(ID, bed);
            if (d >= 0)
            {
                cout << "��ѧ��סУ��" << endl;
                hyit.print(d, bed);
            }
            else
            {
                cout << "��ѧ��û��סУ��" << endl;
            }
            system("pause");
            system("cls");
            break;
        }
        case 4:
        {
            cout << "ͳ�ƽ����" << endl;
            cout << "ѧУ�ܴ�λ����" << hyit.getBedNumber() << endl;
            cout << "ѧУ��ס�ʣ�" << hyit.occupancy() * 100 << "%" << endl;
            system("pause");
            system("cls");
            break;
        }
        case 5:
        {
            cout << "ѧУ����������Ϣ��" << endl;
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