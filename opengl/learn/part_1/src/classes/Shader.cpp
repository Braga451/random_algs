#include "Shader.hpp"
#include <iostream>
#include <fstream>

std::string Shader::readShader(const std::string &shaderPath) {
  std::ifstream shaderFile(shaderPath);

  if (!shaderFile.is_open()) {
    std::cerr << "Error reading shader!" << std::endl;
    return "";
  }

  std::string shaderLine;
  std::string shaderContent;

  while (std::getline(shaderFile, shaderLine)) {
    shaderContent += shaderLine + "\n";
  }

  shaderFile.close();

  std::cout << "Shader content: " << shaderContent << std::endl;

  return shaderContent;

}

Shader::Shader(const std::string &shaderPath,
           const GLenum &shaderType) {
  
  const std::string shaderContent = readShader(shaderPath);
  const char *shaderContentCStr = shaderContent.c_str();

  if (shaderContent == "") {
    exit(1);
  }

  unsigned int shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &shaderContentCStr, nullptr);
  glCompileShader(shader);

  int isCompiled;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

  if (!isCompiled) {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Error compiling shader!" << std::endl;
    std::cerr << "Error: " << std::endl << infoLog << std::endl;
    exit(1);
  }

  else {
    std::cout << "Shader compiled!" << std::endl;
  }

  Shader::shaderId = shader;
}

Shader::Shader(Shader vertexShader, Shader fragmentShader) {
  unsigned int shaderProgram = glCreateProgram();
  
  glAttachShader(shaderProgram, vertexShader.getShaderId());
  glAttachShader(shaderProgram, fragmentShader.getShaderId());
  glLinkProgram(shaderProgram);
  
  char linkedLog[512];
  int isLinked;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);

  if (!isLinked) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, linkedLog);

    std::cerr << "Error linking shaders: " << std::endl
              << linkedLog << std::endl;

    exit(1);
  } else {
    std::cout << "Shaders linked!" << std::endl;
  }

  glDeleteShader(vertexShader.getShaderId());
  glDeleteShader(fragmentShader.getShaderId());

  Shader::shaderId = shaderProgram;
}

void Shader::useShader() {
  glUseProgram(Shader::getShaderId());
}
