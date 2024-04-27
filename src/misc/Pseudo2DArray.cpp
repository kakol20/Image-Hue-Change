#include <string>

#include "Pseudo2DArray.h"

template<class T>
Pseudo2DArray<T>::Pseudo2DArray() {
  m_width = 0;
  m_height = 0;
  m_size = 0;

  delete[] m_arr;
  m_arr = nullptr;
}

template<class T>
Pseudo2DArray<T>::Pseudo2DArray(const size_t width, const size_t height) {
  m_width = width;
  m_height = height;
  m_size = width * height;

  m_arr = new T[m_size];
}

template<class T>
Pseudo2DArray<T>::Pseudo2DArray(const Pseudo2DArray<T>& other) {
  delete[] m_arr;
  m_arr = nullptr;

  m_width = other.m_width;
  m_height = other.m_height;
  m_size = m_width * m_height;

  m_arr = new T[m_size];
  memcpy(m_arr, other.m_arr, m_size);
}

template<class T>
Pseudo2DArray<T>::~Pseudo2DArray() {
  delete[] m_arr;
  m_arr = nullptr;
}

template<class T>
Pseudo2DArray<T>& Pseudo2DArray<T>::operator=(const Pseudo2DArray<T>& other) {
  if (this == &other) return *this;
  delete[] m_arr;
  m_arr = nullptr;

  m_width = other.m_width;
  m_height = other.m_height;
  m_size = m_width * m_height;

  m_arr = new T[m_size];
  memcpy(m_arr, other.m_arr, m_size);
  return *this;
}

template<class T>
T& Pseudo2DArray<T>::operator()(const size_t x, const size_t y) {
  return *(m_arr[GetIndex(x, y)]);
}

template<class T>
T Pseudo2DArray<T>::operator()(const size_t x, const size_t y) const {
  return m_arr[GetIndex(x, y)];
}

template<class T>
size_t Pseudo2DArray<T>::GetIndex(const size_t x, const size_t y) const {
  return x + (y * m_width);
}
