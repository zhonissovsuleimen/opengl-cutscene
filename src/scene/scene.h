#pragma once

#include "../parser/parser.h"
#include "../model/model.h"
#include "camera.h"
#include "light.h"
#include <vector>
#include <string>


class Scene {
private:
  std::vector<Model> models;
  std::vector<Light> lights;
  glm::vec3 ambient;

public:
  Camera camera;

  Scene() {}
  void addModel(Model model);
  void addLight(Light light);
  void setAmbient(glm::vec3 color);

  void draw(unsigned int programId, unsigned int vao, unsigned int vbo, unsigned int tex);
};