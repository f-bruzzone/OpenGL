//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include "vendor/glm/gtc/matrix_transform.hpp"
//#include "classes/Window.h"
//#include "classes/Time.h"
//#include "classes/Camera.h"
//#include "classes/Shader.h"
//
//int main(void)
//{
//    std::shared_ptr<Window> window = std::make_shared<Window>();
//
//    if (glewInit() != GLEW_OK)
//        std::cout << "Error initializing glew!" << std::endl;
//
//    std::cout << glGetString(GL_VERSION) << std::endl;
//    std::cout << glGetString(GL_RENDERER) << std::endl;
//
//    glfwSwapInterval(1);
//
//    Camera camera{ window };
//
//    {
//
//        float vertices[] = {
//           -1.0f, -1.0f, -1.0f, 0.0f, 0.8f, 0.6f, 1.0f,
//           1.0f, -1.0f, -1.0f,  1.0f, 0.3f, 0.1f, 1.0f,
//           1.0f, -1.0f, 1.0f,   0.7f, 0.0f, 0.5f, 1.0f,
//           -1.0f, -1.0f, 1.0f,  0.4f, 0.7f, 0.9f, 1.0f,
//           -1.0f, 1.0f, -1.0f,  0.1f, 0.3f, 0.5f, 1.0f,
//           1.0f, 1.0f, -1.0f,   0.6f, 0.6f, 0.4f, 1.0f,
//           1.0f, 1.0f, 1.0f,    0.3f, 0.8f, 0.8f, 1.0f,
//           -1.0f, 1.0f, 1.0f,   0.8f, 0.4f, 0.0f, 1.0f
//        };
//
//        unsigned int indices[] = { 0, 1, 5, 5, 4, 0, 1, 2, 6, 6, 5, 1, 2, 3, 7, 7, 6, 2, 3, 0, 4, 4, 7, 3, 4, 5, 6, 6, 7, 4, 0, 1, 2, 2, 3, 0 };
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
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);
//
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));
//
//
//        Shader shader{ "res/shaders/MVPCubeShader.shader" };
//        shader.Bind();
//        int mvpLocation = shader.GetUniformLocation("u_MVP");
//
//
//        glm::mat4 mvp;
//
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LESS);
//
//        /* Loop until the user closes the window */
//        while (!window->WindowShouldClose())
//        {
//            Time::UpdateTime();
//
//            /* Render here */
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//            camera.UpdateCamera();
//
//
//            glm::mat4 projection = camera.GetPerspectiveMat();
//            glm::mat4 view = camera.GetViewMat();
//            glm::mat4 model = glm::scale(glm::mat4(1), glm::vec3(1));
//            mvp = projection * view * model;
//
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//
//            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
//
//
//            /* Swap front and back buffers */
//            glfwSwapBuffers(window->GetWindow());
//
//            /* Poll for and process events */
//            glfwPollEvents();
//        }
//    }
//
//    window->Terminate();
//    return 0;
//}
//
