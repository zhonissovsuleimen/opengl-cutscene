#pragma once

const char *FRAGMENT_SHADER = R"(

#version 410 core

in vec3 vColor;
in vec2 texCoord;
out vec4 fColor;

uniform bool hasTexture;
uniform sampler2D tex;

void main() {
  if (hasTexture) {
    fColor = texture(tex, texCoord);
  }else {
    fColor = vec4(vColor, 1.0);
  }
}


)";

const char *const F_SHADER[] = {FRAGMENT_SHADER};