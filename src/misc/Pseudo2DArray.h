#pragma once

template <class T>
class Pseudo2DArray {
public:
  Pseudo2DArray();
  Pseudo2DArray(const size_t width, const size_t heigh);
  Pseudo2DArray(const Pseudo2DArray<T>& other);
  ~Pseudo2DArray();

  Pseudo2DArray<T>& operator=(const Pseudo2DArray<T>& other);

  T& operator()(const size_t x, const size_t y);
  T operator()(const size_t x, const size_t y) const;

private:
  T* m_arr;

  size_t m_width;
  size_t m_height;
  size_t m_size;

  size_t GetIndex(const size_t x, const size_t y) const;
};