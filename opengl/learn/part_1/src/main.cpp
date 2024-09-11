#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

std::string readShader(const std::string &shaderPath) {
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

unsigned int createShader(const std::string &shaderPath,
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

  return shader;
}

unsigned int returnTriangleShader() {
  float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
    , 1.0f, -1.0f, 0.0f};

  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  unsigned int vertexShader =
      createShader("../shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
  unsigned int fragmentShader =
      createShader("../shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);

  unsigned int shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
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

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

unsigned int returnRectangleShader(const unsigned int (&indices)[6], 
                                   const float (&vertices)[12], 
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

  unsigned int vertexShader =
      createShader("../shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
  unsigned int fragmentShader =
      createShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

  unsigned int shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
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
  
  glBindVertexArray(0);

  // std::cout << "VAO: " << VAO << std::endl;

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

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

  unsigned int firstRectangleShader = returnRectangleShader(firstRectangleIndices, 
                                                            firstRectangleVertices, 
                                                            "../shaders/fragment_shader.glsl",
                                                            &firstVAO,
                                                            0);

  unsigned int secondRectangleShader = returnRectangleShader(secondRectangleIndices, 
                                                             secondRectangleVertices, 
                                                             "../shaders/second_fragment_shader.glsl",
                                                             &secondVAO,
                                                             1);
  
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  while (!glfwWindowShouldClose(w) ) {
    // std::cout << firstRectangleShader << ":" << secondRectangleShader << std::endl;
    // std::cout << firstVAO << ":" << secondVAO << std::endl;

    processInput(w);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(firstRectangleShader);
    glBindVertexArray(firstVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glUseProgram(secondRectangleShader);
    glBindVertexArray(secondVAO);  
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);  

    glfwSwapBuffers(w);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
