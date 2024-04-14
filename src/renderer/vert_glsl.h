#pragma once

const char *VERTEX_SHADER = R"(

#version 410 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time;

out vec2 texCoord;

const float PI = 3.1415926535897932384626433832795;

mat4 rotateZ(float angle) {
    return mat4(
        cos(angle), -sin(angle), 0, 0,
        sin(angle), cos(angle), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    );
}

void main() {
    float angle = (time * PI) / 180.0;
	gl_Position = projectionMatrix * viewMatrix * (rotateZ(angle) * modelMatrix) * vPosition;
    texCoord = vTexCoord;
}




)";

const char *const V_SHADER[] = {VERTEX_SHADER};