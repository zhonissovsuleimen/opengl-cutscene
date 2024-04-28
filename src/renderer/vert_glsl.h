#pragma once
#include "../util/definitions.h"

std::string VERTEX_SHADER = R"(

#version 410 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec3 vColor;
out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time;

struct Light {
  vec3 position;
  vec3 color;
  float intensity;
};

const int MAX_LIGHTS = )" + std::to_string(MAX_LIGHTS) + R"(;
uniform int lightCount;
uniform Light lights[MAX_LIGHTS];
uniform vec3 ambient;

void main() {
  vec3 tNorm = normalize(vNormal);
  vec4 tPos = modelMatrix * vPosition;
  vColor = ambient;
  for (int i = 0; i < lightCount && i < MAX_LIGHTS; i++) {
    vec3 s = normalize(lights[i].position - tPos.xyz);
    vColor += lights[i].intensity * lights[i].color * max(dot(tNorm, s), 0.0);
  }

  gl_Position = projectionMatrix * viewMatrix * tPos;
  texCoord = vTexCoord;
}


)";

const char *const V_SHADER[] = {VERTEX_SHADER.c_str()};
