/*
 * Created by Qt Creator 4.11.0 @ 08 Feb 2021 21:03:13
 *
 * Project: GB_CppBasics/lib
 * File: hw.cpp
 *
 * Author: Sergey Lola
 */

#include "hw.h"

#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// ---------------------------- LOCAL VARIABLES ------------------------------
const auto TASK1_RANGE {std::make_pair(10, 20)};
const auto TASK2_MAGIC_NUM {10};

namespace lib {
// ---------------------------------------------------------------------------
// ������� 1: �������� ���������, ����������� ��� ����� ���� (��������� �
// ����������) ����� ����� � �������� �� 10 �� 20 (������������), ���� �� �
// ������� ������ "true", � ��������� ������ � "false".
bool task1(int numA, int numB)
{
  const int sum = numA + numB;
  return (sum >= TASK1_RANGE.first) && (sum <= TASK1_RANGE.second);
}

// ---------------------------------------------------------------------------
// ������� 2: �������� ���������, ��������� �� ����� ������ �true�, ���� ���
// ������������� ���������, ����������� � � ������ ���� ��� ����� ������ ����
// �� ����, ���� �� ����� ����� ������. ����� "false".
bool task2(int numA, int numB)
{
  return (((TASK2_MAGIC_NUM == numA) && (TASK2_MAGIC_NUM == numB)) ||
          (TASK2_MAGIC_NUM == numA + numB));
}

// ---------------------------------------------------------------------------
// ������� 3: �������� ��������� ������� ������� �� ����� ������ ���� ��������
// ����� �� 1 �� 50. ��������: "Your numbers: 1 3 5 7 9 11 13 �". ��� �������
// ����������� ����� �++ ����.
void task3(int min, int max, string &res)
{
  res.assign(string("Your numbers: "));
  // "������" ������� ������������ ������� ������ ��� ������
  res.reserve(size_t(abs(max - min)) * 2u);
  // ���� ����� ������, �� ������� �������� � ���������� ���������
  if (!(min % 2))
  {
    min++;
  } 
  for (int n = min; n <= max; n += 2)
  {
    res.append(to_string(n) + ' ');
  }
  res.shrink_to_fit();
}

// ---------------------------------------------------------------------------
// ������� 4: �������� ���������, �����������, �������� �� ��������� ����� -
// �������. ������� ����� � ��� ����� ������������� �����, ������� ������� ���
// ������� ������ �� ������� � ���� ����.
bool task4(int num) {
  bool isPrime = true;
  const size_t upper_limit = static_cast<size_t>(std::sqrt(static_cast<double>(num))) + 1;
  for (size_t i = 2; i != upper_limit; ++i) {
    if (!(num % i)) {
      isPrime = false;
      break;
    }
  }
  return isPrime;
}

// ---------------------------------------------------------------------------
// ������� 5: ������������ ������ � ���������� ����� (���): �� 1 �� 3000.
// �������� ���������, ������� ���������� �������� �� ���� ��� ����������.
// ������ 4-� ��� �������� ����������, ����� ������� 100-��, ��� ���� ������
// 400-� � ����������.
bool task5(int year)
{
  // ��������� �������, ��� ������ 4-� ��� �������� �������
  const bool test1 = (year & 0x3) == 0;
  // ��������� �������, ��� ������ 100-� ��� �����������
  const bool test2 = (year % 25) != 0;
  // ��������� �������, ��� ������ 400-� ��� ���� �������� �������
  const bool test3 = (year % 0xf) == 0;

  return (test1 && (test2 || test3));
}

} // namespace lib
