#include <cstdlib>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>
#include <cmath>
#include <ostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image/stb_image.hpp>
#include "classes/Shader.hpp"

typedef struct {
  unsigned int shaderId;
  float o;
}Opacity;

void returnModelAndViewAndProjectionMatrices(glm::mat4 * m, glm::mat4 * v, glm::mat4 * p) {
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  
  *m = model;
  *v = view;
  *p = projection;
}

unsigned int createTexture(const char * texturePath, 
                           const float (&borderColor)[4], 
                           const bool flipImage, 
                           const GLenum format) {
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glad_glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glad_glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  
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

void processInput(GLFWwindow *window, void (*f)(GLFWwindow * w, void * args), void * args) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
  
  if (f != nullptr) {
    f(window, args);
  }
}

void modifyTextureOpacity(GLFWwindow * w, void * args) {
  Opacity * op = (Opacity *) args;
  int uniformLocation = glGetUniformLocation(op->shaderId, "texture2Opacity");

  if (glfwGetKey(w, GLFW_KEY_UP) == GLFW_PRESS)
    op->o++;

  if (glfwGetKey(w, GLFW_KEY_DOWN) == GLFW_PRESS)
    op->o--;
  
  op->o = 1/(0.8643 + std::exp(-op->o));

  std::cout << op->o << std::endl;
  glUniform1f(uniformLocation, op->o);
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

Shader returnCubeShader(const std::string &vertexShaderPath,
                                   const std::string &fragmentShaderPath,
                                   unsigned int * VAO) {
  float vertices[] = {
-0.5f, -0.5f, -0.5f,0.0f, 0.0f,
 0.5f, -0.5f, -0.5f,1.0f, 0.0f,
0.5f, 0.5f, -0.5f,1.0f, 1.0f,
0.5f, 0.5f, -0.5f,1.0f, 1.0f,
-0.5f, 0.5f, -0.5f,0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,0.0f, 0.0f,

-0.5f, -0.5f,0.5f,0.0f, 0.0f,
0.5f, -0.5f,0.5f,1.0f, 0.0f,
0.5f, 0.5f,0.5f,1.0f, 1.0f,
0.5f, 0.5f,0.5f,1.0f, 1.0f,
-0.5f, 0.5f,0.5f,0.0f, 1.0f,
-0.5f, -0.5f,0.5f,0.0f, 0.0f,

-0.5f, 0.5f, 0.5f,1.0f, 0.0f,
-0.5f, 0.5f, -0.5f,1.0f, 1.0f,
-0.5f, -0.5f, -0.5f,0.0f, 1.0f,
-0.5f, -0.5f, -0.5f,0.0f, 1.0f,
-0.5f, -0.5f, 0.5f,0.0f, 0.0f,
-0.5f, 0.5f, 0.5f,1.0f, 0.0f,

0.5f, 0.5f, 0.5f,1.0f, 0.0f,
0.5f, 0.5f, -0.5f,1.0f, 1.0f,
0.5f, -0.5f, -0.5f,0.0f, 1.0f,
0.5f, -0.5f, -0.5f,0.0f, 1.0f,
0.5f, -0.5f, 0.5f,0.0f, 0.0f,
0.5f, 0.5f, 0.5f,1.0f, 0.0f,

-0.5f, -0.5f, -0.5f,0.0f, 1.0f,
0.5f, -0.5f, -0.5f,1.0f, 1.0f,
0.5f, -0.5f, 0.5f,1.0f, 0.0f,
0.5f, -0.5f, 0.5f,1.0f, 0.0f,
-0.5f, -0.5f, 0.5f,0.0f, 0.0f,
-0.5f, -0.5f, -0.5f,0.0f, 1.0f,

-0.5f,0.5f, -0.5f,0.0f, 1.0f,
0.5f,0.5f, -0.5f,1.0f, 1.0f,
0.5f,0.5f, 0.5f,1.0f, 0.0f,
0.5f,0.5f, 0.5f,1.0f, 0.0f,
-0.5f,0.5f, 0.5f,0.0f, 0.0f,
-0.5f,0.5f, -0.5f,0.0f, 1.0f
};

  glGenVertexArrays(1, VAO);
  glBindVertexArray(*VAO);
  
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 
                        5 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0); // Position data
  
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 
                        5 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(2); // Texture data
  
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
  
  /*float firstRectangleVertices[] = {
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
                                                             "../shaders/vertex_shader_mvp_example.glsl",
                                                            "../shaders/fragment_shader_texture_example.glsl",
                                                            &firstVAO,
                                                            0);
  firstRectangleShader.useShader();
  
  */

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
  
  /* Opacity * o = new Opacity;
  
  o->o = 0.5;
  o->shaderId = firstRectangleShader.getShaderId();*/
  
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;
  
  returnModelAndViewAndProjectionMatrices(&model, &view, &projection);
  unsigned int VAO;
  Shader cube = returnCubeShader("../shaders/vertex_shader_mvp_example.glsl",
                                 "../shaders/fragment_shader_texture_example.glsl", 
                                 &VAO);
  
  cube.useShader();
  glUniform1i(glGetUniformLocation(cube.getShaderId(), "texture1"), 0);
  glUniform1i(glGetUniformLocation(cube.getShaderId(), "texture2"), 1);

  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glm::vec3 cubePositions[] = {
  glm::vec3( 0.0f, 0.0f, 0.0f),
  glm::vec3( 2.0f, 5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3( 2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f, 3.0f, -7.5f),
  glm::vec3( 1.3f, -2.0f, -2.5f),
  glm::vec3( 1.5f, 2.0f, -2.5f),
  glm::vec3( 1.5f, 0.2f, -1.5f),
  glm::vec3(-1.3f, 1.0f, -1.5f)
  };

  while (!glfwWindowShouldClose(w)) {
    // std::cout << firstRectangleShader << ":" << secondRectangleShader << std::endl;
    // std::cout << firstVAO << ":" << secondVAO << std::endl;

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    cube.useShader();
    
    int viewLoc = glGetUniformLocation(cube.getShaderId(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    
    int projectionLoc = glGetUniformLocation(cube.getShaderId(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    processInput(w, nullptr, nullptr);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, textureId2);

    glBindVertexArray(VAO);
    
    int i = 0;
    for (auto& pos : cubePositions) {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, pos);
      float theta = 20.0f * i;
      model = glm::rotate(model, glm::radians(theta), glm::vec3(1.0f, 0.3f, 0.5f));
      int modelLoc = glGetUniformLocation(cube.getShaderId(), "model");
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      glDrawArrays(GL_TRIANGLES, 0, 36);
      i++;
    }

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
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

    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
  }

  glfwTerminate();

  return 0;
}
