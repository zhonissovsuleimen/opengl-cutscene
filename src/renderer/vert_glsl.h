#pragma once
#include "../util/definitions.h"
#include <string>

std::string VERTEX_SHADER = R"(

#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec3 vColor;
out vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

struct Light {
  vec3 position;
  vec3 color;
  float intensity;
};

const int MAX_LIGHTS = )" + std::to_string(MAX_LIGHTS) + R"(;
uniform int lightCount;
uniform Light lights[MAX_LIGHTS];
uniform vec3 ambient;

vec4 maybeFlipNormal(vec4 normal, vec4 position) {
  vec4 toOrigin = vec4(0.0, 0.0, 0.0, 1.0) - position;
  toOrigin.w = 0.0;
  toOrigin = normalize(toOrigin);

  float n = dot(toOrigin, normal);
  if (n < 0.0) {
    return -normal;
  }
  return normal;
}

vec3 computeLighting(vec4 tPosition, vec4 tNormal, mat4 viewMatrix){
  vec3 color = ambient;
  for(int i = 0; i < lightCount && i < MAX_LIGHTS; i++){
    vec4 lightPos = vec4(lights[i].position, 1.0);
    lightPos = viewMatrix * lightPos;

    vec3 ray = normalize(lightPos.xyz - tPosition.xyz);

    color += lights[i].intensity * lights[i].color * max(dot(tNormal.xyz, ray), 0.0);
    color.rgb = clamp(color.rgb, 0.0, 1.0);
  }

  return color;
}

void main() {
  vec4 position = vec4(inPosition, 1.0);
  vec4 normal = vec4(inNormal, 0.0);

  mat4 mvTransform = viewMatrix * modelMatrix;
  mat4 mvNormal = transpose(inverse(mvTransform));

  vec4 tPosition = mvTransform * position;
  vec4 tNormal = mvNormal * normal;
  
  tNormal.w = 0.0;
  tNormal = maybeFlipNormal(tNormal, tPosition);

  vColor = computeLighting(tPosition, tNormal, viewMatrix);

  mat4 mvpTransform = projectionMatrix * mvTransform;
  gl_Position = mvpTransform * position;

  // vec3 tNorm = normalize(vNormal);
  // vec4 tPos = modelMatrix * vPosition;
  // vColor = ambient;
  // for (int i = 0; i < lightCount && i < MAX_LIGHTS; i++) {
  //   vec3 s = normalize(lights[i].position - tPos.xyz);
  //   vColor += lights[i].intensity * lights[i].color * max(dot(tNorm, s), 0.0);
  // }

  // gl_Position = projectionMatrix * viewMatrix * tPos;
  // texCoord = vTexCoord;
}


)";

const char *const V_SHADER[] = {VERTEX_SHADER.c_str()};
