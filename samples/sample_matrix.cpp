// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  int A[3][3] = { {2,3,4},{4,5,1},{5,5,3} };
  int B[3][3] = { {14,-3,1},{1,5,0},{5,-10,4} };
  TDynamicMatrix<int> a(3), b(3), c(3);
  int i, j;
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами" << endl;
  for (i = 0; i < 3; i++)
	  for (j = 0; j < 3; j++) {
		  a[i][j] = A[i][j];
		  b[i][j] = B[i][j];
	  }
  c = a * b;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;
}
//---------------------------------------------------------------------------
