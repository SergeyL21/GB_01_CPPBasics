#pragma once

#include <iostream>
#include <random>
#include <chrono>
#include <math.h>
#include <string>
#include <numeric>

// вспомогательный макрос для конвертации переданного std::string в std::wstring
#define S2WS(S) std::wstring{(S).cbegin(), (S).cend()}

namespace base
{

  // -------------------------------------------------------------------------------------
  // шаблонная функция преобразования переданного статического массива в строку (для
  // задания 1)
  template <typename T, std::size_t N>
  std::string arrayToString(T const (&array)[N],
                const std::string &prefix = std::string{},
                const std::string &postfix = std::string{})
  {
    std::string result = prefix;
    std::size_t n{ 0u };
    do
    {
      result.append(std::to_string(array[n]) + ',');
    } while (++n < N);
    result.erase(result.size() - 1u);
    result.append(postfix);
    return result;
  }

  namespace inner {

    // -------------------------------------------------------------------------------------
    // вспомогательная шаблонная функция для заполнения переданного массива рандомной
    // последовательностью из 0 и 1 (для задания 2)
    template <std::size_t N>
    void fillArray(int(&array)[N])
    {
      std::size_t n{ 0u };
      const auto now{ std::chrono::system_clock::now() };
      const auto seed{ std::chrono::system_clock::to_time_t(now) };
      std::mt19937 generator{ unsigned(seed) };
      std::uniform_int_distribution<> dis{ 0, 1 };
      do
      {
        array[n] = dis(generator);
      } while (++n < N);
    }

  } // namespace inner

  // -------------------------------------------------------------------------------------
  // шаблонная функция для инвертирования значений 0 и 1 переданного массива (для задания 2)
  template <std::size_t N>
  void inverseArrayValues(int(&array)[N])
  {
    for (std::size_t n = 0u; n < N; ++n)
    {
      *(array + n) = !(*(array + n));
    }
  }

  // -------------------------------------------------------------------------------------
  // шаблонная функция для копирования из специализированного массива внутри функции в
  // переданный (для задания 3)
  template <std::size_t N>
  void copyArray(int(&array)[N])
  {
    static int local_array[N]{ 1, 4, 7, 10, 13, 16, 19, 22 };

    // конечно проще и короче было бы сделать нечто такое:
    // std::copy(std::begin(local_array), std::end(local_array), std::begin(array))
    // но в задании указано что должен быть именно цикл :)
    for (std::size_t n = 0u; n < N; ++n)
    {
      array[n] = local_array[n];
    }
  }

  namespace inner {

    // -------------------------------------------------------------------------------------
    // вспомогательная шаблонная функция поворота массива по итераторам (для задания 4)
    template <typename It>
    void rotateArray(It begin, It end, It offset)
    {
      if ((begin == offset) || (end == offset))
      {
        return;
      }

      auto read		= offset;
      auto next_read	= begin;
      auto write		= begin;

      while (read != end)
      {
        if (write == next_read)
        {
          next_read = read;
        }
        std::iter_swap(write++, read++);
      }
      rotateArray(write, end, next_read);
    }

  } // namespace inner

  // -------------------------------------------------------------------------------------
  // шаблонная функция поворота массива по заданному смещению (для задания 4)
  template <typename T, std::size_t N>
  void rotateArray(T(&array)[N], int offset)
  {
    // если смещение 0 или явно больше размера массива по модулю, то выходим
    if ((0 == offset) || (std::size_t(std::abs(offset)) > N))
    {
      return;
    }

    auto diff = (offset > 0) ? std::begin(array) : std::end(array);
    std::advance(diff, offset);
    inner::rotateArray(std::begin(array), std::end(array), diff);
  }

  // -------------------------------------------------------------------------------------
  // шаблонная функция для проверки равенства левой и правой частей массива (для задания 5)
  template <std::size_t N>
  bool checkBalance(int const (&array)[N])
  {
    int left = 0;
    for (std::size_t n = 0; n < N - 1u; ++n)
    {
      auto diff = std::begin(array);
      std::advance(diff, n + 1u);
      left += array[n];
      auto right = std::accumulate(diff, std::end(array), 0);

      if (left == right)
      {
        return true;
      }
    }
    return false;
  }

} // namespace base
