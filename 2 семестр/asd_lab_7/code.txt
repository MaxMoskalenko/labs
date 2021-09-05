#include <iostream>

#include <ctime>

#include <fstream>

#include <locale.h>

using namespace std;

struct Fakultet
{
    string nazva;
    Fakultet()
    {
        string fuc[5] = {
            "IASA",
            "FIOT",
            "TEF",
            "FMM",
            "FMBI"};

        nazva = fuc[rand() % 5];
    }

    void vivid()
    {
        cout << nazva << endl;
    }
};

struct Student
{
    string surname;
    int age;
    float mark;
    int group;

    Student()
    {
        string surname1[8] = {
            "Sidorov",
            "Pushkin",
            "Onegin",
            "Larina",
            "Stepanov",
            "Korsakov",
            "Ibragimov",
            "Clark"};
        int age1[7] = {
            17,
            18,
            19,
            20,
            21,
            22,
            23};
        float mark1[10] = {
            0.5,
            1,
            1.5,
            2,
            2.5,
            3,
            3.5,
            4,
            4.5,
            5};
        int group1[7] = {
            1,
            2,
            3,
            4,
            5,
            6,
            7};

        surname = surname1[rand() % 8];
        age = age1[rand() % 7];
        mark = mark1[rand() % 10];
        group = group1[rand() % 7];
    }

    void vivod()
    {

        cout
            << " Surname: " << surname << "\t"
            << " Age : " << age << "\t"
            << " Mark: " << mark << "\t"
            << " Group: " << group << "\t" << endl;
    }
};

struct Institut
{
    string name;
    Student student[10];
    Fakultet fakultet[10];
    int numberOfStudents;
    int numberOfFucs;
    Institut() {}                      //конструктор для случая, если пустой Институт
    Institut(int student_n, int fuc_n) //конструктор, если создаем случайные данные
    {
        string names[6] = {
            "KPI",
            "KNU",
            "KBPI",
            "LNU",
            "KhPI",
            "Oxford"};

        name = names[rand() % 6];
        numberOfStudents = student_n; //запоминаем кол-во студентов и факультетов на будущее
        numberOfFucs = fuc_n;

        for (int i = 0; i < student_n; i++)
        {
            student[i] = Student();
        }
        for (int i = 0; i < fuc_n; i++)
        {
            fakultet[i] = Fakultet();
        }
    }

    void vivid()
    { //красивенький вывод :)
        cout << endl
             << "==============================" << endl;
        cout << "Institut name: " << name << endl;
        cout << "---Students---" << endl;
        for (int i = 0; i < numberOfStudents; i++)
        {
            cout << i + 1 << ") ";
            student[i].vivod();
        }
        cout << "---Fakultets---" << endl;
        for (int i = 0; i < numberOfFucs; i++)
        {
            cout << i + 1 << ") ";
            fakultet[i].vivid();
        }
        cout << "==============================" << endl
             << endl;
    }
};

int numOfStruct();

int save()
{
    FILE *fp; //указатель на файл
    int i;    //счетчик

    fp = fopen("f.dat", "ab"); // открываем бинарный файл для записи и чтения в режиме добавления, то есть, если файла нет, то он создастся, а если файл есть, то содержимое файла не будет уничтожено, из файла можно будет читать и в файл можно будет записывать

    int student_n, fuc_n;
    cout << "enter number of students to add: ";
    cin >> student_n;

    cout << "enter numver of fakultets to add: ";
    cin >> fuc_n;

    Institut pack(student_n, fuc_n);
    fwrite(&pack, sizeof(Institut), 1, fp); // записываем в файл fp ровно 1 пакет pack размера institut

    fclose(fp); // закрываем файл
    return 0;
}

