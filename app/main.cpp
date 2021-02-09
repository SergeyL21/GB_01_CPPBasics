/*
 * Created by Qt Creator 4.11.0 @ 01 Feb 2021 21:21:03
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include "main_window.h"

#include <QApplication>

// ---------------------------------------------------------------------------
int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  MainWindow win;
  win.show();
  return app.exec();
}

