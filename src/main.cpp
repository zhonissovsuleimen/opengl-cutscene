#include "renderer/renderer.h"
#include "util/definitions.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
  Scene scene;
  if (!scene.load(OBJ_FILE_PATH)) {
    return 1;
  }

  Renderer renderer;
  if (!renderer.init()) {
    return 1;
  }
  renderer.setScene(&scene);

  while (renderer.render()) {}
}