//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
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
//        // triangle 1
//        float vertices1[] = {
//            -0.5f, -0.5f,
//            0.5f, -0.5f,
//            0.5f, 0.5f
//        };
//
//        unsigned int vao1;
//        glGenVertexArrays(1, &vao1);
//        glBindVertexArray(vao1);
//
//        unsigned int vbo1;
//        glGenBuffers(1, &vbo1);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo1);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
//
//
//        // triangle 2
//        float vertices2[] = {
//            -0.5f, -0.5f,
//            0.5f, 0.5f,
//            -0.5f, 0.5f
//        };
//
//        unsigned int vao2;
//        glGenVertexArrays(1, &vao2);
//        glBindVertexArray(vao2);
//
//        unsigned int vbo2;
//        glGenBuffers(1, &vbo2);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo2);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
//
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
//            glBindVertexArray(vao1);
//            glDrawArrays(GL_TRIANGLES, 0, 3);
//
//
//            glBindVertexArray(vao2);
//            glDrawArrays(GL_TRIANGLES, 0, 3);
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