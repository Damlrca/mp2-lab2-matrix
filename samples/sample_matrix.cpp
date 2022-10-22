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
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класс работы с матрицами." << endl << endl;
  
  {
	  cout << "Умножение матриц:" << endl << endl;
	  int A[3][3] = { {2,3,4},{4,5,1},{5,5,3} };
	  int B[3][3] = { {14,-3,1},{1,5,0},{5,-10,4} };
	  TDynamicMatrix<int> a(3), b(3), c;
	  for (int i = 0; i < 3; i++)
		  for (int j = 0; j < 3; j++) {
			  a[i][j] = A[i][j];
			  b[i][j] = B[i][j];
		  }
	  c = a * b;
	  cout << "Matrix a = " << endl << a << endl;
	  cout << "Matrix b = " << endl << b << endl;
	  cout << "Matrix c = a + b" << endl << c << endl;
  }

  {
	  cout << "Умножение матрицы на вектор:" << endl << endl;

	  TDynamicMatrix<int> m(4);
	  for (int i = 0; i < 4; i++)
		  for (int j = 0; j < 4; j++)
			  m[i][j] = rand() % 23 - 11;
	  TDynamicVector<int> v(4);
	  for (int i = 0; i < 4; i++)
		  v[i] = rand() % 19 - 9;
	  TDynamicVector<int> t = m * v;

	  cout << "Matrix m = " << endl << m << endl;
	  cout << "Vector v = " << endl << v << endl << endl;
	  cout << "Vector t = m * v" << endl << t << endl << endl;
  }

  {
	  cout << "Умножение матрицы на скаляр:" << endl << endl;

	  TDynamicMatrix<int> m(3);
	  for (int i = 0; i < 3; i++)
		  for (int j = 0; j < 3; j++)
			  m[i][j] = rand() % 23 - 11;
	  int u = 3;
	  TDynamicMatrix<int> t = m * u;
	  cout << "Matrix m = " << endl << m << endl;
	  cout << "int u = " << u << endl << endl;
	  cout << "Matrix t = m * u" << endl << t << endl << endl;
  }
}
//---------------------------------------------------------------------------
