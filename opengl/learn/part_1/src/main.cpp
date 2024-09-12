#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <string>
#include "classes/Shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

Shader returnTriangleShader(const std::string& fragmentShaderPath, const std::string& vertexShaderPath, unsigned int * VAO) {
  float vertices[] = {
    -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f
  }; // The last 3 values of each row are color data
  
  glGenVertexArrays(1, VAO);
  glBindVertexArray(*VAO);

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                        6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // Position data

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
                        6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1); // Color data
  
  Shader shaderProgram(Shader(Shader(vertexShaderPath, GL_VERTEX_SHADER), 
                              Shader(fragmentShaderPath, GL_FRAGMENT_SHADER)));

  glBindVertexArray(0);

  return shaderProgram;
}

Shader returnRectangleShader(const unsigned int (&indices)[6], 
                                   const float (&vertices)[12],
                                   const std::string &vertexShaderPath,
                                   const std::string &fragmentShaderPath,
                                   unsigned int * VAO,
                                   unsigned int vertexAttribArrayIndex) {

  glGenVertexArrays(1, VAO);
  glBindVertexArray(*VAO);
  
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  unsigned int EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  
   Shader shaderProgram(Shader(Shader(vertexShaderPath, GL_VERTEX_SHADER), 
                        Shader(fragmentShaderPath, GL_FRAGMENT_SHADER)));
  
  glBindVertexArray(0);

  return shaderProgram;
}


int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *w = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);

  if (w == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(w);

  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    exit(1);
  }

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);

  float firstRectangleVertices[] = {
    -0.5f, 0.5f, 0.0f, // Top left
    -0.5f, -0.5f, 0.0f, // Bottom left
    0.0f, 0.5f, 0.0f, // Top right
    0.0f, -0.5f, 0.0f // Bottom right
  };

  unsigned int firstRectangleIndices[] = {
    0, 1, 2,
    2, 3, 1
  };

float secondRectangleVertices[] = {
    0.0f, 0.5f, 0.0f, // Top left
    0.0f, -0.5f, 0.0f, // Bottom left
    0.5f, 0.5f, 0.0f, // Top right
    0.5f, -0.5f, 0.0f // Bottom right
  };

  unsigned int secondRectangleIndices[] = {
    0, 1, 2,
    2, 3, 1
  };
  
  unsigned int firstVAO;
  unsigned int secondVAO;

  Shader firstRectangleShader = returnRectangleShader(firstRectangleIndices, 
                                                            firstRectangleVertices, 
                                                             "../shaders/vertex_shader.glsl",
                                                            "../shaders/fragment_shader.glsl",
                                                            &firstVAO,
                                                            0);

  Shader secondRectangleShader = returnRectangleShader(secondRectangleIndices, 
                                                             secondRectangleVertices, 
                                                             "../shaders/vertex_shader.glsl",
                                                              "../shaders/second_fragment_shader.glsl",
                                                             &secondVAO,
                                                             1);
  
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  
  
  /*unsigned int VAO;

  Shader triangleShader = returnTriangleShader("../shaders/fragment_shader_multicolor_example.glsl", 
                                                     "../shaders/vertex_shader_multicolor_example.glsl", 
                                                     &VAO); */

  while (!glfwWindowShouldClose(w) ) {
    // std::cout << firstRectangleShader << ":" << secondRectangleShader << std::endl;
    // std::cout << firstVAO << ":" << secondVAO << std::endl;

    processInput(w);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    firstRectangleShader.useShader();
    glBindVertexArray(firstVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    secondRectangleShader.useShader();
    glBindVertexArray(secondVAO);  
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);  
    
    /*
    triangleShader.useShader();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */
    glfwSwapBuffers(w);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
