#pragma once

#include "scene.h"
#include "../parser/parser.h"
#include "../util/vect.h"
#include "../util/mat4.h"
#include <iostream>

Scene::Scene() {
  modelMatrix = Mat4::identity();

  //canonical view volume
  float l = -1.0f;
  float r = 1.0f;
  float t = 1.0f;
  float b = -1.0f;
  float n = 0.1f;
  float f = 100.0f;

  float projectionArr[16] = {
    2*n/(r-l), 0.0f, (r+l)/(r-l), 0.0f,
    0.0f, 2*n/(t-b), (t+b)/(t-b), 0.0f,
    0.0f, 0.0f, (n+f)/(n-f), 2*f*n/(n-f),
    0.0f, 0.0f, -1.0f, 0.0f
  };
  projectionMatrix = Mat4(projectionArr);
}

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