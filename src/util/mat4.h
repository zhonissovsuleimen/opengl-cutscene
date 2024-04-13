#pragma once
#include "vect.h"

class Mat4 {
public:
  float data[16];

  Mat4(); 
  Mat4(float arr[4][4]); 
  Mat4(float arr[16]);
  Mat4(const Mat4& other);

  Mat4 add(const Mat4& other) const;
  Mat4 subtract(const Mat4& other) const;
  Mat4 multiply(const Mat4& other) const;
  float det() const;
  static Mat4 identity();
  static Mat4 lookAt(Vect position, Vect direction, Vect up);

  Mat4 operator+(const Mat4& other) const { return add(other); }
  Mat4 operator-(const Mat4& other) const { return subtract(other); }
  Mat4 operator*(const Mat4& other) const { return multiply(other); }
};
// multiply and divide by float value
Mat4 operator*(const Mat4& mat, float scalar);
Mat4 operator/(const Mat4& mat, float scalar);