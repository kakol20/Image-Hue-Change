#pragma once

#include <string>

template <class T>
class Pseudo2DArray {
public:
  Pseudo2DArray(const unsigned int width = 1, const unsigned int height = 1);
  Pseudo2DArray(const Pseudo2DArray<T>& other);
  Pseudo2DArray(T* arr, const unsigned int width, const unsigned int height);
  ~Pseudo2DArray();

  Pseudo2DArray<T>& operator=(const Pseudo2DArray<T>& other);

  T& operator()(const unsigned int x, const unsigned int y);
  T operator()(const unsigned int x, const unsigned int y) const;

  unsigned int GetWidth() const { return m_width; };
  unsigned int GetHeight() const { return m_height; };

  std::string Debug() const;

private:
  T* m_arr;

  unsigned int m_width;
  unsigned int m_height;
  size_t m_size;

  size_t GetIndex(const unsigned int x, const unsigned int y) const;
};

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(const unsigned int width, const unsigned int height) {
  m_width = width;
  m_height = height;
  m_size = size_t(width * height);

  m_arr = new T[m_size];
}

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(const Pseudo2DArray<T>& other) {
  m_width = other.m_width;
  m_height = other.m_height;
  m_size = size_t(m_width * m_height);

  m_arr = new T[m_size];

  //memcpy(m_arr, other.m_arr, m_size);
  for (size_t i = 0; i < m_size; i++) {
    m_arr[i] = other.m_arr[i];
  }
}

template<class T>
inline Pseudo2DArray<T>::Pseudo2DArray(T* arr, const unsigned int width, const unsigned int height) {
  m_width = width;
  m_height = height;
  m_size = size_t(m_width * m_height);

  m_arr = new T[m_size];

  for (size_t i = 0; i < m_size; i++) {
    m_arr[i] = arr[i];
  }
}

template<class T>
inline Pseudo2DArray<T>::~Pseudo2DArray() {
  delete[] m_arr;
  m_arr = nullptr;
}

template<class T>
inline Pseudo2DArray<T>& Pseudo2DArray<T>::operator=(const Pseudo2DArray<T>& other) {
  if (this == &other) return *this;

  {
    bool temp = true;
  }

  delete[] m_arr;
  m_arr = nullptr;

  m_width = other.m_width;
  m_height = other.m_height;
  m_size = size_t(m_width * m_height);

  m_arr = new T[m_size];

  for (size_t i = 0; i < m_size; i++) {
    m_arr[i] = other.m_arr[i];
  }
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
inline std::string Pseudo2DArray<T>::Debug() const {
  std::string out = "";
  for (unsigned int y = 0; y < m_height; y++) {
    for (unsigned int x = 0; x < m_width; x++) {
      out += std::to_string(m_arr[GetIndex(x, y)]) + " ";
    }
    out += '\n';
  }
  return out;
}

template<class T>
inline size_t Pseudo2DArray<T>::GetIndex(const unsigned int x, const unsigned int y) const {
  return size_t(x + (y * m_width));
}
