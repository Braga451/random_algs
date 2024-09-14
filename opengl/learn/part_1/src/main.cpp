#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <ostream>
#include <string>
#include <stb_image/stb_image.hpp>
#include "classes/Shader.hpp"

unsigned int createTexture(const char * texturePath, 
                           const float (&borderColor)[4], 
                           const bool flipImage, 
                           const GLenum format) {
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glad_glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glad_glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  
  glad_glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glad_glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  
  stbi_set_flip_vertically_on_load(flipImage);
  int width, height, channels;
  unsigned char * textureData = stbi_load(texturePath, &width, &height, &channels, 0);

  if (textureData == nullptr) {
    std::cerr << "Error loding texture data!" << std::endl;
    exit(1);
  }

  unsigned int textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, textureData);
  glGenerateMipmap(GL_TEXTURE_2D);
  
  stbi_image_free(textureData);
  
  return textureId;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

Shader returnTriangleShader(const std::string& fragmentShaderPath, const std::string& vertexShaderPath, unsigned int * VAO) {
  glGenVertexArrays(1, VAO);
  glBindVertexArray(*VAO);

  float vertices[] = {
    -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 
    0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
    1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f
  }; // The last 3 values of each row are colors 
  
  float texture[] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.5f, 1.0f
  };

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
                                   const float (&vertices)[32],
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
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  // glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                        8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // Position data

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 
                        8 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1); // Color data
  
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 
                        8 * sizeof(float), (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2); // Texture data

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
  
  float border[] = {
    1.0f, 1.0f, 1.0f, 1.0f
  };

  unsigned textureId = createTexture("../textures/container.jpg", border, false, GL_RGB);
  unsigned textureId2 = createTexture("../textures/awesomeface.png", border, true, GL_RGBA);
  
  float firstRectangleVertices[] = {
    -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top left
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,// Bottom left
    0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,// Top right
    0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f // Bottom right
  };

  unsigned int firstRectangleIndices[] = {
    0, 1, 2,
    2, 3, 1
  };

  unsigned int firstVAO;
  Shader firstRectangleShader = returnRectangleShader(firstRectangleIndices, 
                                                            firstRectangleVertices, 
                                                             "../shaders/vertex_shader_texture_example.glsl",
                                                            "../shaders/fragment_shader_texture_example.glsl",
                                                            &firstVAO,
                                                            0);
  firstRectangleShader.useShader();
  glUniform1i(glGetUniformLocation(firstRectangleShader.getShaderId(), "texture1"), 0);
  glUniform1i(glGetUniformLocation(firstRectangleShader.getShaderId(), "texture2"), 1);

  /*float secondRectangleVertices[] = {
    0.0f, 0.5f, 0.0f, // Top left
    0.0f, -0.5f, 0.0f, // Bottom left
    0.5f, 0.5f, 0.0f, // Top right
    0.5f, -0.5f, 0.0f // Bottom right
  };

  unsigned int secondRectangleIndices[] = {
    0, 1, 2,
    2, 3, 1
  };
  
  unsigned int secondVAO;

  Shader secondRectangleShader = returnRectangleShader(secondRectangleIndices, 
                                                             secondRectangleVertices, 
                                                             "../shaders/vertex_shader.glsl",
                                                              "../shaders/second_fragment_shader.glsl",
                                                             &secondVAO,
                                                             1);
  
  
  
  unsigned int VAO;

  Shader triangleShader = returnTriangleShader("../shaders/fragment_shader_multicolor_example.glsl", 
                                                     "../shaders/vertex_shader_multicolor_example.glsl", 
                                                     &VAO);
  */

  while (!glfwWindowShouldClose(w) ) {
    // std::cout << firstRectangleShader << ":" << secondRectangleShader << std::endl;
    // std::cout << firstVAO << ":" << secondVAO << std::endl;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    processInput(w);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    firstRectangleShader.useShader();
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureId2);

    glBindVertexArray(firstVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    /*
    secondRectangleShader.useShader();
    glBindVertexArray(secondVAO);  
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);  
    
    triangleShader.useShader();
   
    int offSet = glGetUniformLocation(triangleShader.getShaderId(), "offSet");
    glUniform1f(offSet, 0.5f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */

    glfwSwapBuffers(w);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
