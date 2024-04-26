#pragma once

#include "scene.h"
#include "../parser/parser.h"
#include "../util/definitions.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Scene::addModel(Model model) {
  models.push_back(model);
}

void Scene::addLight(Light light) {
  lights.push_back(light);
}

void Scene::setAmbient(glm::vec3 color) {
  ambient = color;
}

void Scene::draw(unsigned int programId, unsigned int vao, unsigned int vbo, unsigned int tex) {
  glUniform3fv(glGetUniformLocation(programId, "ambient"), 1, glm::value_ptr(ambient));

  glUniform1i(glGetUniformLocation(programId, "lightCount"), lights.size());
  for(int i = 0; i < lights.size(); i++) {
    std::string prefix = "lights[" + std::to_string(i) + "].";
    glUniform3fv(glGetUniformLocation(programId, (prefix + "position").c_str()), 1, glm::value_ptr(lights[i].position));
    glUniform3fv(glGetUniformLocation(programId, (prefix + "color").c_str()), 1, glm::value_ptr(lights[i].color));
    glUniform1f(glGetUniformLocation(programId, (prefix + "intensity").c_str()), lights[i].intensity);
  }

  for (Model model : models) {
    model.draw(programId, vao, vbo, tex);
  }
}
