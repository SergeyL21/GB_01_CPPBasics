/*
 * Created by Qt Creator 4.11.0 @ 17 Feb 2021 13:04:56
 *
 * Project: GB_CppBasics
 * File: helpers.h
 *
 * Author: Sergey Lola
 */

#include <cstring>
#include <memory>
#include <iostream>
#include <fstream>

// макрос для удаления предупреждения об неиспользуемой переменной
#undef unused
#define unused(x) (void)(x);

// вспомогательный макрос показывающий что переменная передается по ссылке
#undef OUT
#define OUT

namespace helpers {

using p_bounds = std::pair<int, int>;

// ---------------------------------------------------------------------------
// шаблонная функция вывода переданного массива в поток вывода
template <typename T>
void printArray(T const *array, std::size_t size, bool printIndexes = false) {
  std::string extra;
  for (std::size_t n {0u}; n < size; ++n)
  {
    if (printIndexes)
    {
      extra = "[" + std::to_string(n + 1u) + "]=";
    }
    std::cout << extra << array[n] << " ";
  }
  std::cout << std::endl;
}

// ---------------------------------------------------------------------------
// прототип функции динамического выделения целочисленного одномерного массива
// с использованием unique_ptr
std::unique_ptr<int[]> allocArray1D(std::size_t size);

// ---------------------------------------------------------------------------
// прототип функции динамического выделения целочисленного двухмерного массива
// с использованием unique_ptr
std::unique_ptr<std::unique_ptr<int[]>[]> allocArray2D(std::size_t columns,
                                                       std::size_t rows);

// ---------------------------------------------------------------------------
// прототип функции получения произвольного числа в заданном диапазоне
int getRandomNumber(int lower = 0, int upper = RAND_MAX);

// ---------------------------------------------------------------------------
// прототип функции заполнения колонки матрицы
void fillMatrixColumn(int *array,
                      std::size_t size,
                      p_bounds const &bounds = std::make_pair(0, RAND_MAX));

// ---------------------------------------------------------------------------
// прототип функции создания и заполнения файла по переданному имени
bool generateFile(std::string const &filepath, p_bounds const &size_bounds);

// ---------------------------------------------------------------------------
// прототип функции объединения двух файлов в один отдельный
bool mergeFiles(std::string const &filepathA,
                std::string const &filepathB,
                std::string const &filepathC);

// ---------------------------------------------------------------------------
// прототип функции поиска в файловом потоке определенного слова
bool findWord(std::ifstream &stream, std::size_t &lineNum, std::string const &word);

} // namespace helpers
