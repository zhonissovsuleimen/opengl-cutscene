#pragma once
#include <string>
#include <vector>

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


class Parser {
  private:
    std::vector<Triangle> triangles;
    void interpolate();
  public:
  bool parse(std::string filename);
  std::vector<Triangle>& getTriangles();
}; 