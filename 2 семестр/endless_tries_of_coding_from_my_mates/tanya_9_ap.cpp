#include <iostream>

#include <ctime>

using namespace std;

struct man {//делаем структуру
    string surname;
    string address;
};

void vibirka(man* massiv, int size);
void vivid(man* massiv, int size);
void sravnenie(man* massiv1, int size1, man* massiv2, int size2, man* massiv3, int* size3);

int main() {
    setlocale(LC_ALL, "rus");

    srand(time(NULL));

    man *array1 = new man[10];//динамический массив new используется для выделения и установки памяти для заданного значения:

    vibirka(array1, 10);//альо,альо, вызываю значения функции
    cout << "   Список 1: " << endl;//вывожу тип список1
    vivid(array1, 10);//вывожу свой массивчик

    man *array2 = new man[4];//вот и второй динам массив
    vibirka(array2, 4);
    cout << "   Список 2: " << endl;
    vivid(array2, 4);


    man *array3 = new man[14];//третий
    int result_size=0;
    cout << "   Список 3: " << endl;

    sravnenie(array1, 10, array2, 4, array3, &result_size);
    sravnenie(array2, 4, array1, 10, array3, &result_size);

    vivid(array3, 10);
    delete [] array1;//освобождение памяти
    delete [] array2;
    delete [] array3;


    return 0;
}

void vibirka(man* massiv, int size) {
    string surname[5] = {
      "Павлова",
      "Рудаметкин",
      "Москаленко",
      "Менделеев",
      "Высоцкий"
    };

    string address[6] = {
      "Пересыпкина",
      "Политехническая",
      "Рогозина",
      "Чубинского",
      "Школьная",
      "Петлюры"
    };//из чего выбираем

    for (int i = 0; i < size; i++) {
        man a = {
          surname[rand() % 3],
          address[rand() % 4]
        };
        massiv[i] = a;//задаем из скольки выбираем
    }
}

void vivid(man* massiv, int size) {//костыльный вывод, тип мы дали размерчик 10 а потом удаляем места там где ничего нет
    for (int i = 0; i < size; i++) {
        if (massiv[i].surname != "") {
            cout << " Фамилия: " << massiv[i].surname << "\t" << " Адрес: " << massiv[i].address << endl;

        }
    }
}

void sravnenie(man* massiv1, int size1, man* massiv2, int size2, man* massiv3, int* size3) {//Берем из одного массива елемент если этот елемент = елеинту второго массива , перерываем цикл , а если наше условие как бы верно то записываем в третий массив
    bool uslovie;
    for (int i = 0; i < size1; i++) {
        uslovie = true;
        for (int j = 0; j < size2; j++) {
            if (massiv1[i].surname == massiv2[j].surname && massiv1[i].address == massiv2[j].address) {
                uslovie = false;
                break;
            }
        }
        if (uslovie == true) {
            massiv3[*size3] = massiv1[i];
            (*size3)++;
        }
    }
}
