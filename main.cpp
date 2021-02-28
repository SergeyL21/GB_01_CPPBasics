/*
 * Created by Qt Creator 4.11.0 @ 17 Feb 2021 12:34:22
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include "game.h"

#include <locale>

// ---------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  UNUSED(argc)
  UNUSED(argv)

  // setlocale(LC_ALL, "en_US.UTF-8");

  game::initGame();
  game::startGame();
  game::closeGame();

  return 0;
}
