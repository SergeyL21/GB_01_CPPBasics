/*
 * Created by Qt Creator 4.11.0 @ 20 Feb 2021 16:06:16
 *
 * Project: GB_CppBasics
 * File: mylib.h
 *
 * Author: Sergey Lola
 */

#pragma once

#include <memory>
#include <vector>
#include <random>
#include <sstream>
#include <iomanip>
#include <algorithm>

// ---------------------------------------------------------------------------
// вспомогательный макрос для удаления предупреждения об неиспользуемой переменной
#undef UNUSED
#define UNUSED(X) (void)(X);

// ---------------------------------------------------------------------------
// вспомогательный макрос показывающий что переменная передается по ссылке
#undef OUT
#define OUT

// ---------------------------------------------------------------------------
// макросы для дополнительного обозначения секции бесконечного цикла
#define FOREVER_BEGIN do
#define FOREVER_END while(true);

// ---------------------------------------------------------------------------
// макрофункция определения входит ли число в заданный диапазон значений
#define IN_RANGE(VALUE, MIN, MAX) \
  ((((VALUE) >= (MIN)) && ((VALUE) < (MAX))) ? true : false)

// ---------------------------------------------------------------------------
// макрофункция обмена значенями между двумя целочисленными переменными
#define SWAP_BASE_INT(A, B) ((A) ^= (B), (B) ^= (A), (A) ^= (B))
// макрофункция обмена значенями между двумя целочисленными переменными с
// проверкой на равенство этих значений
#define SWAP_INT(A, B) ((&(A) == &(B)) ? (A) : SWAP_BASE_INT(A, B))

// ---------------------------------------------------------------------------
// поскольку для C++14 reflection не завезли (вроде как луч надежды появился
// в C++20 :) ), то для простого отображения имени перечислений приходится
// делать один достаточно "грязный" хак с использованием __LINE__!
//
// объявляем вспомогательные макросы для формирования псевдо-enums
#define FAKE_ENUM_TYPE(X) using Type = FakeEnum<X>;
#define FAKE_ENUM_VALUE(VALUE) \
  constexpr Type VALUE{ __LINE__, #VALUE};

// ---------------------------------------------------------------------------
// шаблонный класс псевдо-enum
template <typename T>
struct FakeEnum final
{
  T value{T{}};
  const char *refl_name{nullptr};

  constexpr operator T() const noexcept { return value; }
  constexpr const char *operator&() const noexcept { return refl_name; }
};

// ---------------------------------------------------------------------------
// пространства имен для 4-го задания
namespace enums
{

// пространство имен с перечислением уровня профессиональных навыков сотрудника
namespace Level
{
  FAKE_ENUM_TYPE(char)
  // задаем число с которого начнется наш FakeEnum (главное потом не забыть
  // вернуть нумерацию через __LINE__ на нормальное число)
#line 0
  FAKE_ENUM_VALUE(Schoolkid)  // начальный
  FAKE_ENUM_VALUE(Adept)      // улучшенный
  FAKE_ENUM_VALUE(Red_Eyed)   // продвинутый
  FAKE_ENUM_VALUE(Grandmaster)// высокий
  FAKE_ENUM_VALUE(Stroustrup) // максимальный
} // namespace Level

// пространство имен с перечислением оценки психологического состояния сотрудника
namespace Moral
{
  FAKE_ENUM_TYPE(char)
  // задаем число с которого начнется наш FakeEnum
#line 0
  FAKE_ENUM_VALUE(Undefined)  // по умолчанию
  FAKE_ENUM_VALUE(Monday)     // слабое
  FAKE_ENUM_VALUE(Wednesday)  // среднее
  FAKE_ENUM_VALUE(Friday)     // высокое
} // namespace Moral

// пространство имен с перечислением предметов используемых сотрудником
namespace Item
{
  FAKE_ENUM_TYPE(char)
  // задаем число с которого начнется наш FakeEnum
#line 1
  FAKE_ENUM_VALUE(CoffeeMug)        // зелье повышения параметра moral
  FAKE_ENUM_VALUE(MagicCard)        // ключ получения разрешения на проход в определенные локации
  FAKE_ENUM_VALUE(SingularityBook)  // книга "Шаблоны С++: Краткий справочник разработчика"
}

// возвращаем нормальную положение для __LINE__. У меня соответственно это 113
// строчка, и да - "грязно", но увы это не C# или Java, где отражения делаются буквально
// одним кликом, здесь имеем что имеем (это без подключения сторонних решений!) :(
#line 113

} // namespace enums

// ---------------------------------------------------------------------------
// пространства имен для вспомогательных конструкций при выполнии ДЗ
namespace mylib
{

// ---------------------------------------------------------------------------
// структура описывающая сотрудника для 4-го задания
#pragma pack(push, 1)
struct TEmployee {
  using PEmployee = std::unique_ptr<TEmployee>;

  std::string name;                         // идентификатор сотрудника
  unsigned short salary;                    // зарплата сотрудника
  unsigned int tasks;                       // текущее количество активных задач
  enums::Level::Type level;                 // уровень профессиональных навыков
  enums::Moral::Type moral;                 // оценка психологического состояния
  std::vector<enums::Item::Type> inventory; // инвентарь сотрудника
  std::vector<PEmployee> currentEnemies;    // текущие враждебные персонажи

// public members
  // метод вывода значений структуры в строку
  std::string toString(bool print_header) const;
};
#pragma pack(pop)

// ---------------------------------------------------------------------------
// шаблонная функция для заполнения переданного объекта типа std::array
template <typename T, std::size_t N>
void fillArray(std::array<T, N> &array, std::pair<T, T> const &range)
{
  using namespace std;
  std::mt19937 generator(random_device{}());
  std::uniform_real_distribution<T> dis{range.first, range.second};
  for (auto it = array.begin(); it != array.end(); ++it)
  {
    *it = dis(generator);
  }
}

// ---------------------------------------------------------------------------
// функция для преобразования массива типа std::array в std::string
template <typename T, std::size_t N>
std::string array2String(std::array<T, N> const &array, int precision = 6)
{
  using namespace std;
  stringstream stream;
  for (auto it = array.cbegin(); it != array.cend(); ++it)
  {
    stream << fixed << setprecision(precision) << *it << " ";
  }
  return stream.str();
}

// ---------------------------------------------------------------------------
// шаблонная функция для подсчета кол-ва положительных и отрицательных чисел в
// массиве
template <typename T, std::size_t N>
void countArrayNums(std::array<T, N> const &array, int &positives, int &negatives)
{
  positives = negatives = 0;
  for (auto it = array.cbegin(); it != array.cend(); ++it)
  {
    positives += int{*it > 0};
    negatives += int{*it < 0};
  }
}

// ---------------------------------------------------------------------------
// шаблонная функция реализации алгоритма "шейкерной" сортировки (хоть чуточку
// более "умная", нежели пузырьковая! :) )
void shakerSort(int array[], int size);

} // namespace mylib


