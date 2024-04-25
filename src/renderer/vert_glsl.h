#pragma once

const char *VERTEX_SHADER = R"(

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

const vec3 Kd = vec3(0.8, 0.8, 0.8); // diffuse reflection coefficient
const vec3 Ld = vec3(1.0, 1.0, 1.0); // light source intensity
const vec3 La = vec3(0.5, 0.5, 0.5); // ambient light intensity

void main() {
  vec3 tNorm = normalize(vNormal);
  vec4 tPos = modelMatrix * vPosition;
  vec3 s = normalize(vec3(viewMatrix * vec4(0, 10.0, 0, 1) - tPos));

  float angle = time;

  vColor = Ld * Kd * max(dot(tNorm, s), 0.0) + La;
  gl_Position = projectionMatrix *  viewMatrix * modelMatrix * vPosition;
  texCoord = vTexCoord;
}




)";

const char *const V_SHADER[] = {VERTEX_SHADER};