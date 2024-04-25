#pragma once

#include <string>

class Texture {
public:
  bool success = false;
private:
  std::string path;
  unsigned char* buffer;
  int width, height, bpp; // bpp = bits per pixel

  void configure();
public:
  Texture(const std::string& path);
  ~Texture();

  void bind(unsigned int slot, unsigned int tex) const;
  void unbind() const;
};