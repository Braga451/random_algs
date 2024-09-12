#version 330 core
layout (location = 0) in vec3 vertexPositions;
layout (location = 1) in vec3 vertexColor;

out vec3 color;
uniform float offSet;

void main() {
  float theta = radians(0);
  
  mat3 rotationMatrix = mat3(
    vec3(cos(theta), -sin(theta), 0),
    vec3(sin(theta), cos(theta), 0),
    vec3(0 , 0, 1)
  );

  gl_Position = vec4(vertexPositions.x + offSet, vertexPositions.y, vertexPositions.z, 1.0f);
  color = vertexColor;
}
