#include "renderer/renderer.h"
#include "util/definitions.h"
#include "model/model.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  Model model(OBJ_FILE_PATH);
  // not working yet
  //model.setTexture(new Texture(""));

  Light blue(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 1.0f);
  Light red(glm::vec3(-10.0f, 10.0f, -10.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f);
  
  Scene scene;
  scene.setAmbient(glm::vec3(0.1f, 0.1f, 0.1f));
  scene.addModel(model);
  scene.addLight(blue);
  scene.addLight(red);

  Renderer renderer;
  if (!renderer.init()) {
    return 1;
  }

  while (renderer.renderScene(&scene)) {}
}