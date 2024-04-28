#pragma once
#include "../scene/scene.h"

class Milestone1 {
private:
  float duration = 30.0f;
  Scene scene;

  void setup();
public:
  Milestone1() { setup(); }
  void play();
};