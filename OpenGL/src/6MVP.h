//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "vendor/glm/gtc/matrix_transform.hpp"
//
//struct ShaderProgram
//{
//    std::string Vertex;
//    std::string Fragment;
//};
//
//ShaderProgram ParseShader(const char* file)
//{
//    std::ifstream stream(file);
//    std::string line;
//    std::stringstream ss[2];
//
//    enum ProgramType
//    {
//        Vertex = 0,
//        Fragment = 1
//    };
//
//    ProgramType type;
//
//    while (std::getline(stream, line))
//    {
//        if (line.find("#shader") != std::string::npos)
//        {
//            if (line.find("vertex") != std::string::npos)
//                type = ProgramType::Vertex;
//            else if (line.find("fragment") != std::string::npos)
//                type = ProgramType::Fragment;
//        }
//        else
//        {
//            ss[type] << line << "\n";
//        }
//    }
//
//    return { ss[ProgramType::Vertex].str(), ss[ProgramType::Fragment].str() };
//}
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    if (glewInit() != GLEW_OK)
//        std::cout << "Error initializing glew!" << std::endl;
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//    std::cout << glGetString(GL_RENDERER) << std::endl;
//
//    glfwSwapInterval(1);
//
//    {
//
//        float vertices[] = {
//            0.25f, 0.0f, 1.0f, 0.5f, 0.5f, 1.0f,
//            0.5f, 0.0f, 1.0f, 0.5f, 0.5f, 1.0f,
//            0.5f, 0.25f, 1.0f, 0.5f, 0.5f, 1.0f,
//            0.25f, 0.25f, 1.0f, 0.5f, 0.5f, 1.0f,
//
//            -0.5f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
//            -0.25f, 0.0f, 0.5f, 1.0f, 0.5f, 1.0f,
//            -0.25f, 0.25f, 0.5f, 1.0f, 0.5f, 1.0f,
//            -0.5f, 0.25f, 0.5f, 1.0f, 0.5f, 1.0f
//        };
//
//        unsigned int indices[] = { 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
//
//        unsigned int vao;
//        glCreateVertexArrays(1, &vao);
//
//        unsigned int ib;
//        glGenBuffers(1, &ib);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//        unsigned int vbo;
//        glGenBuffers(1, &vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
//
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 2));
//
//        ShaderProgram shader = ParseShader("res/shaders/MVPShader.shader");
//        const char* vertex = shader.Vertex.c_str();
//        const char* fragment = shader.Fragment.c_str();
//
//        unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
//        glShaderSource(vShader, 1, &vertex, nullptr);
//        glCompileShader(vShader);
//        unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
//        glShaderSource(fShader, 1, &fragment, nullptr);
//        glCompileShader(fShader);
//
//        unsigned int program = glCreateProgram();
//        glAttachShader(program, vShader);
//        glAttachShader(program, fShader);
//        glLinkProgram(program);
//
//
//        glm::mat4 projection = glm::perspective(glm::radians(20.0f), 640.0f / 480.0f, 0.01f, 100.0f);
//        glm::mat4 view = glm::lookAt(glm::vec3(4, 2, 2), glm::vec3(0), glm::vec3(0, 1, 0));
//        glm::mat4 model = glm::mat4(1);
//        glm::mat4 mvp = projection * view * model;
//
//
//        // check if shader compiles
//        GLint success;
//        glGetProgramiv(program, GL_LINK_STATUS, &success);
//        if (!success)
//        {
//            GLint logLength = 0;
//            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
//            if (logLength > 1)
//            {
//                //char* log = new char[logLength];
//                char* log = (char*)alloca(sizeof(char) * logLength);
//                glGetProgramInfoLog(program, logLength, NULL, log);
//                std::cerr << "Shader program linking failed: " << log << std::endl;
//            }
//        }
//
//        glUseProgram(program);
//
//
//        int location = glGetUniformLocation(program, "u_MVP");
//        glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
//
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//
//        /* Loop until the user closes the window */
//        while (!glfwWindowShouldClose(window))
//        {
//            /* Render here */
//            glClear(GL_COLOR_BUFFER_BIT);
//
//
//
//            glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
//
//
//            /* Swap front and back buffers */
//            glfwSwapBuffers(window);
//
//            /* Poll for and process events */
//            glfwPollEvents();
//        }
//    }
//
//    glfwTerminate();
//    return 0;
//}