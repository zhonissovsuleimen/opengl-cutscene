#pragma once
#include "mat4.h"

Mat4::Mat4() {
  for (int i = 0; i < 16; i++) {
    data[i] = 0;
  }
}

Mat4::Mat4(float arr[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      data[i * 4 + j] = arr[i][j];
    }
  }
}

Mat4::Mat4(float arr[16]) {
  for (int i = 0; i < 16; i++) {
    data[i] = arr[i];
  }
}

Mat4::Mat4(const Mat4& other) {
  for (int i = 0; i < 16; i++) {
    data[i] = other.data[i];
  }
}

Mat4 Mat4::add(const Mat4& other) const {
  Mat4 result;
  for (int i = 0; i < 16; i++) {
    result.data[i] = data[i] + other.data[i];
  }
  return result;
}

Mat4 Mat4::subtract(const Mat4& other) const {
  Mat4 result;
  for (int i = 0; i < 16; i++) {
    result.data[i] = data[i] - other.data[i];
  }
  return result;
}

Mat4 Mat4::multiply(const Mat4& other) const {
  Mat4 result;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
        result.data[i * 4 + j] += data[i * 4 + k] * other.data[k * 4 + j];
      }
    }
  }
  return result;
}

Mat4 Mat4::identity() {
  float arr[16] = {1, 0, 0, 0,
                   0, 1, 0, 0,
                   0, 0, 1, 0,
                   0, 0, 0, 1};
  return Mat4(arr);
}

float Mat4::det() const {
  return data[0] * (data[5] * (data[10] * data[15] - data[11] * data[14]) - data[6] * (data[9] * data[15] - data[11] * data[13]) + data[7] * (data[9] * data[14] - data[10] * data[13])) -
         data[1] * (data[4] * (data[10] * data[15] - data[11] * data[14]) - data[6] * (data[8] * data[15] - data[11] * data[12]) + data[7] * (data[8] * data[14] - data[10] * data[12])) +
         data[2] * (data[4] * (data[9] * data[15] - data[11] * data[13]) - data[5] * (data[8] * data[15] - data[11] * data[12]) + data[7] * (data[8] * data[13] - data[9] * data[12])) -
         data[3] * (data[4] * (data[9] * data[14] - data[10] * data[13]) - data[5] * (data[8] * data[14] - data[10] * data[12]) + data[6] * (data[8] * data[13] - data[9] * data[12]));
}

Mat4 Mat4::lookAt(Vect position, Vect direction, Vect up) {
  Vect f = direction.normalize();
  Vect r = up.cross(f).normalize();
  Vect u = f.cross(r).normalize();

  float arr[16] = {
    r.x, r.y, r.z, -r * position,
    u.x, u.y, u.z, -u * position,
    -f.x, -f.y, -f.z, f * position,
    0.0f, 0.0f, 0.0f, 1.0f
  };

  return Mat4(arr);
}

Mat4 operator*(const Mat4& mat, float scalar) {
  Mat4 result;
  for (int i = 0; i < 16; i++) {
    result.data[i] = mat.data[i] * scalar;
  }
  return result;
}



