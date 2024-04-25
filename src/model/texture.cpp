#include "texture.h"
#include "../util/stb/stb_image.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Texture::configure(){
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
}

Texture::Texture(const std::string& path) : path(path), buffer(nullptr), width(0), height(0), bpp(0) {
  configure();

  stbi_set_flip_vertically_on_load(true); // opengl expects y=0.0 to be the bottom
  buffer = stbi_load(path.c_str(), &width, &height, &bpp, 4); //rgba = 4 channels 

  if (buffer) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
    // glGenerateMipmap(GL_TEXTURE_2D);
    success = true;
    stbi_image_free(buffer); //freeing the buffer after binding
  }
}

Texture::~Texture() {
  // glDeleteTextures(1, &tex);
}

void Texture::bind(unsigned int slot, unsigned int tex) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, tex);
}

void Texture::unbind() const {
  glBindTexture(GL_TEXTURE_2D, 0);
}