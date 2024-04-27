#pragma once

#include <string>

template <class T>
class Pseudo2DArray {
public:
  Pseudo2DArray();
  Pseudo2DArray(const unsigned int width, const unsigned int height);
  Pseudo2DArray(const Pseudo2DArray<T>& other);
  ~Pseudo2DArray();

  Pseudo2DArray<T>& operator=(const Pseudo2DArray<T>& other);

  T& operator()(const unsigned int x, const unsigned int y);
  T operator()(const unsigned int x, const unsigned int y) const;

private:
  T* m_arr;

  unsigned int m_width;
  unsigned int m_height;
  size_t m_size;

  size_t GetIndex(const unsigned int x, const unsigned int y) const;
};

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray() {
  m_width = 0;
  m_height = 0;
  m_size = 0;
}

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(const unsigned int width, const unsigned int height) {
  m_width = width;
  m_height = height;
  m_size = size_t(width * height);

  m_arr = new T[m_size];
}

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(const Pseudo2DArray<T>& other) {
  /*delete[] m_arr;
  m_arr = nullptr;*/

  m_width = other.m_width;
  m_height = other.m_height;
  m_size = size_t(m_width * m_height);

  m_arr = new T[m_size];

  memcpy(m_arr, other.m_arr, m_size);
}

template<class T>
inline Pseudo2DArray<T>::~Pseudo2DArray() {
  delete[] m_arr;
  m_arr = nullptr;
}

template<class T>
inline Pseudo2DArray<T>& Pseudo2DArray<T>::operator=(const Pseudo2DArray<T>& other) {
  if (this == &other) return *this;

  delete[] m_arr;
  m_arr = nullptr;

  m_width = other.m_width;
  m_height = other.m_height;
  m_size = size_t(m_width * m_height);

  m_arr = new T[m_size];

  memcpy(m_arr, other.m_arr, m_size);
  return *this;
}

template<class T>
inline T& Pseudo2DArray<T>::operator()(const unsigned int x, const unsigned int y) {
  return m_arr[GetIndex(x, y)];
}

template<class T>
inline T Pseudo2DArray<T>::operator()(const unsigned int x, const unsigned int y) const {
  return m_arr[GetIndex(x, y)];
}

template<class T>
inline size_t Pseudo2DArray<T>::GetIndex(const unsigned int x, const unsigned int y) const {
  return size_t(x + (y * m_width));
}
