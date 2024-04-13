#pragma once

#include "../parser/parser.h"
#include "../util/mat4.h"
#include <vector>
#include <string>


class Scene {
  public:
  Mat4 modelMatrix;
  Mat4 viewMatrix;
  Mat4 projectionMatrix;
  std::vector<Triangle> triangles;

  Scene();
  bool load(std::string filename);
};

