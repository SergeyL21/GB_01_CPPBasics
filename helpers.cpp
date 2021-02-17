/*
 * Created by Qt Creator 4.11.0 @ 17 Feb 2021 13:45:01
 *
 * Project: GB_CppBasics
 * File: helpers.cpp
 *
 * Author: Sergey Lola
 */

#include "helpers.h"

#include <ctime>
#include <bitset>

using namespace std;

namespace helpers {

// ---------------------------------------------------------------------------
std::unique_ptr<int[]> allocArray1D(size_t size)
{
  return unique_ptr<int[]>{new int [size], default_delete<int[]>()};
}

// ---------------------------------------------------------------------------
unique_ptr<unique_ptr<int[]>[]> allocArray2D(size_t columns, size_t rows) {
  // для двухмерного массива оборачивание в unique_ptr выглядит ужасно! :(
  // можно было, конечно, вызвать allocArray1D с длиной [columns * rows]
  // и просто работать с этим, но хотелось именно вариант с указателем на
  // указатель в связке с unique_ptr.
  unique_ptr<unique_ptr<int[]>[]> array{new unique_ptr<int[]>[columns],
      default_delete<unique_ptr<int[]>[]>()};
  for (size_t c {0u}; c < columns; ++c)
  {
    array[c] = unique_ptr<int[]>{new int[rows], default_delete<int[]>()};
  }
  return array;
}

// ---------------------------------------------------------------------------
int getRandomNumber(int lower, int upper)
{
  return rand() % (upper - lower + 1) + lower;
}

// ---------------------------------------------------------------------------
void fillMatrixColumn(int *array, size_t size, p_bounds const &bounds)
{
  for (size_t n {0u}; n < size; ++n)
  {
    array[n] = getRandomNumber(bounds.first, bounds.second);
  }
}

// ---------------------------------------------------------------------------
bool generateFile(const string &filepath, p_bounds const &size_bounds)
{
  ofstream fout(filepath, ios_base::binary);
  if (fout.is_open())
  {
    const auto fileSize {size_t(getRandomNumber(size_bounds.first, size_bounds.second))};
    string line;
    for (size_t l {0u}; l < fileSize; ++l)
    {
      // генерируем последовательность 0 и 1, например, размером 16
      fout << bitset<16u>(getRandomNumber()).to_string() << endl;
    }
    fout.flush();
    fout.close();
    return true;
  }
  cout << "Error: " << strerror(errno) << endl;
  return false;
}

// ---------------------------------------------------------------------------
bool mergeFiles(const string &filepathA,
                const string &filepathB,
                const string &filepathC)
{
  ifstream finA(filepathA, ios_base::binary);
  ifstream finB(filepathB, ios_base::binary);
  ofstream fout(filepathC, ios_base::binary);
  if (finA.is_open() && finB.is_open() && fout.is_open())
  {
    fout << finA.rdbuf() << finB.rdbuf();
    finA.close();
    finB.close();
    fout.flush();
    fout.close();
    return true;
  }
  cout << "Error: " << strerror(errno) << endl;
  return false;
}

// ---------------------------------------------------------------------------
bool findWord(ifstream &stream, size_t &lineNum, const string &word)
{
  string line;
  lineNum = 0u;
  while(getline(stream, OUT line, '\n'))
  {
    ++lineNum;
    if (line.find(word) != string::npos)
    {
      return true;
    }
  }
  return false;
}

} // namespace helpers

