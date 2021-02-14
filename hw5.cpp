// hw5.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "hw5.h"

#include "base.h"

#define MAX_LOADSTRING 100

// -------------------------------------------------------------------------------------
// Global Variables:
HINSTANCE g_hInst;                              // current instance
HWND g_hInfoWnd;								// current info section window instance
HWND g_hOutputWnd;								// current output window instance
HWND g_hButtonTask1;							// current button "Task 1" instance
HWND g_hButtonTask2;							// current button "Task 2" instance
HWND g_hButtonTask3;							// current button "Task 3" instance
HWND g_hButtonTask4;							// current button "Task 4" instance
HWND g_hButtonTask5;							// current button "Task 5" instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

const std::string WIN32_ENDL{ "\r\n" };

// -------------------------------------------------------------------------------------
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// -------------------------------------------------------------------------------------
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HW5, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HW5));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

// -------------------------------------------------------------------------------------
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HW5));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HW5);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return ::RegisterClassExW(&wcex);
}

// -------------------------------------------------------------------------------------
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // initialization text output windows
   g_hInfoWnd = CreateWindowW(TEXT("STATIC"), TEXT(""), 
	   WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 10, 1000, 200, hWnd, nullptr, g_hInst, nullptr);
   g_hOutputWnd = CreateWindowW(TEXT("STATIC"), TEXT(""),
	   WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 215, 1000, 200, hWnd, nullptr, g_hInst, nullptr);
   if (!g_hOutputWnd || !g_hInfoWnd) 
   {
	   return FALSE;
   }

   // initialization all buttons
   g_hButtonTask1 = CreateWindowW(TEXT("BUTTON"), TEXT("TASK 1"),
	   WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON, 10, 10, 100, 25, hWnd, (HMENU) IDC_TASK1, g_hInst, nullptr);
   g_hButtonTask2 = CreateWindowW(TEXT("BUTTON"), TEXT("TASK 2"),
	   WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON, 10, 40, 100, 25, hWnd, (HMENU) IDC_TASK2, g_hInst, nullptr);
   g_hButtonTask3 = CreateWindowW(TEXT("BUTTON"), TEXT("TASK 3"),
	   WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON, 10, 70, 100, 25, hWnd, (HMENU) IDC_TASK3, g_hInst, nullptr);
   g_hButtonTask4 = CreateWindowW(TEXT("BUTTON"), TEXT("TASK 4"),
	   WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON, 10, 100, 100, 25, hWnd, (HMENU) IDC_TASK4, g_hInst, nullptr);
   g_hButtonTask5 = CreateWindowW(TEXT("BUTTON"), TEXT("TASK 5"),
	   WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON, 10, 130, 100, 25, hWnd, (HMENU) IDC_TASK5, g_hInst, nullptr);
   if (!g_hButtonTask1 || !g_hButtonTask2 || !g_hButtonTask3 || !g_hButtonTask4 || !g_hButtonTask5)
   {
	   return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

// -------------------------------------------------------------------------------------
VOID PrintInfoText(int id) 
{
	switch (id) 
	{
	case IDC_TASK1:
		SetWindowTextW(g_hInfoWnd, TEXT(
			"Написать функцию которая выводит массив double чисел на экран. "
			"Параметры функции это сам массив и его размер. Вызвать эту функцию из main."
		));
		break;
	case IDC_TASK2:
		SetWindowTextW(g_hInfoWnd, TEXT(
			"Задать целочисленный массив, состоящий из элементов 0 и 1. Например: "
			"[1, 1, 0, 0, 1, 0, 1, 1, 0, 0]. Написать функцию, заменяющую в принятом массиве "
			"0 на 1, 1 на 0. Выводить на экран массив до изменений и после.\r\n\r\n"
			"ПРИМЕЧАНИЕ: изначательный массив изменяется каждый раз по нажатию кнопки \"TASK 2\". "
			"Обновление раз в секунду."
		));
		break;
	case IDC_TASK3:
		SetWindowTextW(g_hInfoWnd, TEXT(
			"Задать пустой целочисленный массив размером 8. Написать функцию, которая с помощью "
			"цикла заполнит его значениями 1, 4, 7, 10, 13, 16, 19, 22 (объявить второй массив с "
			"этими числами внутри функции). Копировать его в цикле в принятый массив (параметр "
			"функции)."
		));
		break;
	case IDC_TASK4:
		SetWindowTextW(g_hInfoWnd, TEXT(
			"Написать функцию, которой на вход подается одномерный массив и число n (может быть "
			"положительным или отрицательным), при этом метод должен циклически сместить все "
			"элементы массива на n позиций)."
		));
		break;
	case IDC_TASK5:
		SetWindowTextW(g_hInfoWnd, TEXT(
			"Написать метод, в который передается не пустой одномерный целочисленный массив, "
			"метод должен вернуть истину если в массиве есть место, в котором сумма левой и "
			"правой части массива равны. Примеры: checkBalance([1, 1, 1, || 2, 1) -> true, "
			"checkBalance([2, 1, 1, 2, 1) -> false, checkBalance([10, || 1, 2, 3, 4) -> true. "
			"Абстрактная граница показана символами ||, эти символы в массив не входят."
		));
	}
}

// -------------------------------------------------------------------------------------
VOID ExecTasks(int id) 
{
	PrintInfoText(id);
	std::string text;
	switch (id)
	{
	case IDC_TASK1:
	{
		const float arr[]{ 0.1f, 0.2f, 0.123f };
		text.append(base::arrayToString(arr, std::string{ "Array: " }, WIN32_ENDL));
		break;
	}
	case IDC_TASK2:
	{
		const std::size_t ARR_SIZE{ 10u };
		int arr[ARR_SIZE];
		base::inner::fillArray(arr);

		text.append(base::arrayToString(arr, std::string{ "Array before : " }, WIN32_ENDL));
		base::inverseArrayValues(arr);
		text.append(base::arrayToString(arr, std::string{ "Array after    : " }, WIN32_ENDL));
		break;
	}
	case IDC_TASK3:
	{
		const std::size_t ARR_SIZE{ 8u };
		int arr[ARR_SIZE];
		base::copyArray(arr);
		text = base::arrayToString(arr, std::string{ "Result: " }, WIN32_ENDL);
		break;
	}
	case IDC_TASK4:
	{
		int arr[]{ 1, 2, 3, 4, 5 };
		text.append(base::arrayToString(arr, std::string{ "Origin array: " }, WIN32_ENDL));
		base::rotateArray(arr, 1);
		text.append(base::arrayToString(arr, std::string{ "Rotate left 1: " }, WIN32_ENDL));
		// возвращаем массив в исходное положение
		base::rotateArray(arr, -1);
		base::rotateArray(arr, 3);
		text.append(base::arrayToString(arr, std::string{ "Rotate left 3: " }, WIN32_ENDL));
		// возвращаем массив в исходное положение
		base::rotateArray(arr, -3);
		base::rotateArray(arr, -1);
		text.append(base::arrayToString(arr, std::string{ "Rotate right 1: " }, WIN32_ENDL));
		// возвращаем массив в исходное положение
		base::rotateArray(arr, 1);
		base::rotateArray(arr, -3);
		text.append(base::arrayToString(arr, std::string{ "Rotate right 3: " }, WIN32_ENDL));
		break;
	}
	case IDC_TASK5:
	{
		const std::string TRUE_STR{ " = true" };
		const std::string FALSE_STR{ " = false" };
		int arr1[]{ 1, 1, 1, 2, 1 };
		int arr2[]{ 2, 1, 1, 2, 1 };
		int arr3[]{ 10, 1, 2, 3, 4 };
		int arr4[]{ 5, 4, 3, 4, 2, 8, 1};
		int arr5[]{ 13, 13 };

		// первый массив
		bool res = base::checkBalance(arr1);
		text.append(base::arrayToString(arr1, std::string{ "Array 1: " }, res ? TRUE_STR : FALSE_STR));
		text.append(WIN32_ENDL);
		// второй массив
		res = base::checkBalance(arr2);
		text.append(base::arrayToString(arr2, std::string{ "Array 2: " }, res ? TRUE_STR : FALSE_STR));
		text.append(WIN32_ENDL);
		// третий массив
		res = base::checkBalance(arr3);
		text.append(base::arrayToString(arr3, std::string{ "Array 3: " }, res ? TRUE_STR : FALSE_STR));
		text.append(WIN32_ENDL);
		// четвертый массив
		res = base::checkBalance(arr4);
		text.append(base::arrayToString(arr4, std::string{ "Array 4: " }, res ? TRUE_STR : FALSE_STR));
		text.append(WIN32_ENDL);
		// пятый массив
		res = base::checkBalance(arr5);
		text.append(base::arrayToString(arr5, std::string{ "Array 5: " }, res ? TRUE_STR : FALSE_STR));
		text.append(WIN32_ENDL);
	}
	}
	SetWindowTextW(g_hOutputWnd, S2WS(text).c_str());
}

// -------------------------------------------------------------------------------------
// free all global resources
VOID FreeGlobalResources() 
{
	DestroyWindow(g_hInfoWnd);
	DestroyWindow(g_hOutputWnd);
	DestroyWindow(g_hButtonTask1);
	DestroyWindow(g_hButtonTask2);
	DestroyWindow(g_hButtonTask3);
	DestroyWindow(g_hButtonTask4);
	DestroyWindow(g_hButtonTask5);
}

// -------------------------------------------------------------------------------------
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case IDC_TASK1:
			case IDC_TASK2:
			case IDC_TASK3:
			case IDC_TASK4:
			case IDC_TASK5:
				ExecTasks(wmId);
				break;
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
				FreeGlobalResources();
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// -------------------------------------------------------------------------------------
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
