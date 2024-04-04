#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
  private:
  GLFWwindow *window;

  public:
  bool init();
  bool render();
};