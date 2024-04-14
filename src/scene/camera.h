#pragma once

#include "../util/vect.h"
#include "../util/mat4.h"

class Camera {
private:
  float focalLength;
  float time; // from 0.0 to 1.0 for animation

public:
  Vect position;
  Vect direction;
  Vect up;

  Camera();
  Camera(Vect position, Vect direction, Vect up);

  void setTime(float time);
  void setFocalLength(float focalLength) { this->focalLength = focalLength; }

  Mat4 getViewMatrix();
};