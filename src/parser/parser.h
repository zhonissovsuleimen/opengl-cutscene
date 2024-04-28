#pragma once
#include <string>
#include <vector>
#include "glm/vec3.hpp"

struct Vertex
{
  // coordinates
  float x;
  float y;
  float z;
  // normal
  float normal_x;
  float normal_y;
  float normal_z;
  // texture coordinates
  float u;
  float v;
};

struct Triangle
{
  Vertex v1;
  Vertex v2;
  Vertex v3;
};

struct Bezier
{
  glm::vec3 start;
  glm::vec3 control1;
  glm::vec3 control2;
  glm::vec3 end;
};

struct Light
{
  glm::vec3 position;
  glm::vec3 color;
  float intensity;
};


static class Parser {
public:
  static std::vector<Triangle> parseObj(std::string filename);
  static std::vector<Bezier> parseBezier(std::string filename);
  static std::vector<Light> parseLightCoords(std::string filename);
}; 