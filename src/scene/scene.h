#pragma once

#include "../parser/parser.h"
#include "camera.h"
#include <vector>
#include <string>


class Scene {

public:
  std::vector<Triangle> triangles;
  Camera camera;

  Scene() {}
  bool load(std::string filename);
};