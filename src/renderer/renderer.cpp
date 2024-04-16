#pragma once

#include "renderer.h"
#include "vert_glsl.h"
#include "frag_glsl.h"
#include "../parser/parser.h"
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
  
  if (!initShaders()){ return false; }
  
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);
  time = 0.0f;

  return true;
}

void Renderer::setScene(Scene *scene) {
  this->scene = scene;
  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  GLsizei vertexCount = scene->triangles.size()* 3;

  int stride = 8 * sizeof(GLfloat);
  glBufferData(GL_ARRAY_BUFFER, vertexCount * stride, scene->triangles.data(), GL_STATIC_DRAW);

  int offset = 3 * sizeof(GLfloat);
  int offset2 = 6 * sizeof(GLfloat);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)offset);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)offset2);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
}

bool Renderer::render() {
  int location = glGetUniformLocation(shaderProgram, "modelMatrix");
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));
  location = glGetUniformLocation(shaderProgram, "viewMatrix");
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(scene->camera.getViewMatrix()));
  location = glGetUniformLocation(shaderProgram, "projectionMatrix");
  glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(scene->camera.getProjectionMatrix()));
  location = glGetUniformLocation(shaderProgram, "time");
  glUniform1f(location, time);

  if (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLsizei vertexCount = scene->triangles.size()* 3;
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glfwSwapBuffers(window);
    glfwPollEvents();

    time+= .01;
    return true;
  } else {
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }
}