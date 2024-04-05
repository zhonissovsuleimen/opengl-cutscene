#pragma once

const char *VERTEX_SHADER = R"(

#version 410 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;

out vec2 texCoord;

void main() {
	gl_Position = vec4(vPosition, 1.0);
    texCoord = vTexCoord;
}


)";

const char *const V_SHADER[] = {VERTEX_SHADER};