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

void fillBezierCoords(const std::string& line, float& x, float& y, float& z){
  std::string coords = line.substr(1);
  coords = coords.substr(coords.find_first_not_of(' '));

  std::string xStr = coords.substr(0, coords.find(' '));
  x = std::stof(xStr);
  coords = coords.substr(coords.find(' '));
  coords = coords.substr(coords.find_first_not_of(' '));

  std::string yStr = coords.substr(0, coords.find(' '));
  y = std::stof(yStr);
  coords = coords.substr(coords.find(' '));
  coords = coords.substr(coords.find_first_not_of(' '));

  z = std::stof(coords);
}

void fillVertexCoords(const std::string& line, float& x, float& y, float& z){
  std::string coords = line.substr(1);
  coords = coords.substr(coords.find_first_not_of(' '));

  std::string xStr = coords.substr(0, coords.find(' '));
  x = std::stof(xStr);
  coords = coords.substr(coords.find(' '));
  coords = coords.substr(coords.find_first_not_of(' '));

  std::string yStr = coords.substr(0, coords.find(' '));
  y = std::stof(yStr);
  coords = coords.substr(coords.find(' '));
  coords = coords.substr(coords.find_first_not_of(' '));

  z = std::stof(coords);
}

void fillNormalCoords(const std::string& line, float& x, float& y, float& z){
  std::string coords = line.substr(2);
  coords = coords.substr(coords.find_first_not_of(' '));

  std::string xStr = coords.substr(0, coords.find(' '));
  x = std::stof(xStr);
  coords = coords.substr(coords.find(' '));
  coords = coords.substr(coords.find_first_not_of(' '));

  std::string yStr = coords.substr(0, coords.find(' '));
  y = std::stof(yStr);
  coords = coords.substr(coords.find(' '));
  coords = coords.substr(coords.find_first_not_of(' '));

  z = std::stof(coords);
}

void fillTextureCoords(const std::string& line, float& u, float& v){
  std::string coords = line.substr(2);
  coords = coords.substr(coords.find_first_not_of(' '));

  std::string uStr = coords.substr(0, coords.find(' '));
  u = std::stof(uStr);
  coords = coords.substr(coords.find(' '));
  coords = coords.substr(coords.find_first_not_of(' '));

  v = std::stof(coords);
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

std::vector<Triangle> Parser::parseObj(std::string filename){
  std::vector<Triangle> triangles;
  std::ifstream fileStream (filename);
  if (!fileStream.is_open()) { 
    std::cerr << "Could not open file " << filename << std::endl;
    return std::vector<Triangle>();
  }

  std::string line;
  if(containsFaceWithFiveOrMoreVertecies(fileStream)){
    std::cerr << "The file contains a face with five or more vertices. Please triangulate the object" << std::endl;
    return std::vector<Triangle>();
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
        fillVertexCoords(line, x, y, z);
        vCache[v][0] = x;
        vCache[v][1] = y;
        vCache[v][2] = z;
        v++;
      } else if (isTextureDefinition(line)) {
        float u,v;
        fillTextureCoords(line, u, v);
        vtCache[vt][0] = u;
        vtCache[vt][1] = v;
        vt++;
      } else if (isNormalDefinition(line)) {
        float x,y,z;
        fillNormalCoords(line, x, y, z);
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
  return triangles;
}

std::vector<Bezier> Parser::parseBezier(std::string filename) {
  std::vector<Bezier> beziers;

  std::ifstream fileStream (filename);
  if (!fileStream.is_open()) { 
    std::cerr << "Could not open file " << filename << std::endl;
    return std::vector<Bezier>();
  }


  unsigned i = 0;  
  std::string line;
  while (!fileStream.eof()) {
    while (std::getline(fileStream, line)) {
      glm::vec3 start, control1, control2, end;

      float x, y, z;
      fillBezierCoords(line, x, y, z);
      if(i % 4 == 0){
        start = glm::vec3(x, y, z);
      } else if(i % 4 == 1){
        control1 = glm::vec3(x, y, z);
      } else if(i % 4 == 2){
        control2 = glm::vec3(x, y, z);
      } else if(i % 4 == 3){
        end = glm::vec3(x, y, z);
      }
      beziers.push_back({start, control1, control2, end});

      i++;
    }
  }

  fileStream.close();
  return beziers;
}
