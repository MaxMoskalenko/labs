#include <iostream>

#include <time.h>

#include <string>

int main() {
  using namespace std;
  setlocale(LC_ALL, "rus");

  const int street_Surname = 7;
  string value[street_Surname] = {
    "Иванов",
    "ул. Политехническая",
    "ул. Щербакова",
    "Сидоров",
    "Руденко",
    "ул. Пересыпкина",
    "Фесенко"
  };
  cout << "Значення першого списку:  \n";
  for (int i = 0; i < street_Surname; i++) {
    cout << "Значення " << i << " = " << value[i] << endl;
  }

  const int street_Surname657 = 10;
  string words[street_Surname657] = {
    "ул. Политехническая",
    "Завражная",
    "ул. Академика Шалимова",
    "Суконов",
    "Руденко",
    "ул. Пересыпкина",
    "ул.Победы",
    "Фесенко",
    "Громов",
    "ул. Чубинского"
  };
  cout << "\n\nЗначення другого списку:  \n";
  for (int i = 0; i < street_Surname657; i++) {
    cout << "Значення " << i << " = " << words[i] << endl;
  }

  for (i = 0; i < street_Surname + street_Surname657; i++) {
    if (i < 0) data[i] = value[i];
    else data[i] = words[i];
  }
  for (i = 0; i < street_Surname + street_Surname657; i++) {
    cout << "Значення " << i << " = " << data[i] << endl;
    puts("\n");
  }
  system("PAUSE");
  return 0;
}
}
