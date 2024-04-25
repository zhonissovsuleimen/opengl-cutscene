#pragma once

#include "model.h"
#include "../parser/parser.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"


Model::Model(const std::string& path) : path(path), modelMatrix(glm::mat4(1.0f)), texture(nullptr), hasTexture(false) {
  Parser parser;
  parser.parse(path);
  triangles = parser.getTriangles(); 
}

Model::~Model() {
  // glDeleteVertexArrays(1, &vao);
  // glDeleteBuffers(1, &vbo);
  // glDeleteTextures(1, &tex);
}

void Model::setTexture(Texture* texture) {
  this->texture = texture;
  hasTexture = texture->success;
}

void Model::bind(unsigned int vao, unsigned int vbo, unsigned int tex) const {
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  GLsizei vertexCount = triangles.size() * 3;
  int stride = 8 * sizeof(GLfloat);
  int offset = 3 * sizeof(GLfloat);
  int offset2 = 6 * sizeof(GLfloat);

  glBufferData(GL_ARRAY_BUFFER, vertexCount * stride, triangles.data(), GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)offset);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)offset2);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  if(hasTexture) { texture->bind(0, tex); }
}

void Model::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  if(hasTexture) { texture->unbind(); }
}

void Model::draw(unsigned int programId, unsigned int vao, unsigned int vbo, unsigned int tex) const {
  glUniformMatrix4fv(glGetUniformLocation(programId, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
  if (hasTexture) {
    glUniform1i(glGetUniformLocation(programId, "hasTexture"), texture->success);  
    glUniform1i(glGetUniformLocation(programId, "tex"), 0); 
  }

  bind(vao, vbo, tex);
  glDrawArrays(GL_TRIANGLES, 0, triangles.size() * 3);
  unbind();
}