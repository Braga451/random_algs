#version 330 core

in vec3 color;
in vec2 textureCoords;
out vec4 fragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float texture2Opacity;

void main() {
  fragColor = mix(texture(texture1, textureCoords),
                  texture(texture2, textureCoords), texture2Opacity);
}
