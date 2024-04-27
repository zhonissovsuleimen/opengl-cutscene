#pragma once

#include "../util/definitions.h"
#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

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

glm::vec3 getDeCasteljauPoint(Bezier& bezier, float t) {
  std::vector<glm::vec3> points = {bezier.start, bezier.control1, bezier.control2, bezier.end};
  while (points.size() > 1) {
    std::vector<glm::vec3> newPoints;
    for (int i = 0; i < points.size() - 1; i++) {
      newPoints.push_back(points[i] * (1 - t) + points[i + 1] * t);
    }
    points = newPoints;
  }
  return points[0];
}

void Camera::animate(float t) {
  if (motionPath.size() == 0 || t > 1.0f || t < 0.0f) { return; }

  int ibezier = (t * motionPath.size());
  float miniT = t * motionPath.size() - ibezier;
  position = getDeCasteljauPoint(motionPath[ibezier], miniT);

  float nextT = t + 0.01f;
  if (nextT > 1.0f) { return; }

  ibezier = (nextT * motionPath.size());
  miniT = nextT * motionPath.size() - ibezier;
  direction = getDeCasteljauPoint(motionPath[ibezier], miniT) - position;
}

glm::mat4x4 Camera::getViewMatrix() {
  return glm::lookAt(position, position + direction, up);
}

glm::mat4x4 Camera::getProjectionMatrix() {
  return glm::perspective(glm::radians(fov), (float)WIDTH/HEIGHT, frustumNear, frustumFar);
}