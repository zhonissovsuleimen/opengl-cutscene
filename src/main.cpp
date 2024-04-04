#include <stdio.h>
#include <stdlib.h>
#include "renderer/renderer.h"

int main(int argc, char **argv) {
  Renderer renderer;
  if (!renderer.init()) {
    return 1;
  }

  while (renderer.render()) {}
}