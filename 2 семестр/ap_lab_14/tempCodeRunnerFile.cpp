#include <iostream>

#include <ctime>

#include <fstream>

// #include <locale.h>

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

    cout
        << "========================================================================"
        << "\n"
        << " FAKULTET: " << nazva << "\t" << endl;
  }
};

struct Student
{
  string surname;
  int age;
  char mark;
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
    char mark1[5] = {
        'A',
        'B',
        'C',
        'D',
        'E'};
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
    mark = mark1[rand() % 5];
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

  Student *student = new Student[10];
  Fakultet *fakultet = new Fakultet[10];

  Institut()
  {
    for (int i = 0; i < 10; i++)
    {
      fakultet[i] = Fakultet();
      student[i] = Student();
    }
  }

  void vivid()
  {
    for (int i = 0; i < 10; i++)
    {
      fakultet[i].vivid();
      student[i].vivod();
    }
  }
};

// int proverka(FILE *fp)
// {
//   if (fp == NULL)
//   {
//     cout << "Error opening file";
//     return 0;
//   }
// }

int save()
{
  FILE *fp; //указатель на файл
  int i;    //счетчик

  fp = fopen(".\\alc.dat", "a+b"); // открываем бинарный файл для записи и чтения в режиме добавления, то есть, если файла нет, то он создастся, а если файл есть, то содержимое файла не будет уничтожено, из файла можно будет читать и в файл можно будет записывать

  for (i = 0; i < 4; i++)
  {
    Institut pack;
    fwrite(&pack, sizeof(Institut), 1, fp); // записываем в файл fp ровно 1 пакет pack размера institut
  }
  fclose(fp); // закрываем файл
  return 0;
}

void vivid(Institut pack)
{
  cout << pack.student << pack.fakultet << endl;
}

void del()
{
  Institut pack;
  FILE *fp, *fp1;
  int stroka;
  int i;
  fp = fopen(".\\alc.dat", "r+b");
  fp1 = fopen(".\\alc.dat", "w+b");
  int cur = 0;

  cout << "введите номер строчки которую хотите удалить";
  cin >> stroka;
  cout << stroka;
  long fileSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  long structSize = sizeof(Institut);
  int numOfStruct = fileSize / structSize;

  for (int i = 0; i < numOfStruct; i++)
  {
    fread(&pack, sizeof(Institut), 1, fp);
    if (i != stroka)
    {
      cur++;
      fwrite(&pack, sizeof(Institut), 1, fp1); // записываем в файл_2
    }
  }
  fclose(fp);
  fclose(fp1);
}

