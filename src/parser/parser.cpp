#pragma once

#include "parser.h"
#include <iostream>
#include <fstream>

bool isObjectDefinition(const std::string& line){
  return line.length() >= 2 && line[0] == 'o' && line[1] == ' ';
}

bool isVertexDefinition(const std::string& line){
  return line.length() >= 2 && line[0] == 'v' && line[1] == ' ';
}

bool isNormalDefinition(const std::string& line){
  return line.length() >= 2 && line[0] == 'v' && line[1] == 'n';
}

bool isTextureDefinition(const std::string& line){
  return line.length() >= 2 && line[0] == 'v' && line[1] == 't';
}

bool isFaceDefinition(const std::string& line){
  return line.length() >= 2 && line[0] == 'f' && line[1] == ' ';
}

void fillVertexCords(const std::string& line, float& x, float& y, float& z){
  std::string cords = line.substr(1);
  cords = cords.substr(cords.find_first_not_of(' '));

  std::string xStr = cords.substr(0, cords.find(' '));
  x = std::stof(xStr);
  cords = cords.substr(cords.find(' '));
  cords = cords.substr(cords.find_first_not_of(' '));

  std::string yStr = cords.substr(0, cords.find(' '));
  y = std::stof(yStr);
  cords = cords.substr(cords.find(' '));
  cords = cords.substr(cords.find_first_not_of(' '));

  z = std::stof(cords);
}

void fillNormalCords(const std::string& line, float& x, float& y, float& z){
  std::string cords = line.substr(2);
  cords = cords.substr(cords.find_first_not_of(' '));

  std::string xCords = cords.substr(0, cords.find(' '));
  x = std::stof(xCords);
  cords = cords.substr(cords.find(' '));
  cords = cords.substr(cords.find_first_not_of(' '));

  std::string yCords = cords.substr(0, cords.find(' '));
  y = std::stof(yCords);
  cords = cords.substr(cords.find(' '));
  cords = cords.substr(cords.find_first_not_of(' '));

  z = std::stof(cords);
}

void fillTextureCords(const std::string& line, float& u, float& v){
  std::string cords = line.substr(2);
  cords = cords.substr(cords.find_first_not_of(' '));

  std::string uStr = cords.substr(0, cords.find(' '));
  u = std::stof(uStr);
  cords = cords.substr(cords.find(' '));
  cords = cords.substr(cords.find_first_not_of(' '));

  v = std::stof(cords);
}

void fillCountInfo(std::ifstream& fileStream, unsigned int& vCount, unsigned int& vtCount, unsigned int& vnCount){
  fileStream.clear();
  fileStream.seekg(0);

  std::string line;
  while (std::getline(fileStream, line)) {
    if (isVertexDefinition(line)) {
      vCount++;
    } else if (isTextureDefinition(line)) {
      vtCount++;
    } else if (isNormalDefinition(line)) {
      vnCount++;
    }
  }
}

void fillTriangles(const std::string& line, const std::vector<std::vector<float>>& vCache, const std::vector<std::vector<float>>& vnCache, const std::vector<std::vector<float>>& vtCache,  Triangle& t1, bool& isQuad, Triangle& t2){
  int v1, vt1, vn1;
  int v2, vt2, vn2;
  int v3, vt3, vn3;
  int v4, vt4, vn4;

  std::string cords = line.substr(1);
  cords = cords.substr(cords.find_first_not_of(' '));
  v1 = std::stoi(cords.substr(0, cords.find('/')));
  cords = cords.substr(cords.find('/') + 1);
  vt1 = std::stoi(cords.substr(0, cords.find('/')));
  cords = cords.substr(cords.find('/') + 1);
  vn1 = std::stoi(cords.substr(0, cords.find(' ')));            
  cords = cords.substr(cords.find(' ') + 1);

  cords = cords.substr(cords.find_first_not_of(' '));
  v2 = std::stoi(cords.substr(0, cords.find('/')));
  cords = cords.substr(cords.find('/') + 1);
  vt2 = std::stoi(cords.substr(0, cords.find('/')));
  cords = cords.substr(cords.find('/') + 1);
  vn2 = std::stoi(cords.substr(0, cords.find(' ')));
  cords = cords.substr(cords.find(' ') + 1);

  cords = cords.substr(cords.find_first_not_of(' '));
  v3 = std::stoi(cords.substr(0, cords.find('/')));
  cords = cords.substr(cords.find('/') + 1);
  vt3 = std::stoi(cords.substr(0, cords.find('/')));
  cords = cords.substr(cords.find('/') + 1);
  vn3 = std::stoi(cords.substr(0, cords.find(' ')));
  
  t1 = {
    Vertex {
      vCache[v1 - 1][0],
      vCache[v1 - 1][1],
      vCache[v1 - 1][2],
      vnCache[vn1 - 1][0],
      vnCache[vn1 - 1][1],
      vnCache[vn1 - 1][2],
      vtCache[vt1 - 1][0],
      vtCache[vt1 - 1][1]
    },
    Vertex {
      vCache[v2 - 1][0],
      vCache[v2 - 1][1],
      vCache[v2 - 1][2],
      vnCache[vn2 - 1][0],
      vnCache[vn2 - 1][1],
      vnCache[vn2 - 1][2],
      vtCache[vt2 - 1][0],
      vtCache[vt2 - 1][1]
    },
    Vertex {
      vCache[v3 - 1][0],
      vCache[v3 - 1][1],
      vCache[v3 - 1][2],
      vnCache[vn3 - 1][0],
      vnCache[vn3 - 1][1],
      vnCache[vn3 - 1][2],
      vtCache[vt3 - 1][0],
      vtCache[vt3 - 1][1]
    }
  };

  int erase = 0;
  int copy = vn3;
  while (copy > 0) {
    copy /= 10;
    erase++;
  }

  cords = cords.erase(0, erase);            
  if (cords.length() > 0 && cords.find_first_not_of(' ') != std::string::npos) {
    isQuad = true;
    cords = cords.substr(cords.find_first_not_of(' '));
    v4 = std::stoi(cords.substr(0, cords.find('/')));
    cords = cords.substr(cords.find('/') + 1);
    vt4 = std::stoi(cords.substr(0, cords.find('/')));
    cords = cords.substr(cords.find('/') + 1);
    vn4 = std::stoi(cords.substr(0, cords.find(' ')));

    t2 = {
      Vertex {
        vCache[v1 - 1][0],
        vCache[v1 - 1][1],
        vCache[v1 - 1][2],
        vnCache[vn1 - 1][0],
        vnCache[vn1 - 1][1],
        vnCache[vn1 - 1][2],
        vtCache[vt1 - 1][0],
        vtCache[vt1 - 1][1]
      },
      Vertex {
        vCache[v3 - 1][0],
        vCache[v3 - 1][1],
        vCache[v3 - 1][2],
        vnCache[vn3 - 1][0],
        vnCache[vn3 - 1][1],
        vnCache[vn3 - 1][2],
        vtCache[vt3 - 1][0],
        vtCache[vt3 - 1][1]
      },
      Vertex {
        vCache[v4 - 1][0],
        vCache[v4 - 1][1],
        vCache[v4 - 1][2],
        vnCache[vn4 - 1][0],
        vnCache[vn4 - 1][1],
        vnCache[vn4 - 1][2],
        vtCache[vt4 - 1][0],
        vtCache[vt4 - 1][1]
      }
    };
  } 
}

