#pragma once

#include "../parser/parser.h"
#include <vector>
#include <string>


class Scene {
  public:
  std::vector<Triangle> triangles;

  bool load(std::string filename);
};

