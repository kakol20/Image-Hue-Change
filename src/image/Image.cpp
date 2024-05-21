#include "Image.h"

#include <iostream>
#include <cstring>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "../../ext/stb/stb_image.h"
#include "../../ext/stb/stb_image_write.h"

#include "../misc/Log.h"

Image::Image() {
  m_h = 0;
  m_w = 0;
  m_channels = 0;
  m_size = 0;
  m_data = nullptr;
}

Image::Image(const char* file, const int forceChannels) {
  Image::Read(file, forceChannels);
}

Image::Image(const Image& other) {
  //stbi_image_free(m_data);

  m_w = other.m_w;
  m_h = other.m_h;
  m_channels = other.m_channels;
  m_size = other.m_size;

  m_data = new uint8_t[m_size];

  memcpy(m_data, other.m_data, m_size);
}

Image::Image(const int w, const int h, const int channels) {
  m_w = w;
  m_h = h;
  m_channels = channels;
  m_size = (size_t)(m_w * m_h * m_channels);

  m_data = new uint8_t[m_size];
}

Image::~Image() {
  stbi_image_free(m_data);
}

Image& Image::operator=(const Image& other) {
  if (&other == this) return *this;

  stbi_image_free(m_data);

  m_w = other.m_w;
  m_h = other.m_h;
  m_channels = other.m_channels;
  m_size = other.m_size;

  m_data = new uint8_t[m_size];

  memcpy(m_data, other.m_data, m_size);

  return *this;
}

bool Image::Read(const char* file, const int forceChannels) {
  Log::StartLine();
  if (forceChannels > 0 && forceChannels <= 4) {
    m_data = stbi_load(file, &m_w, &m_h, &m_channels, forceChannels);
  }
  else {
    m_data = stbi_load(file, &m_w, &m_h, &m_channels, 0);
  }

  if (m_data != NULL) {
    Log::Write("Read success ");
  }
  else {
    Log::Write("Read failed ");
  }

  m_size = (size_t)(m_w * m_h * m_channels);

  Log::Write(file);
  Log::EndLine();

  return m_data != NULL;
}

bool Image::Write(const char* file) {
  ImageType type = GetFileType(file);
  int success = 0;

  switch (type) {
  case Image::ImageType::PNG:
    success = stbi_write_png(file, m_w, m_h, m_channels, m_data, m_w * m_channels);
    break;
  case Image::ImageType::JPG:
    success = stbi_write_jpg(file, m_w, m_h, m_channels, m_data, 100);
    break;
  case Image::ImageType::BMP:
    success = stbi_write_bmp(file, m_w, m_h, m_channels, m_data);
    break;
  case Image::ImageType::TGA:
    success = stbi_write_tga(file, m_w, m_h, m_channels, m_data);
    break;
  case Image::ImageType::NA:
    //std::cout << "File type not supported\nPNG, JPG, BMP or TGA";
    Log::StartLine();
    Log::Write("File type not supported - PNG, JPG, BMP or TGA");
    Log::EndLine();
    success = 0;
    break;
  default:
    Log::StartLine();
    Log::Write("File type not supported - PNG, JPG, BMP or TGA");
    Log::EndLine();
    success = 0;
    break;
  }

  Log::StartLine();
  if (success != 0) {
    //std::cout << "Write success " << file << '\n';
    Log::Write("Write success ");
    Log::Write(file);
  }
  else {
    //std::cout << "Write fail " << file << '\n';
    Log::Write("Write fail ");
    Log::Write(file);
  }
  Log::EndLine();

  return success != 0;
}

size_t Image::GetIndex(const int x, const int y) const {
  if (x < 0 || x >= m_w || y < 0 || y >= m_h) return NAN;
  return size_t((x + y * m_w) * m_channels);
}

size_t Image::GetIndex_s(const int x, const int y, const int width, const int channels) {
  return size_t((x + y * width) * channels);
}

void Image::Clear() {
  for (size_t i = 0; i < m_size; i++) {
    m_data[i] = 0;
  }
}

Image::ImageType Image::GetFileType(const char* file) {
  const char* ext = strrchr(file, '.');

  if (ext != nullptr) {
    if (strcmp(ext, ".png") == 0) {
      return ImageType::PNG;
    }
    else if (strcmp(ext, ".jpg") == 0) {
      return ImageType::JPG;
    }
    else if (strcmp(ext, ".bmp") == 0) {
      return ImageType::BMP;
    }
    else if (strcmp(ext, ".tga") == 0) {
      return ImageType::TGA;
    }
  }

  return ImageType::NA;
}