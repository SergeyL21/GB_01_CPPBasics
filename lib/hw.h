/*
 * Created by Qt Creator 4.11.0 @ 08 Feb 2021 21:02:12
 *
 * Project: GB_CppBasics/lib
 * File: hw.h
 *
 * Author: Sergey Lola
 */

#pragma once

#include "lib_global.h"

#include <cstddef>
#include <string>

extern "C" {

namespace lib {

DLL_LIB_EXPORT bool task1(int numA, int numB);

DLL_LIB_EXPORT bool task2(int numA, int numB);

DLL_LIB_EXPORT void task3(int min, int max, std::string &res);

DLL_LIB_EXPORT bool task4(int num);

DLL_LIB_EXPORT bool task5(int year);

} // namespace lib

} // extern "C"
