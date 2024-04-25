#pragma once

#include "../scene/scene.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Renderer {
  private:
  GLFWwindow *window;
  GLfloat time;

  GLuint vao;
  GLuint vbo;
  GLuint tex;

  bool initShaders();

  public:
  bool init();
  bool renderScene(Scene *scene);
};