#pragma once

const char *FRAGMENT_SHADER = R"(

#version 410 core

in vec3 vColor;
out vec4 fColor;

void main() {
	fColor = vec4(vColor, 1.0);
}


)";

const char *const F_SHADER[] = {FRAGMENT_SHADER};