#pragma once

#include "scene.h"
#include "../parser/parser.h"
#include "../util/definitions.h"
#include <iostream>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

bool Scene::load(std::string filename) {
  Parser parser;
  if (!parser.parse(filename)) { return false; }

  triangles = parser.getTriangles();
  if(triangles.size() == 0) {
    std::cerr << "File contains no triangles" << std::endl;  
    return false;
  }

  return true;
}