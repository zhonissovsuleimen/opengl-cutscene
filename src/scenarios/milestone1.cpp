#pragma once
#include "milestone1.h"
#include "../renderer/renderer.h"
#include <iostream>
#include <filesystem>

void Milestone1::setup() {
  //requires cpp 17 or later
  std::string assets = (std::filesystem::current_path() / "assets" / "milestone1").string() + "/";

  Scene scene;
  scene.setAmbient(glm::vec3(0.1f, 0.1f, 0.1f));

  Model model(assets + "model1.obj");
  scene.addModel(model);

  std::vector<Light> lights = Parser::parseLightCoords(assets + "light_coordinates.txt");
  for(Light light : lights) { scene.addLight(light); }

  scene.camera = Camera(assets + "bezier.txt", glm::vec3(0.0f, 1.0f, 0.0f));

  this->scene = scene;
}

void Milestone1::play(){
  Renderer renderer;
  if (!renderer.init()) { return; }


  float t = 0.0f; // t = [0..1] for animation purposes
  float startTime = glfwGetTime();
  float currentTime = startTime;
  float deltaTime;

  while(renderer.renderScene(&scene) && glfwGetTime() - startTime < duration){
    deltaTime = glfwGetTime() - currentTime;
    currentTime = glfwGetTime();

    t += deltaTime / duration;
    scene.camera.animate(t);
  }

  std::cin.get();
}