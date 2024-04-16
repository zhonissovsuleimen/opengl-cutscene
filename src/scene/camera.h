#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

class Camera {
private:
  float fov = 90.0f;
  float time = 0.0f; // from 0.0 to 1.0 for animation

  float frustumNear = 0.1f;
  float frustumFar = 100.0f;

public:
  glm::vec3 position;
  glm::vec3 direction;
  glm::vec3 up;

  Camera();
  Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up);

  void setTime(float time);

  glm::mat4x4 getViewMatrix();
  glm::mat4x4 getProjectionMatrix();
};