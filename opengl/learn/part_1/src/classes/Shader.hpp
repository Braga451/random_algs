#ifndef SHADER_H
#define SHADER_H

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>

class Shader {
  public:
    Shader(const std::string &shaderPath,
           const GLenum &shaderType);
    
    Shader(Shader vertexShader, Shader fragmentShader);

    unsigned int getShaderId() {
      return shaderId;
    }

    void useShader();

  private:  
    std::string readShader(const std::string &shaderPath);
    unsigned int shaderId;
};

#endif
