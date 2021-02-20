/*
 * Created by Qt Creator 4.11.0 @ 17 Feb 2021 12:34:22
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include <iostream>
#include <fstream>

#include "mylib.h"

using namespace std;

// ---------------------------------------------------------------------------
// макросы для обозначения размера массива в 3-м задании
#define TASK3_ARRAY_SIZE 10

// ---------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  UNUSED(argc)
  UNUSED(argv)
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 1: Создайте проект из 2-х cpp файлов и заголовочного (main.cpp, mylib.cpp,
  // mylib.h). Во втором модуле mylib объявить 3 функции: для инициализации массива (типа
  // float), печати его на экран и подсчета количества отрицательных и положительных
  // элементов. Вызывайте эти 3-и функции из main для работы с массивом.
  // +
  // ЗАДАНИЕ 5: Сделайте задание 1 добавив свой неймспейс во втором модуле (первое задание
  // тогда можно не делать).
  {
    cout << "--- TASK 1+5 ---" << endl;
    const size_t LOCAL_ARRAY_SIZE{10u};
    const auto RANGE {make_pair(-100.f, 100.f)};
    array<float, LOCAL_ARRAY_SIZE> arr;
    mylib::fillArray(OUT arr, RANGE);
    cout << "Array: " << mylib::array2String(arr, 2) << endl;
    int positives, negatives;
    mylib::countArrayNums(arr, OUT positives, OUT negatives);
    cout << "Positive numbers count: " << positives << endl;
    cout << "Negative numbers count: " << negatives << endl;
  }
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 2: Описать макрокоманду (через директиву define), проверяющую, входит ли
  // переданное ей число (введенное с клавиатуры) в диапазон от нуля (включительно) до
  // переданного ей второго аргумента (исключительно) и возвращает true или false, вывести
  // на экран "true" или "false".
  {
    cout << endl << "--- TASK 2 ---" << endl;
    auto bool2String = [](bool value)
    {
      return value ? std::string{"true"} : std::string{"false"};
    };
    cout << "Macro function IN_RANGE(3, 0, 5) = " << bool2String(IN_RANGE(3, 0, 5)) << endl;
    cout << "Macro function IN_RANGE(5, 0, 5) = " << bool2String(IN_RANGE(5, 0, 5)) << endl;
    cout << "Macro function IN_RANGE(2 + 1, 0, 4) = " << bool2String(IN_RANGE(2 + 1, 0, 4)) << endl;
    cout << "Macro function IN_RANGE(6, 0, 2 * 3) = " << bool2String(IN_RANGE(6, 0, 2 * 3)) << endl;
    cout << "Macro function IN_RANGE(0, 0, 1) = " << bool2String(IN_RANGE(0, 0, 1)) << endl;
    cout << "Macro function IN_RANGE(0, 0, -1) = " << bool2String(IN_RANGE(0, 0, -1)) << endl;
  }
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 3: Задайте массив типа int. Пусть его размер задается через директиву
  // препроцессора #define. Инициализируйте его через ввод с клавиатуры. Напишите для него
  // свою функцию сортировки (например Пузырьком). Реализуйте перестановку элементов как
  // макрокоманду SwapINT(a, b). Вызывайте ее из цикла сортировки.
  {
    cout << endl << "--- TASK 3 ---" << endl;
    array<int, TASK3_ARRAY_SIZE> arr;
    std::size_t index{1u};
    // заполняем массив с клавиатуры
    for (auto it = arr.begin(); it != arr.end(); ++it, ++index)
    {
      FOREVER_BEGIN
      {
        cout << " value " << index << ": ";
        if (cin >> *it)
        {
          break;
        }
        else
        {
          cout << "Invalid input, try again!" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
      }
      FOREVER_END
    }
    mylib::shakerSort(arr.data(), int{arr.size()});
    cout << "Sorted array: " << mylib::array2String(arr) << endl;
  }
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 4: Объявить структуру Сотрудник с различными полями. Сделайте для нее
  // побайтовое выравнивание с помощью директивы pragma pack. Выделите динамически
  // переменную этого типа. Инициализируйте ее. Выведите ее на экран и ее размер с помощью
  // sizeof. Сохраните эту структуру в текстовый файл.
  {
    cout << endl << "--- TASK 4 ---" << endl;
    auto employee = make_unique<mylib::TEmployee>();
    employee->name = "Anonymous";
    employee->salary = 3000u;
    employee->tasks = 100500u;
    employee->level = enums::Level::Red_Eyed;
    employee->moral = enums::Moral::Monday;
    employee->inventory = {enums::Item::MagicCard, enums::Item::SingularityBook};

    const auto text = employee->toString(true);
    cout << text << endl;
    ofstream fout{"employee.txt"};
    if (fout.is_open())
    {
      fout << text;
      fout.close();
      cout << "The file was created successfully." << endl;
    }
  }

  return 0;
}
