/*
 * Created by Qt Creator 4.11.0 @ 27 Feb 2021 16:37:58
 *
 * Project: GB_CppBasics
 * File: game.cpp
 *
 * Author: Sergey Lola
 */
#include "game.h"

#include <iomanip>
#include <iostream>
#include <chrono>
#include <random>
#include <cstring>
#include <algorithm>

// --------------------------------------------------------------------------------------
// макрос валидации переданных значений Х и Y в диапазоне от нуля до SX/SY
#define VALIDATE_POINT(X, Y, SX, SY) \
  (((X) >= 0 && (X) < (SX)) && ((Y) >= 0 && (Y) < (SY)))

using namespace std;

// --------------------------------------------------------------------------------------
// объявление статических членов структуры Field
const int8_t Field::MIN_SIZE;
const int8_t Field::MAX_SIZE;

// --------------------------------------------------------------------------------------
// объявление локальных переменных
Field _gField;

namespace game {

// --------------------------------------------------------------------------------------
void initGame()
{
  auto inputValue = [](const std::string &param, int8_t vmin, int8_t vmax)
  {
    short value;
    do
    {
      cout << "Enter field " << param << " between " <<
              short(vmin) << " and " << short(vmax) << " : ";
      cin >> value;
      if ((value >= vmin) &&
          (value <= vmax))
      {
        break;
      }
    }
    while (true);
    return value;
  };

  closeGame();

  _gField.width = inputValue(string{"width"}, Field::MIN_SIZE, Field::MAX_SIZE);
  _gField.height = inputValue(string{"height"}, Field::MIN_SIZE, Field::MAX_SIZE);
  if (_gField.width == _gField.height)
  {
    const int8_t diff = _gField.width - Field::MIN_SIZE;
    if (0 == diff)
    {
      _gField.winCombo = _gField.width;
    }
    else
    {
      _gField.winCombo = inputValue(string{"win combination"}, Field::MIN_SIZE, Field::MIN_SIZE + diff);
    }
  }
  else
  {
    _gField.winCombo = min(_gField.width, _gField.height);
  }
  _gField.turnsLimit = _gField.width * _gField.height;

  // определяем кто ходит первый
  auto rand = inner::getRandomNumber(0, 1);
  if (1 == rand) {
    _gField.humanSign = Cell::CROSS;
    _gField.aiSign = Cell::ZERO;
    _gField.currentPlayer = Player::Human;
  }
  else {
    _gField.humanSign = Cell::ZERO;
    _gField.aiSign = Cell::CROSS;
    _gField.currentPlayer = Player::AI;
  }

  _gField.cells.resize(_gField.turnsLimit);
  fill(_gField.cells.begin(), _gField.cells.end(), Cell::EMPTY);

  cout << endl << "Human is '" << enum2Val(_gField.humanSign) << "', AI is '"
       << enum2Val(_gField.aiSign) << "', win combination is '"
       << short(_gField.winCombo) << "'" << endl;
  cout << "Press any key to start the game...";

  cin.clear();
  cin.ignore();
  cin.get();
}

// --------------------------------------------------------------------------------------
void closeGame()
{
  _gField = Field{};
}

// --------------------------------------------------------------------------------------
void startGame()
{
  bool isWin {false};
  inner::clearField();
  inner::updateField();
  do
  {
    // если закончилось число ходов, до того как кто либо выиграл, то это ничья
    if (++_gField.currentTurn > _gField.turnsLimit)
    {
      break;
    }

    if (Player::Human == _gField.currentPlayer)
    {
      inner::humanTurn();
      isWin = inner::checkWin(_gField.humanSign);
      _gField.currentPlayer = Player::AI;
    }
    else
    {
      inner::aiTurn();
      isWin = inner::checkWin(_gField.aiSign);
      _gField.currentPlayer = Player::Human;
    }

    inner::clearField();
    inner::updateField();
  }
  while (!isWin);

  if (isWin)
  {
    cout << endl << "*** Win "
         << ((Player::Human == _gField.currentPlayer) ? "AI" : "HUMAN")
         << " at turn " << short(_gField.currentTurn) << " ***" << endl;
  }
  else
  {
    cout << endl << "*** DRAW ***" << endl;
  }
}

namespace inner
{

// --------------------------------------------------------------------------------------
Cell getCell(int8_t x, int8_t y)
{
  return VALIDATE_POINT(x, y, _gField.width, _gField.height)
    ? _gField.cells.at(y * _gField.width + x) : Cell::EMPTY;
}

// --------------------------------------------------------------------------------------
bool setCell(int8_t x, int8_t y, Cell cell)
{
  if (VALIDATE_POINT(x, y, _gField.width, _gField.height))
  {
    _gField.cells[y * _gField.width + x] = cell;
    return true;
  }
  return false;
}

// --------------------------------------------------------------------------------------
int8_t getRandomNumber(int8_t min, int8_t max)
{
  const static auto seed = chrono::system_clock::now().time_since_epoch().count();
  static mt19937 generator{seed};
  uniform_int_distribution<int8_t> dis(min, max);
  return dis(generator);
}

// --------------------------------------------------------------------------------------
void clearField()
{
  system("cls");
}

// --------------------------------------------------------------------------------------
void updateField()
{
  static const char hSep {'|'};
  static const char vSep {'-'};
  static const string space {' '};

  cout << "Human is '" << enum2Val(_gField.humanSign) << "', AI is '"
       << enum2Val(_gField.aiSign) << "', win combination is '"
       << short(_gField.winCombo) << "'" << endl << endl;

  // отрисовка горизонтальной шкалы
  cout << space << hSep << "1";
  for (int8_t x {1}; x < _gField.width; ++x)
  {
    cout << space << x + 1;
  }
  cout << hSep << endl;

  for (int8_t y {0}; y < _gField.height; ++y)
  {
    cout << setfill(vSep) << setw((_gField.width + 1) * 2 + 1) << space << endl;
    cout << y + 1 << hSep;
    for (int8_t x {0}; x < _gField.width; ++x)
    {
      cout << enum2Val(getCell(x, y)) << hSep;
    }
    cout << endl;
  }
  cout << setfill(vSep) << setw((_gField.width + 1) * 2 + 1) << space << endl;
}

// --------------------------------------------------------------------------------------
bool checkWin(Cell playerSign)
{
  auto findSeq = [](int8_t x, int8_t y, int8_t vx, int8_t vy, int8_t size, Cell sign)
  {    
    const Point end {int8_t(x + size * vx),
                     int8_t(y + size * vy)};
    if (VALIDATE_POINT(end.x, end.y, size, size)) {
      return false;
    }
    bool isWin {true};
    for (int8_t n {0}; n < size; ++n)
    {
      isWin &= getCell(x + n * vx, y + n * vy) == sign;
      if (!isWin)
      {
        return false;
      }
    }
    return isWin;
  };

  for (int8_t x {0}; x < _gField.width; ++x)
  {
    for (int8_t y {0}; y < _gField.height; ++y)
    {
      // ищем последовательность:
      //  - по горизонтали vec = (1, 0)
      //  - по вертикали vec = (0, 1)
      //  - по прямой диагонали vec = (1, 1) и обратной vec = (1, -1)
      if (findSeq(x, y, 1, 0, _gField.winCombo, playerSign) ||
          findSeq(x, y, 0, 1, _gField.winCombo, playerSign) ||
          findSeq(x, y, 1, 1, _gField.winCombo, playerSign) ||
          findSeq(x, y, 1, -1, _gField.winCombo, playerSign))
      {
        return true;
      }
    }
  }
  return false;
}

// --------------------------------------------------------------------------------------
void humanTurn()
{
  short x, y;
  cout << endl;
  do
  {
    cout << "Enter X coordinate: ";
    cin >> x;
    x--;
    if (VALIDATE_POINT(x, 0, _gField.width, 1))
    {
      cout << "Enter Y coordinate: ";
      cin >> y;
      y--;
      if (VALIDATE_POINT(x, y, _gField.width, _gField.height))
      {
        if (inner::getCell(x, y) == Cell::EMPTY)
        {
          break;
        }
        cout << "Current position is already occupied!" << endl;
      }
    }
  }
  while (true);

  setCell(x, y, _gField.humanSign);
}

// --------------------------------------------------------------------------------------
void aiTurn()
{
  // если первый ход, то стараемся разместить знак компьютера ориентировочно где то по середине
  if (1 == _gField.currentTurn)
  {
    const int8_t centerX = _gField.width / 2 + _gField.width % 2 - 1;
    const int8_t centerY = _gField.height / 2 + _gField.height % 2 - 1;
    inner::setCell(centerX, centerY, _gField.aiSign);
  }
  else
  {
    // проверяем не выигрывает ли компьютер следующим ходом
    auto pos = ai::predictMove(_gField.aiSign);
    // если нет, то смотрим не выигрывает ли игрок следующим ходом
    if (pos < 0)
    {
      pos = ai::predictMove(_gField.humanSign);
      // если нет рандомно размещаем символ компьютера на поле
      if (pos < 0)
      {
        pos = ai::randomMove();
      }
    }

    _gField.cells[pos] = _gField.aiSign;
  }
}

} // namespace inner

namespace ai
{

// --------------------------------------------------------------------------------------
list<int8_t> createMoves()
{
  list<int8_t> list;
  for (size_t n {0u}; n < _gField.cells.size(); ++n)
  {
    if (Cell::EMPTY == _gField.cells.at(n))
    {
      list.push_back(n);
    }
  }
  return list;
}

// --------------------------------------------------------------------------------------
int8_t predictMove(Cell playerSign)
{
  int8_t pos {-1};
  list<int8_t> movesList = createMoves();
  while (!movesList.empty())
  {
    _gField.cells[movesList.front()] = playerSign;
    if (inner::checkWin(playerSign))
    {
      pos = movesList.front();
      _gField.cells[movesList.front()] = Cell::EMPTY;
      break;
    }
    _gField.cells[movesList.front()] = Cell::EMPTY;
    movesList.pop_front();
  }
  return pos;
}

// --------------------------------------------------------------------------------------
int8_t randomMove()
{
  list<int8_t> movesList = createMoves();
  const auto index = inner::getRandomNumber(0, movesList.size() - 1);
  return *(next(movesList.cbegin(), index));
}

} // namespace ai

} // namespace game
