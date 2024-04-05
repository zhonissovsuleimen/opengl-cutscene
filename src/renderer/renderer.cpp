#include "renderer.h"
#include "vert_glsl.h"
#include "frag_glsl.h"

#include "../parser/parser.h"
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

  glfwMakeContextCurrent(window); 
  glfwSetKeyCallback(window, key_callback); // escape key to close window

  glewExperimental = GL_TRUE;
  glewInit();
  
  if (!initShaders()){ return false; }
  
  glGenBuffers(1, &vbo);
  glGenVertexArrays(1, &vao);

  return true;
}

void Renderer::setScene(Scene *scene) {
  this->scene = scene;
}

bool Renderer::render() {
  if (!glfwWindowShouldClose(window)) {
    static const float black[] = {0.0f, 0.0f, 0.0f, 0.0f};
    glClearBufferfv(GL_COLOR, 0, black);

    GLsizei count = scene->triangles.size() * 3;
    for(Triangle triangle : scene->triangles){
      GLfloat vertices[] = {
        triangle.v1.x, triangle.v1.y, triangle.v1.z, 
        triangle.v1.normal_x, triangle.v1.normal_y, triangle.v1.normal_z, 
        triangle.v1.u, triangle.v1.v,

        triangle.v2.x, triangle.v2.y, triangle.v2.z,
        triangle.v2.normal_x, triangle.v2.normal_y, triangle.v2.normal_z,
        triangle.v2.u, triangle.v2.v,

        triangle.v3.x, triangle.v3.y, triangle.v3.z,
        triangle.v3.normal_x, triangle.v3.normal_y, triangle.v3.normal_z,
        triangle.v3.u, triangle.v3.v
      };

      int stride = 8 * sizeof(GLfloat);
      int offset = 3 * sizeof(GLfloat);
      int offset2 = 6 * sizeof(GLfloat);

      glBindVertexArray(vao);
      glBindBuffer(GL_ARRAY_BUFFER, vbo);

      glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)offset);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)offset2);

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);

      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindVertexArray(0);
    }

    glDrawArrays(GL_TRIANGLES, 0, count);

    glfwSwapBuffers(window);
    glfwPollEvents();

    return true;
  } else {
    glfwDestroyWindow(window);
    glfwTerminate();
    return false;
  }
}