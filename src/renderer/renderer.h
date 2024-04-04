#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
  private:
  GLFWwindow *window;

  GLuint vao;
  GLuint vbo;
  GLuint tex;

  bool initShaders();

  public:
  bool init();
  bool render();
};