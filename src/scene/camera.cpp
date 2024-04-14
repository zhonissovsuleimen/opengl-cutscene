#pragma once

#include "camera.h"

Camera::Camera() {
  position = Vect(0.0f, 0.0f, 0.0f);
  direction = Vect(0.0f, 0.0f, 1.0f);
  up = Vect(0.0f, 1.0f, 0.0f);
  focalLength = 1.2f;
  time = 0.0f;
}

Camera::Camera(Vect position, Vect direction, Vect up) {
  this->position = position;
  this->direction = direction;
  this->up = up;
  focalLength = 1.2f;
  time = 0.0f;
}

void Camera::setTime(float time) {
  if (time < 0.0f) { time = 0.0f; }
  if (time > 1.0f) { time = 1.0f; }

  this->time = time;
}

Mat4 Camera::getViewMatrix() {
  return Mat4::lookAt(position, direction, up);
}