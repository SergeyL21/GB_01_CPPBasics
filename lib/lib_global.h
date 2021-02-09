/*
 * Created by Qt Creator 4.11.0 @ 08 Feb 2021 20:58:23
 *
 * Project: GB_CppBasics/lib
 * File: lib_global.h
 *
 * Author: Sergey Lola
 */

#ifdef _WIN32
# if defined(LIB_EXPORTS)
#   define DLL_LIB_EXPORT __declspec(dllexport)
# else
#   define DLL_LIB_EXPORT __declspec(dllimport)
# endif // if defined(LIB_EXPORTS)
#elif __linux__
# define DLL_LIB_EXPORT __attribute__((visibility("default")))
#else
# define DLL_LIB_EXPORT
#endif // ifndef __linux__
