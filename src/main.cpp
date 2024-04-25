#include "renderer/renderer.h"
#include "util/definitions.h"
#include "model/model.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  Model model(OBJ_FILE_PATH);
  // not working yet
  //model.setTexture(new Texture(""));
  
  Scene scene;
  scene.addModel(model);

  Renderer renderer;
  if (!renderer.init()) {
    return 1;
  }

  while (renderer.renderScene(&scene)) {}
}