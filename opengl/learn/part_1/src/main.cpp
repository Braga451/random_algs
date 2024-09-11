#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

std::string readShader(const std::string& shaderPath) {
  std::ifstream shaderFile(shaderPath);

  if (!shaderFile.is_open()) {
    std::cerr << "Error reading shader!" << std::endl;
    return "";
  }
  
  std::string shaderLine;
  std::string shaderContent;

  while (getline(shaderFile, shaderLine)) {
    shaderContent += shaderLine + "\n";
  }
  
  shaderFile.close();
  
  std::cout << "Shader content: " << shaderContent << std::endl;

  return shaderContent;
}

unsigned int createShader(const std::string& shaderPath, const GLenum& shaderType) {
  const std::string shaderContent = readShader(shaderPath);
  const char * shaderContentCStr = shaderContent.c_str();
  
  if (shaderContent == "") {
    return -1;
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
    return -1;
  }

  else {
    std::cout << "Shader compiled!" << std::endl;
  }

  return shader;
}

unsigned int returnTriangleShader() {
  float vertices[] = {
    -1.0f, -1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
  };
  
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  unsigned int vertexShader = createShader("../shaders/vertex_shader.glsl", GL_VERTEX_SHADER);
  unsigned int fragmentShader = createShader("../shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER);
  
  if (vertexShader == -1 || fragmentShader == -1) {
    return -1;
  }

  unsigned int shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  char linkedLog[512];
  int isLinked;
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isLinked);

  if (!isLinked) {
    glGetProgramInfoLog(shaderProgram, 512, nullptr, linkedLog);

    std::cerr << "Error linking shaders: " << std::endl << linkedLog << std::endl;
  
    return -1;
  }
  else {
    std::cout << "Shaders linked!" << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return shaderProgram;
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  GLFWwindow * w = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);

  if (w == nullptr) {
    std::cerr << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return 1;
  }

  glfwMakeContextCurrent(w);

  if (!gladLoadGL(glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    return 1;
  }

  glViewport(0, 0, 800, 600);
  
  glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);

  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  
  unsigned int triangleShader = returnTriangleShader();

  while(!glfwWindowShouldClose(w) && triangleShader  != -1) {
    processInput(w);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(triangleShader);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(w);
    glfwPollEvents();
  }
  
  glfwTerminate();

  return 0;
}
