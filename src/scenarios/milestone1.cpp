#pragma once
#include "milestone1.h"
#include "../renderer/renderer.h"
#include <iostream>
#include <filesystem>

void setLightParams(std::vector<Light> *lights){
  //hard-coded; might crush if the number of lights is different
  (*lights)[0].intensity = 0.20f;
  (*lights)[1].intensity = 0.35f;
  (*lights)[2].intensity = 0.35f;
  (*lights)[3].intensity = 0.35f;
  (*lights)[4].intensity = 0.35f;
  (*lights)[5].intensity = 0.35f;
  (*lights)[6].intensity = 0.35f;
  (*lights)[7].intensity = 0.35f;
  (*lights)[8].intensity = 0.20f;
  (*lights)[9].intensity = 0.20f;
  (*lights)[10].intensity = 0.20f;
  (*lights)[11].intensity = 0.40f;

  (*lights)[0].color = glm::vec3(1.0f, 1.0f, 1.0f);
  (*lights)[1].color = glm::vec3(1.0f, 1.0f, 0.0f);
  (*lights)[2].color = glm::vec3(1.0f, 0.0f, 1.0f);
  (*lights)[3].color = glm::vec3(0.0f, 0.0f, 1.0f);
  (*lights)[4].color = glm::vec3(0.0f, 0.0f, 1.0f);
  (*lights)[5].color = glm::vec3(0.0f, 1.0f, 1.0f);
  (*lights)[6].color = glm::vec3(0.5f, 0.0f, 0.5f);
  (*lights)[7].color = glm::vec3(1.0f, 0.0f, 1.0f);
  (*lights)[8].color = glm::vec3(0.35f, 0.25f, 0.6f);
  (*lights)[9].color = glm::vec3(0.1f, 0.8f, 0.1f);
  (*lights)[10].color = glm::vec3(0.3, 0.15f, 0.9f);
  (*lights)[11].color = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Milestone1::setup() {
  std::cout << "Milestone 1: Setup started" << std::endl;
  //requires cpp 17 or later
  std::string assets = (std::filesystem::current_path() / "assets" / "milestone1").string() + "/";

  Scene scene;
  scene.setAmbient(glm::vec3(0.1f));

  std::cout << "Milestone 1: parsing models" << std::endl;
  Model model(assets + "model1.obj");
  scene.addModel(model);

  std::cout << "Milestone 1: parsing lights" << std::endl;
  std::vector<Light> lights = Parser::parseLightCoords(assets + "light_coordinates.txt");
  setLightParams(&lights);
  for(Light light : lights) { scene.addLight(light); }

  std::cout << "Milestone 1: parsing camera movements" << std::endl;
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

  std::cout << "Playing Milestone 1 scenario" << std::endl;
  while(renderer.renderScene(&scene) && glfwGetTime() - startTime < duration){
    deltaTime = glfwGetTime() - currentTime;
    currentTime = glfwGetTime();

    t += deltaTime / duration;
    scene.camera.animate(t);
  }

  while(renderer.renderScene(&scene)){}
}