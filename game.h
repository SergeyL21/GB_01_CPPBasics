/*
 * Created by Qt Creator 4.11.0 @ 27 Feb 2021 16:35:21
 *
 * Project: GB_CppBasics
 * File: game.h
 *
 * Author: Sergey Lola
 */
#pragma once

#include <limits.h>
#include <vector>
#include <list>

#include "common.h"

namespace game
{

// инициализация ресурсов игры
void initGame();
// очистка ресурсов игры
void closeGame();
// запустить цикл игры
void startGame();

// секция внутренних функций игры
namespace inner
{
// получение произвольного числа в заданном диапазоне
int8_t getRandomNumber(int8_t min = CHAR_MIN, int8_t max = CHAR_MAX);

// очистка игрового поля
void clearField();
// обновление игрового поля
void updateField();

// получить состояние ячейки поля по x и y
Cell getCell(int8_t x, int8_t y);
// записать состояние ячейки поля по х и у
bool setCell(int8_t x, int8_t y, Cell cell);

// запуск действий игрока в его ход
void humanTurn();
// запуск действий компьютера в его ход
void aiTurn();
// проверка на выигрыш
bool checkWin(Cell playerSign);

} // namespace inner

// секция функций отвечающих за искуственный интеллект
namespace ai
{

// формирование списка доступных (т.е. пока пустых) клеток
std::list<std::int8_t> createMoves();
// предсказание выигрышного хода
std::int8_t predictMove(Cell playerSign);
// формирование рандомного хода
std::int8_t randomMove();

} // namespace ai

} // namespace game
