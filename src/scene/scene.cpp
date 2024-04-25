#pragma once

#include "scene.h"
#include "../parser/parser.h"
#include "../util/definitions.h"
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void Scene::addModel(Model model) {
  models.push_back(model);
}

void Scene::draw(unsigned int programId, unsigned int vao, unsigned int vbo, unsigned int tex) {
  for (Model model : models) {
    model.draw(programId, vao, vbo, tex);
  }
}