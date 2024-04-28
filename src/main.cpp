#include "renderer/renderer.h"
#include "util/definitions.h"
#include "model/model.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int main(int argc, char **argv) {
  Model model("");
  // not working yet
  //model.setTexture(new Texture(""));

  Light blue(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
  Light red(glm::vec3(-10.0f, 10.0f, -10.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
  
  Scene scene;
  scene.setAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
  scene.addModel(model);
  scene.addLight(blue);
  scene.addLight(red);
  scene.camera = Camera("", glm::vec3(0.0f, 1.0f, 0.0f));

  Renderer renderer;
  if (!renderer.init()) {
    return 1;
  }

  float t = 0.01f;
  while (renderer.renderScene(&scene)) {
    scene.camera.animate(t);
    t += 0.00001f;
  }
}