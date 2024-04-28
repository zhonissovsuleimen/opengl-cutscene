#pragma once

#include "renderer.h"
#include "vert_glsl.h"
#include "frag_glsl.h"
#include "../util/definitions.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

GLint shaderProgram;

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
  shaderProgram = glCreateProgram();
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

  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Scene", NULL, NULL);

  if(!window){
    glfwTerminate();
    return false;
  }

  glfwMakeContextCurrent(window); 
  glfwSetKeyCallback(window, key_callback); // escape key to close window

  glewExperimental = GL_TRUE;
  glewInit();
  glEnable(GL_DEPTH_TEST); // fixes issues with depth 
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND); 
  
  if (!initShaders()){ return false; }
  
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  glGenTextures(1, &tex);

  return true;
}

bool Renderer::renderScene(Scene *scene) {
  int location = glGetUniformLocation(shaderProgram, "viewMatrix");
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(scene->camera.getViewMatrix()));
  location = glGetUniformLocation(shaderProgram, "projectionMatrix");
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(scene->camera.getProjectionMatrix()));
  location = glGetUniformLocation(shaderProgram, "time");
  glUniform1f(location, time);

  if (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    scene->draw(shaderProgram, vao, vbo, tex);
    glfwSwapBuffers(window);
    glfwPollEvents();

    return true;
  } else {
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }
}