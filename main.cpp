/*
 * Created by Qt Creator 4.11.0 @ 01 Feb 2021 21:21:03
 *
 * Project: GB_CppBasics
 * File: main.cpp
 *
 * Author: Sergey Lola
 */

#include <iostream>
#include <limits>

// ������ ��� �������� �������������� �� �������������� ����������
#undef unused
#define unused(x) (void)(x);

// ��������������� ������ ������������ ��� ���������� ���������� �� ������
#undef OUT
#define OUT

using namespace std;

extern int task1_A, task1_B, task1_C, task1_D;

// ---------------------------------------------------------------------------
// �������� ������� ��������� ����������� ����� � ���������� ��� ���� int
void getAndValidateInput(const string &text, int &input);

// ---------------------------------------------------------------------------
int main(int argc, const char ** argv)
{
  unused(argc)
  unused(argv)
  // -------------------------------------------------------------------------
  // ������� 2: ���� ����� �����. ���� ��� ������ ��� ����� 21, �� �������� ��
  // ����� ������� ����� ���� ������ � ������ 21. ���� �� �������� �����
  // ������, ��� 21, ���������� ������� ��������� ������� ����� ���� ������ �
  // 21. ��� ���������� ������� ������� ������������ ��������� �������� (?:).
  {
    int input;
    const int MAGIC_NUM = 21;
    cout << "--- TASK 2 ---" << endl;
    getAndValidateInput(string("Please enter an integer number: "), OUT input);

    const int diff = (input <= MAGIC_NUM) ?
                      MAGIC_NUM - input :
                      (input - MAGIC_NUM) << 1;
    cout << "Difference between your input number and " <<
            MAGIC_NUM <<
            " is: " <<
            diff <<
            endl;
  }
  // -------------------------------------------------------------------------
  // ������� 3: ������� ��������� ������������� ������, �������� 3�3�3 �
  // ��������� �� �������� ������ ������� � ��� ������ �������� �������������
  // ������� �� ����� �������� ����������� ������ ������������� ���� [1][1][1]
  {
    const int cube[3][3][3] {
      {{1, 1, 1}, {2, 4, 2}, {1, 1, 1}},
      {{2, 2, 2}, {4, 7, 4}, {2, 2, 2}},
      {{3, 3, 3}, {8, 8, 8}, {3, 3, 3}}
    };
    cout << endl << "--- TASK 3 ---" << endl;
    const int *pCube = &cube[1][1][1];
    cout << "Cube[1][1][1] = " << *pCube << endl;
  }
  // -------------------------------------------------------------------------
  // ������� 1: �������� ���������, ����������� ��������� a * (b + (c / d)) �
  // ��������� ��������� � ��������� ������, ��� a, b, c, d � �������������
  // ���������. ����������� static_cast ��� �-Style cast � float �����
  // ��������� ������ �������.
  // +
  // ������� 4: �������� ���������, ����������� ��������� �� ������� �������,
  // � ���������� ��� �� ��������� � ���������������� � ������ cpp �����.
  // ����������� extern.
  {
    cout << endl << "--- TASK 1+4 ---" << endl;
    getAndValidateInput(string("Please enter integer number A: "), OUT task1_A);
    getAndValidateInput(string("Please enter integer number B: "), OUT task1_B);
    getAndValidateInput(string("Please enter integer number C: "), OUT task1_C);
    // ����� ������������� �������� �������� �� ��, ����� ����������� d �� ���
    // ����� 0!
    do {
      getAndValidateInput(string("Please enter integer number D (other than 0): "),
                          OUT task1_D);
    } while (0 == task1_D);
    cout << "The result is: " <<
            task1_A * (task1_B + (static_cast<float>(task1_C) / task1_D)) <<
            endl;
  }
  return 0;
}

// ---------------------------------------------------------------------------
void getAndValidateInput(const string &text, int &input)
{
  bool isValid = false;   // ���������� ��� ��������� ���������� ��������
  do {
    cout << text << flush;
    cin >> input;
    isValid = cin.good();
    if (cin.fail()) {
      // ������������ ���� ������������ ��������, ���������� ���������
      // ������ �� ��������� "good"
      cin.clear();
      // � ������� ���
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } while (!isValid);
}
