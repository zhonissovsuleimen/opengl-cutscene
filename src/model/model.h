#pragma once
#include "../parser/parser.h"
#include "texture.h"
#include "glm/mat4x4.hpp"
#include <vector>
#include <string>

class Model {
private:
  std::string path;
  glm::mat4x4 modelMatrix;
  std::vector<Triangle> triangles;
  Texture *texture;
  bool hasTexture;

public:
  Model() = default;
  Model(const std::string& path);
  Model(const std::string& path, unsigned int vao, unsigned int vbo, unsigned int tex);
  ~Model();

  void setTexture(Texture* texture);
  void bind(unsigned int vao, unsigned int vbo, unsigned int tex) const;
  void unbind() const;
  void draw(unsigned int programId, unsigned int vao, unsigned int vbo, unsigned int tex) const;
};