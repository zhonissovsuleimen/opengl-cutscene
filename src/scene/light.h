#include <glm/vec3.hpp>

class Light {
public:
  glm::vec3 position;
  glm::vec3 color;
  float intensity;

  Light(glm::vec3 position, glm::vec3 color = glm::vec3(0.0f, 0.0f, 0.0f), float intensity = 1.0f);
};