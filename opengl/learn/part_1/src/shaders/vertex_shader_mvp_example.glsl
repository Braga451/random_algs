#version 330 core
layout (location = 0) in vec3 vertexPositions;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 aTextureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 color;
out vec2 textureCoords;

void main() {
  gl_Position = projection * view * model * vec4(vertexPositions, 1.0f);
  color = vertexColor;
  textureCoords = aTextureCoords;
}