bool containsFaceWithFiveOrMoreVertecies(std::ifstream& fileStream){
  fileStream.clear();
  fileStream.seekg(0);

  std::string line;
  while (std::getline(fileStream, line)) {
    if(isFaceDefinition(line)){
      unsigned int count = 0;
      for(char c : line){
        if(c == '/') count++;
      }

      if(count > 4*2) return true;
    }
  }

  return false;
}

bool Parser::parse(std::string filename){
  std::ifstream fileStream (filename);
  if (!fileStream.is_open()) { 
    std::cerr << "Could not open file " << filename << std::endl;
    return false;
  }

  std::string line;
  if(containsFaceWithFiveOrMoreVertecies(fileStream)){
    std::cerr << "The file contains a face with five or more vertices. Please triangulate the object" << std::endl;
    return false;
  }

  unsigned int vCount = 0;
  unsigned int vtCount = 0;
  unsigned int vnCount = 0;
  fillCountInfo(fileStream, vCount, vtCount, vnCount);

  std::vector<std::vector<float>> vCache(vCount, {0.0f, 0.0f, 0.0f});
  std::vector<std::vector<float>> vtCache(vtCount, {0.0f, 0.0f});
  std::vector<std::vector<float>> vnCache(vnCount, {0.0f, 0.0f, 0.0f});

  fileStream.clear();
  fileStream.seekg(0);

  int v = 0;
  int vt = 0;
  int vn = 0;
  while (!fileStream.eof()) {
    while (std::getline(fileStream, line)) {
      if (isObjectDefinition(line)) break; 

      if (isVertexDefinition(line)) {
        float x,y,z;
        fillVertexCords(line, x, y, z);
        vCache[v][0] = x;
        vCache[v][1] = y;
        vCache[v][2] = z;
        v++;
      } else if (isTextureDefinition(line)) {
        float u,v;
        fillTextureCords(line, u, v);
        vtCache[vt][0] = u;
        vtCache[vt][1] = v;
        vt++;
      } else if (isNormalDefinition(line)) {
        float x,y,z;
        fillNormalCords(line, x, y, z);
        vnCache[vn][0] = x;
        vnCache[vn][1] = y;
        vnCache[vn][2] = z;
        vn++;
      } else if (isFaceDefinition(line)) {
        bool isQuad = false;
        Triangle t1, t2;
        fillTriangles(line, vCache, vnCache, vtCache, t1, isQuad, t2);

        triangles.push_back(t1); 

        if (isQuad) {
          triangles.push_back(t2);
        }
      }
    }
  }

  fileStream.close();
}
void Parser::interpolate(){
  float min_x = std::numeric_limits<float>::max();
  float max_x = std::numeric_limits<float>::min();
  float min_y = std::numeric_limits<float>::max();
  float max_y = std::numeric_limits<float>::min();

  for(const Triangle& triangle : this->triangles){
    min_x = std::min(min_x, std::min(triangle.v1.x, std::min(triangle.v2.x, triangle.v3.x)));
    max_x = std::max(max_x, std::max(triangle.v1.x, std::max(triangle.v2.x, triangle.v3.x)));
    min_y = std::min(min_y, std::min(triangle.v1.y, std::min(triangle.v2.y, triangle.v3.y)));
    max_y = std::max(max_y, std::max(triangle.v1.y, std::max(triangle.v2.y, triangle.v3.y)));
  }

  for(Triangle& triangle : this->triangles){
    triangle.v1.x = (triangle.v1.x - min_x) / (max_x - min_x);
    triangle.v1.y = (triangle.v1.y - min_y) / (max_y - min_y);
    triangle.v2.x = (triangle.v2.x - min_x) / (max_x - min_x);
    triangle.v2.y = (triangle.v2.y - min_y) / (max_y - min_y);
    triangle.v3.x = (triangle.v3.x - min_x) / (max_x - min_x);
    triangle.v3.y = (triangle.v3.y - min_y) / (max_y - min_y);
  }
}

std::vector<Triangle>& Parser::getTriangles() {
  interpolate();
  return triangles;
}