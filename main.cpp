/*
 * Created by Qt Creator 4.11.0 @ 01 Feb 2021 21:21:03
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include <iostream>
#include <limits>

// макрос для удаления предупреждения об неиспользуемой переменной
#undef unused
#define unused(x) (void)(x);

// вспомогательный макрос показывающий что переменная передается по ссылке
#undef OUT
#define OUT

using namespace std;

extern int task1_A, task1_B, task1_C, task1_D;

// ---------------------------------------------------------------------------
// прототип функции получения корректного ввода с клавиатуры для типа int
void getAndValidateInput(const string &text, int &input);

// ---------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  unused(argc)
  unused(argv)
  // -------------------------------------------------------------------------
  // ЗАДАНИЕ 2: Дано целое число. Если оно меньше или равно 21, то выведите на
  // экран разницу между этим числом и числом 21. Если же заданное число
  // больше, чем 21, необходимо вывести удвоенную разницу между этим числом и
  // 21. При выполнении задания следует использовать тернарный оператор (?:).
  {
    int input;
    const int MAGIC_NUM = 21;
    cout << "--- TASK 2 ---" << endl;
    getAndValidateInput(string("Please enter an integer number: "), OUT input);

    const int diff = (input <= MAGIC_NUM) ?
                      MAGIC_NUM - input :
                      (input - MAGIC_NUM) << 1;
    cout << "Difference between your input number and " <<
            MAGIC_NUM <<
            " is: " <<
            diff <<
            endl;
  }
  // -------------------------------------------------------------------------
  // ЗАДАНИЕ 3: Описать трёхмерный целочисленный массив, размером 3х3х3 и
  // указатель на значения внутри массива и при помощи операции разыменования
  // вывести на экран значение центральной ячейки получившегося куба [1][1][1]
  {
    const int cube[3][3][3] {
      {{1, 1, 1}, {2, 4, 2}, {1, 1, 1}},
      {{2, 2, 2}, {4, 7, 4}, {2, 2, 2}},
      {{3, 3, 3}, {8, 8, 8}, {3, 3, 3}}
    };
    cout << endl << "--- TASK 3 ---" << endl;
    const int *pCube = &cube[1][1][1];
    cout << "Cube[1][1][1] = " << *pCube << endl;
  }
  // -------------------------------------------------------------------------
  // ЗАДАНИЕ 1: Написать программу, вычисляющую выражение a * (b + (c / d)) и
  // выводящую результат с плавающей точкой, где a, b, c, d – целочисленные
  // константы. Используйте static_cast или С-Style cast к float чтобы
  // выполнить точное деление.
  // +
  // ЗАДАНИЕ 4: Написать программу, вычисляющую выражение из первого задания,
  // а переменные для неё объявлены и инициализировать в другом cpp файле.
  // Используйте extern.
  {
    cout << endl << "--- TASK 1+4 ---" << endl;
    getAndValidateInput(string("Please enter integer number A: "), OUT task1_A);
    getAndValidateInput(string("Please enter integer number B: "), OUT task1_B);
    getAndValidateInput(string("Please enter integer number C: "), OUT task1_C);
    // здесь дополнительно проводим проверку на то, чтобы знаменатель d не был
    // равен 0!
    do {
      getAndValidateInput(string("Please enter integer number D (other than 0): "),
                          OUT task1_D);
    } while (0 == task1_D);
    cout << "The result is: " <<
            task1_A * (task1_B + (static_cast<float>(task1_C) / task1_D)) <<
            endl;
  }
  return 0;
}

// ---------------------------------------------------------------------------
void getAndValidateInput(const string &text, int &input)
{
  bool isValid = false;   // переменная для валидации введенного значения
  do {
    cout << text << flush;
    cin >> input;
    isValid = cin.good();
    if (cin.fail()) {
      // пользователь ввел некорректное значение, сбрасываем состояние
      // буфера до состояния "good"
      cin.clear();
      // и очищаем его
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } while (!isValid);
}
