/*
 * Created by Qt Creator 4.11.0 @ 20 Feb 2021 16:08:23
 *
 * Project: GB_CppBasics
 * File: mylib.cpp
 *
 * Author: Sergey Lola
 */

#include "mylib.h"

using namespace std;

namespace mylib
{

// -------------------------------------------------------------------------------------
void shakerSort(int array[], int size)
{
  int i, j, k;
  for (i = 0; i < size;)
  {
    for (j = i + 1; j < size; ++j)
    {
      if (array[j] < array[j - 1])
      {
        SWAP_INT(array[j], array[j - 1]);
      }
    }
    --size;
    for(k = size; k > i; --k)
    {
      if(array[k] < array[k - 1])
      {
        SWAP_INT(array[k], array[k - 1]);
      }
    }
    ++i;
  }
}

// -------------------------------------------------------------------------------------
string TEmployee::toString(bool print_header) const
{
  stringstream stream;
  if (print_header)
  {
    stream << "Employee [sizeof = " << sizeof(*this) << "]: " << endl;
  }
  stream << " name: " << name << endl
         << " salary: " << salary << endl
         << " tasks: " << tasks << endl
         << " level: " << level.refl_name << endl
         << " moral: " << moral.refl_name << endl
         << " currentEnemies: ";
  for (auto it = currentEnemies.cbegin(); it != currentEnemies.cend(); ++it)
  {
    stream << "{" << endl << (*it)->toString(false) << endl << "}" << endl;
  }
  stream << endl << " inventory: {";
  for (auto it = inventory.cbegin(); it != inventory.cend(); ++it)
  {
    if (nullptr != (*it).refl_name)
    {
      stream << (*it).refl_name << ", ";
    }
  }
  stream.seekp(-2, std::ios_base::end);
  stream << "}" << endl;
  return stream.str();
}

} // namespace mylib
