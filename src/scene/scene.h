#pragma once

#include "../parser/parser.h"
#include "../model/model.h"
#include "camera.h"
#include <vector>
#include <string>


class Scene {
public:
  std::vector<Model> models;
  Camera camera;

  Scene() {}
  void addModel(Model model);
  void draw(unsigned int programId, unsigned int vao, unsigned int vbo, unsigned int tex);
};