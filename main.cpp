/*
 * Created by Qt Creator 4.11.0 @ 17 Feb 2021 12:34:22
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include "helpers.h"

using namespace std;

// ---------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  unused(argc)
  unused(argv)
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 1: Выделить в памяти динамический одномерный массив типа int. Размер массива
  // запросить у пользователя. Инициализировать его числами степенями двойки: 1, 2, 4, 8,
  // 16, 32, 64, 128 … Вывести массив на экран. Не забыть освободить память. =)
  // Разбить программу на функции.
  {
    size_t arraySize;
    cout << "--- TASK 1 ---" << endl;
    cout << "Please enter an array size: " << flush;
    cin >> arraySize;

    auto pArray = helpers::allocArray1D(arraySize);
    int number {1u};
    for (std::size_t n {0u}; n < arraySize; ++n, (number <<= 1))
    {
      pArray[n] = number;
    }
    helpers::printArray(pArray.get(), arraySize);
    // объект pArray автоматически очиститься при выходе из области видимости, delete тут
    // не нужен! Магия "умных указателей" )
  }
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 2: Динамически выделить матрицу 4х4 типа int. Инициализировать ее
  // псевдослучайными числами через функцию rand. Вывести на экран. Разбейте вашу программу
  // на функции которые вызываются из main.
  {
    cout << endl << "--- TASK 2 ---" << endl;
    cout << "Matrix with random numbers:" << endl;
    const size_t COLUMNS {4u}, ROWS {4u};
    // устанавливаем границы генерируемых чисел (для лучшего восприятия при выводе)
    const auto BOUNDS {make_pair(10, 99)};
    auto pArray = helpers::allocArray2D(COLUMNS, ROWS);
    for (std::size_t c {0u}; c < COLUMNS; ++c) {
      auto column = pArray[c].get();
      cout << c + 1u << " | ";
      helpers::fillMatrixColumn(column, ROWS, BOUNDS);
      helpers::printArray(column, ROWS, true);
    }
    // объект pArray автоматически очиститься при выходе из области видимости, delete тут
    // не нужен! Магия "умных указателей" )
  }
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 3: Написать программу c 2-я функциями, которая создаст два текстовых файла
  // (*.txt), примерно по 50-100 символов в каждом (особого значения не имеет с каким
  // именно содержимым). Имена файлов запросить у польлзователя.
  // +
  // ЗАДАНИЕ 4: Написать функцию, «склеивающую» файлы из задания 3 в третий текстовый файл
  // (имя файлов спросить у пользователя).
  {
    string filepathA, filepathB, filepathC;
    cout << endl << "--- TASK 3+4 ---" << endl;
    cout << "Please enter a path for first file: ";
    cin >> filepathA;
    const auto SIZE_BOUNDS {make_pair(50, 100)};
    if (helpers::generateFile(filepathA, SIZE_BOUNDS)) {
      cout << "'" << filepathA << "'" << " created successfully." << endl;
    }
    cout << "Please enter a path for second file: ";
    cin >> filepathB;
    if (helpers::generateFile(filepathB, SIZE_BOUNDS)) {
      cout << "'" << filepathB << "'" << " created successfully." << endl;
    }
    cout << "Please enter a path for merge files " <<
            "'" << filepathA << "' and " <<
            "'" << filepathB << "': ";
    cin >> filepathC;
    if (helpers::mergeFiles(filepathA, filepathB, filepathC)) {
      cout << "'" << filepathC << "'" << " created and merged successfully." << endl;
    }
  }
  // -------------------------------------------------------------------------------------
  // ЗАДАНИЕ 5: Написать программу, которая проверяет присутствует ли указанное
  // пользователем при запуске программы слово в указанном пользователем файле
  // (для простоты работаем только с латиницей).
  {
    string filepath;
    cout << endl << "--- TASK 5 ---" << endl;
    cout << "Please enter a file path: ";
    cin >> filepath;
    ifstream fin(filepath, ios_base::binary);
    if (fin.is_open())
    {
      string word;
      cout << "Please enter a search word: ";
      cin >> word;
      size_t lineNum;
      if (helpers::findWord(OUT fin, OUT lineNum, word))
      {
        cout << "Word '" << word << "'" << " found at line " << lineNum << endl;
      }
      else
      {
        cout << "Word '" << word << "' not found" << endl;
      }
      fin.close();
    }
    else {
      cout << "Error: " << strerror(errno) << endl;
    }
  }
  return 0;
}
