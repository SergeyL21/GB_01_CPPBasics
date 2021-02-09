/*
 * Created by Qt Creator 4.11.0 @ 01 Feb 2021 21:21:03
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include <iostream>
#include <vector>

#include "hw.h"

// макрос для удаления предупреждения об неиспользуемой переменной
#undef unused
#define unused(x) (void)(x);

using namespace std;

// ---------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  unused(argc)
  unused(argv)

  bool t1 = lib::task1(1, 15);
  t1 = false;
  std::cout << t1 << std::endl;
}
