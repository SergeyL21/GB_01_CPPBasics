/*
 * Created by Qt Creator 4.11.0 @ 01 Feb 2021 21:21:03
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include <iostream>

// макрос для удаления предупреждения об неиспользуемой переменной
#undef unused
#define unused(x) (void)(x);

// -------------------------------------------------------------------------
// ЗАДАНИЕ 2: Создать перечисление (enum) с возможными вариантами символов
// для игры в крестики-нолики.
enum class ECellType : std::uint8_t {
  Empty,      // поле не заполнено
  Sym_X,      // символ "Х"
  Sym_O       // символ "O"
};

// -------------------------------------------------------------------------
// ЗАДАНИЕ 4: Создать структуру (struct) данных «Поле для игры в крестики-
// нолики» и снабдить его всеми необходимыми свойствами (подумайте что может
// понадобиться).

// структура описывающая одну игровую ячейку поля
struct GameCell {
  int x {-1};                           // порядковый номер ячейки по горизонтали
  int y {-1};                           // порядковый номер ячейки по вертикали
  ECellType state { ECellType::Empty }; // текущее состояние ячейки
};

// структура описывающая игровое поле
struct GameField {
  // размер поля (предполагается что по горизонтали и по вертикали размеры поля
  // всегда одинаковы)
  static const int iFieldSize {3};

  // теоретически лучше конечно использовать динамические контейнеры (std::vector),
  // поскольку поле для игры может быть как классическое 3х3, так и большего размера.
  // Но предполагается, что на этом этапе мы знаем только статические массивы,
  // поэтому для потенциального будущего "маневра" вводим константу!
  GameCell cells[iFieldSize][iFieldSize];
};

// -------------------------------------------------------------------------
// ЗАДАНИЕ 5: Создать структуру (struct) объединяющую: union (int, float,
// char) и 3-и битовых поля (флага) указывающими какого типа значение в
// данный момент содержится в объединении (isInt, isFloat, isChar).
// Продемонстрировать пример использования в коде этой структуры.
struct SimpleVariant {
  // можно было сделать ее unnamed, но возможно появление предупреждения об
  // неименнованных типах данных!
  union Data {
    char ch;
    int i;
    float f;
  } data;

  unsigned isInt : 1;
  unsigned isFloat : 1;
  unsigned isChar : 1;
};

// ---------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  unused(argc)
  unused(argv)
  // -------------------------------------------------------------------------
  // ЗАДАНИЕ 1: Создать и инициализировать переменные пройденных типов данных
  // (short int, int, long long, char, bool, float, double)
  // ПРИМЕЧАНИЕ: использовал новый тип инициализаторов введенный в С+11, как
  // рекомендуемый к применению (даже не смотря на то, что здесь POD-типы)
  {
    bool bVar {true};               unused(bVar)
    char chVar { 'A' };             unused(chVar)
    short int nVar { 1 };           unused(nVar)
    int iVar { 2 };                 unused(iVar)
    long long lVar { 10000000ll };  unused(lVar)
    float fpVar { 0.33f };          unused(fpVar)
    double dpVar { 0.12345 };       unused(dpVar)
  }
  // -------------------------------------------------------------------------
  // ЗАДАНИЕ 3: Создать массив, способный содержать значения такого
  // перечисления и инициализировать его.
  {
    const auto iSize = GameField::iFieldSize;
    // для инициализации всех значений массива CellType::Empty
    ECellType aGameField[iSize][iSize] = { {ECellType::Empty} };
    unused(aGameField)
  }
  // -------------------------------------------------------------------------
  // ЗАДАНИЕ 5: Создать структуру (struct) объединяющую: union (int, float,
  // char) и 3-и битовых поля (флага) указывающими какого типа значение в
  // данный момент содержится в объединении (isInt, isFloat, isChar).
  // Продемонстрировать пример использования в коде этой структуры.
  {
    using namespace std;

    SimpleVariant var;
    var.data.i = 2020;
    var.isInt = true;
    var.isChar = false;
    var.isFloat = false;

    cout << "Integer variable:" << endl;
    cout << " data.i = " << var.data.i << endl;
    cout << " data.ch = " << var.data.ch << endl;
    cout << " data.f = " << var.data.f << endl;

    var.data.ch = 'X';
    var.isInt = false;
    var.isChar = true;
    var.isFloat = false;

    cout << endl << "Character variable:" << endl;
    cout << " data.i = " << var.data.i << endl;
    cout << " data.ch = " << var.data.ch << endl;
    cout << " data.f = " << var.data.f << endl;

    var.data.f = 0.333f;
    var.isInt = false;
    var.isChar = false;
    var.isFloat = true;

    cout << endl << "Floating point variable:" << endl;
    cout << " data.i = " << var.data.i << endl;
    cout << " data.ch = " << var.data.ch << endl;
    cout << " data.f = " << var.data.f << endl;
  }
  return 0;
}