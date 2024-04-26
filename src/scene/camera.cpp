#pragma once

#include "../util/definitions.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() {
  position = glm::vec3(0.0f, 0.0f, 0.0f);
  direction = glm::vec3(0.0f, 0.0f, 1.0f);
  up = glm::vec3(0.0f, 1.0f, 0.0f);
}

Camera::Camera(const std::string& path, glm::vec3 up) {
  this->up = up;
  motionPath = Parser::parseBezier(path);

  if(motionPath.size() > 0) {
    position = motionPath[0].start;
    if(motionPath.size() > 1) {
      direction = motionPath[1].start - position;
    } else {
      direction = glm::vec3(0.0f, 0.0f, 1.0f);
    }
  }
}

Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up) {
  this->position = position;
  this->direction = direction;
  this->up = up;
}

void Camera::setTime(float time) {
  if (time < 0.0f) { time = 0.0f; }
  if (time > 1.0f) { time = 1.0f; }

  this->time = time;
}

glm::mat4x4 Camera::getViewMatrix() {
  return glm::lookAt(position, direction, up);
}

glm::mat4x4 Camera::getProjectionMatrix() {
  return glm::perspective(glm::radians(fov), (float)WIDTH/HEIGHT, frustumNear, frustumFar);
}