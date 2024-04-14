#pragma once

#include "../parser/parser.h"
#include "../util/mat4.h"
#include "camera.h"
#include <vector>
#include <string>


class Scene {
private:
  Mat4 modelMatrix;
  Mat4 projectionMatrix;

public:
  std::vector<Triangle> triangles;
  Camera camera;

  Scene();
  bool load(std::string filename);

  Mat4 getModelMatrix() { return modelMatrix; }
  Mat4 getViewMatrix() { return camera.getViewMatrix(); }
  Mat4 getProjectionMatrix() { return projectionMatrix; }
};