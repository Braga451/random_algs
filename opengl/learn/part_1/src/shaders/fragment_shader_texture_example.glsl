#version 330 core

in vec3 color;
in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main() {
  vec2 newCoords = (textureCoords * 1/4) - vec2(0.5, 0.5);
  
  fragColor = mix(texture(texture1, textureCoords),
                  texture(texture2, newCoords), 0.5f);
}
