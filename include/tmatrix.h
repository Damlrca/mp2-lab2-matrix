// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

constexpr size_t MAX_VECTOR_SIZE = 100000000;
constexpr size_t MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  explicit TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw length_error("TDynamicVector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw length_error("TDynamicVector size shouldn't be greater than MAX_VECTOR_SIZE");
    pMem = new T[sz]{}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(sz != 0 && "TDynamicVector size should be greater than zero");
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::uninitialized_copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
    pMem = new T[sz];
    std::uninitialized_copy(v.pMem, v.pMem + sz, pMem);
  }

  TDynamicVector(TDynamicVector&& v) noexcept
  {
    sz = 0;
    pMem = nullptr;
    swap(*this, v);
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
        return *this;

    if (sz != v.sz) {
        delete[] pMem;
        sz = v.sz;
        pMem = new T[sz];
        std::uninitialized_copy(v.pMem, v.pMem + sz, pMem);
    }
    else {
        std::copy(v.pMem, v.pMem + sz, pMem);
    }

    return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    swap(*this, v);
    return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz)
          throw out_of_range{"Wrong TDynamicVector index"};
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz)
          throw out_of_range{ "Wrong TDynamicVector index" };
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this == &v) 
          return true;
      if (sz != v.sz)
          return false;
      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i])
              return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector t(*this);
      for (size_t i = 0; i < sz; i++)
          t.pMem[i] += val;
      return t;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector t(*this);
      for (size_t i = 0; i < sz; i++)
          t.pMem[i] -= val;
      return t;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector t(*this);
      for (size_t i = 0; i < sz; i++)
          t.pMem[i] *= val;
      return t;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw length_error{ "TDynamicVectors should have equal size" };
      TDynamicVector t(*this);
      for (size_t i = 0; i < sz; i++)
          t.pMem[i] = t.pMem[i] + v.pMem[i];
      return t;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw length_error{ "TDynamicVectors should have equal size" };
      TDynamicVector t(*this);
      for (size_t i = 0; i < t.sz; i++)
          t.pMem[i] = t.pMem[i] - v.pMem[i];
      return t;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz)
          throw length_error{ "TDynamicVectors should have equal size" };
      T t{};
      for (size_t i = 0; i < sz; i++)
          t += this->pMem[i] * v.pMem[i];
      return t;
  }

  friend void swap(TDynamicVector& l, TDynamicVector& r) noexcept
  {
    std::swap(l.sz, r.sz);
    std::swap(l.pMem, r.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz >= MAX_MATRIX_SIZE)
        throw length_error("TDynamicMatrix size shouldn't be greater than MAX_MATRIX_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& m) : TDynamicVector<TDynamicVector<T>>(m) {}

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;
  using TDynamicVector<TDynamicVector<T>>::at;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      return TDynamicVector<TDynamicVector<T>>::operator*(val);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.sz)
          throw length_error{ "TDynamicMatrix and TDynamicVector should have equal size" };

      TDynamicVector<T> t(sz);
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++)
              t[i] += pMem[i][j] * v[i];

      return t;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      return TDynamicVector<TDynamicVector<T>>::operator+(m);
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      return TDynamicVector<TDynamicVector<T>>::operator-(m);
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != v.sz)
          throw length_error{ "TDynamicMatrixs should have equal size" };
      
      TDynamicMatrix t(sz);
      TDynamicVector v(sz);

      for (size_t j = 0; j < sz; j++) {
          for (size_t i = 0; i < sz; i++)
              v[i] = m[i][j];
          for (size_t i = 0; i < sz; i++)
              t[i][j] = pMem[i] * v;
      }

      return t;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          istr >> v[i];
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
          ostr << v[i] << "\n";
      return ostr;
  }
};

#endif
