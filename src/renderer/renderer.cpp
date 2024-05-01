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
  std::cout << "Initializing vertex shader" << std::endl;
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, V_SHADER, NULL);
  glCompileShader(vertexShader);

  //Checking for errors
  GLint status;
  glGetProgramiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char infolog[512];
    glGetProgramInfoLog(vertexShader, 512, NULL, infolog);
    std::cerr << "Vertex shader compilation failed" << std::endl;
    std::cerr << infolog << std::endl;
    return false;
  }
  std::cout << "Initializing vertex shader complete" << std::endl;

  std::cout << "Initializing fragment shader" << std::endl;
  //Initialize fragment shader
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, F_SHADER, NULL);
  glCompileShader(fragmentShader);

  //Checking for errors
  glGetProgramiv(fragmentShader, GL_COMPILE_STATUS, &status);
  if (status != GL_TRUE) {
    char infolog[512];
    glGetProgramInfoLog(fragmentShader, 512, NULL, infolog);
    std::cerr << "Fragment shader compilation failed" << std::endl;
    std::cerr << infolog << std::endl;
    return false;
  }
  std::cout << "Initializing fragment shader complete" << std::endl;

  //Linking vertex and fragment shaders
  std::cout << "Linking shaders into shader program" << std::endl;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  //Checking for errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
  if (status != GL_TRUE) {
    char infolog[512];
    glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
    std::cerr << "Shader linking failed" << std::endl;
    std::cerr << infolog << std::endl;
    return false;
  }
  std::cout << "Linking shaders complete" << std::endl;

  glUseProgram(shaderProgram);
  return true;
}

bool Renderer::init() {
  std::cout << "Initializing OpenGL libraries" << std::endl;
  if (!glfwInit()) { 
    std::cerr << "Failed to initialize GLFW" << std::endl;
    return false; 
  }
  std::cout << "Initializing OpenGL libraries complete" << std::endl;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // required for MacOS
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


  std::cout << "Creating OpenGL window" << std::endl;
  window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Scene", NULL, NULL);
  if(!window){
    std::cerr << "Failed to create OpenGL window" << std::endl;
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