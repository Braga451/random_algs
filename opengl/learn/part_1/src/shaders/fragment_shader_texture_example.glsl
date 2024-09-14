#version 330 core

in vec3 color;
in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
  vec2 flippedCoords = vec2(-1, 1) * textureCoords;

  fragColor = mix(texture(texture1, textureCoords),
                  texture(texture2, flippedCoords), 0.5f);
}
