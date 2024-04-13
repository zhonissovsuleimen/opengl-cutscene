#pragma once

const char *VERTEX_SHADER = R"(

#version 410 core

layout (location = 0) in vec4 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 texCoord;

void main() {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vPosition;
    texCoord = vTexCoord;
}


)";

const char *const V_SHADER[] = {VERTEX_SHADER};