#include "renderer.h"
#include "vert_glsl.h"
#include "frag_glsl.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
}

bool Renderer::initShaders(){
  // Initialize vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, V_SHADER, NULL);
  glCompileShader(vertexShader);

  //Checking for errors
  GLint status;
  glGetProgramiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char infolog[512];
    glGetProgramInfoLog(vertexShader, 512, NULL, infolog);
    std::cerr << "Vertex shader error" << std::endl;
    std::cerr << infolog << std::endl;
    return false;
  }

  //Initialize fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, F_SHADER, NULL);
  glCompileShader(fragmentShader);

  //Checking for errors
  glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char infolog[512];
    glGetProgramInfoLog(fragmentShader, 512, NULL, infolog);
    std::cerr << "Fragment shader error" << std::endl;
    std::cerr << infolog << std::endl;
    return false;
  }

  //Linking vertex and fragment shaders
  GLuint shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  //Checking for errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    char infolog[512];
    glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
    std::cerr << "Shader linking error" << std::endl;
    std::cerr << infolog << std::endl;
    return false;
  }

  glUseProgram(shaderProgram);
  return true;
}

bool Renderer::init() {
  if (!glfwInit()) return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required for MacOS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow( 800, 600, "OpenGL Scene", NULL, NULL);

  if(!window){
    glfwTerminate();
    return false;
  }

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glfwMakeContextCurrent(window); 
  glfwSetKeyCallback(window, key_callback); // escape key to close window

  glewExperimental = GL_TRUE;
  glewInit();

  if (!initShaders()){ return false; }

  return true;
}

bool Renderer::render() {
  if (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
    return true;
  } else {
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }
}