void del()
{
    Institut pack;
    FILE *fp, *fp1;
    string name;
    fp = fopen("f.dat", "rb");
    fp1 = fopen("f2.dat", "wb");

    cout << "Enter Institut name to delete: ";
    cin >> name; //спрашиваем имя института

    bool isdelete = false; //чтобы не удалить два с одинаковым именем

    for (int i = 0; i < numOfStruct(); i++)
    {
        fread(&pack, sizeof(Institut), 1, fp);
        if (pack.name == name && !isdelete) //если нашли, то не записываем
        {
            isdelete = true;
        }
        else
        {
            fwrite(&pack, sizeof(Institut), 1, fp1); // записываем в файл_2
        }
    }
    fclose(fp);
    fclose(fp1);

    remove("f.dat"); // удаляем старый и переназываем новый
    rename("f2.dat", "f.dat");
}
void change()
{
    Institut pack;
    FILE *fp, *fp1;
    fp = fopen("f.dat", "rb");
    fp1 = fopen("f2.dat", "wb");
    string name;
    cout << "name of institut where you want change some information: ";
    cin >> name; // спросили имя опять

    for (int i = 0; i < numOfStruct(); i++)
    {
        fread(&pack, sizeof(Institut), 1, fp);
        if (name == pack.name) //если нашли  то начинаем менять
        {
            char choice;
            cout << "Change fakultets or students (f/s):";
            cin >> choice;

            if (choice == 'f') //меняем факультет
            {
                int fuc_n;
                cout << "enter a number of fakultet to change: ";
                cin >> fuc_n;

                string newnazva;
                cout << "enter a new name of fakultet: ";
                cin >> newnazva;

                pack.fakultet[fuc_n - 1].nazva = newnazva;
            }

            else if (choice == 's') //меняем студентов
            {
                int stud_n;
                cout << "enter a number of student to change: ";
                cin >> stud_n;

                string newsurname;
                cout << "enter a new surname: ";
                cin >> newsurname;
                pack.student[stud_n - 1].surname = newsurname;

                int newage;
                cout << "enter a new age: ";
                cin >> newage;
                pack.student[stud_n - 1].age = newage;

                float newmark;
                cout << "enter a new mark: ";
                cin >> newmark;
                pack.student[stud_n - 1].mark = newmark;

                int newgroup;
                cout << "enter a new group: ";
                cin >> newgroup;
                pack.student[stud_n - 1].group = newgroup;
            }
        }
        fwrite(&pack, sizeof(Institut), 1, fp1);
    }

    fclose(fp);
    fclose(fp1);
    remove("f.dat"); // удаляем старый и переназываем новый
    rename("f2.dat", "f.dat");
}

void rightmark()
{
    Institut pack;
    FILE *fp;
    fp = fopen("f.dat", "rb");

    cout << "Students with good marks:" << endl;
    for (int i = 0; i < numOfStruct(); i++)
    {
        fread(&pack, sizeof(Institut), 1, fp);
        for (int i = 0; i < pack.numberOfStudents; i++)
        {
            if (pack.student[i].mark >= 3.5) //выводим только отличников
            {
                pack.student[i].vivod();
            }
        }
    }
    cout << endl;
    fclose(fp);
}

void thebestgroup()
{
    Institut pack;
    FILE *fp;
    fp = fopen("f.dat", "rb");

    int groups[7] = {0};

    for (int i = 0; i < numOfStruct(); i++)
    {
        fread(&pack, sizeof(Institut), 1, fp);
        for (int i = 0; i < pack.numberOfStudents; i++)
        {
            if (pack.student[i].mark >= 3.5) //находим суму всех хороших оценок для каждой из груп
            {
                groups[pack.student[i].group - 1] += pack.student[i].mark;
            }
        }
    }
    fclose(fp);

    int max_indx = 0;
    for (int i = 0; i < 7; i++) //ищем максимальную суму хорошых оценок
    {
        if (groups[max_indx] < groups[i])
        {
            max_indx = i;
        }
    }
    cout << "The best group is " << max_indx + 1 << ". Joke, it`s actually KA-07" << endl; //выводим результат
}

void vyvod()
{
    Institut pack;

    FILE *fp;
    fp = fopen("f.dat", "rb");

    for (int i = 0; i < numOfStruct(); i++)
    {
        fread(&pack, sizeof(Institut), 1, fp);
        pack.vivid();
    }
    fclose(fp);
}

int numOfStruct()
{
    FILE *f = fopen("f.dat", "rb");

    int size = 0;
    if (fseek(f, 0, SEEK_END) == 0)
        size = ftell(f); //получаем размер файла в битах
    fclose(f);
    return size / sizeof(Institut); // делим на размер структуры в битах
}

int main()
{

    srand(time(NULL));
    int choice;
    while (true)
    {
        cout << "Enter 1 to add Institut" << endl;
        cout << "Enter 2 to change data" << endl;
        cout << "Enter 3 to delete data" << endl;
        cout << "Enter 4 to print students with good marks" << endl;
        cout << "Enter 5 to print the best group" << endl;
        cout << "Enter 6 to print all data" << endl;
        cout << "Enter 0 to exit" << endl;
        cout << "You entered: ";
        cin >> choice;
        switch (choice) //запускаем функцию в зависимости от того, что ввел пользователь
        {
        case 1:
            save();
            break;
        case 2:
            change();
            break;
        case 3:
            del();
            break;
        case 4:
            rightmark();
            break;
        case 5:
            thebestgroup();
            break;
        case 6:
            vyvod();
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
}