//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//
//#include "vendor/glm/gtc/matrix_transform.hpp"
//#include "classes/Window.h"
//#include "classes/Time.h"
//#include "classes/Camera.h"
//#include "classes/Shader.h"
//#include "classes/ObjReader.h"
//#include "classes/Texture.h"
//
//
//void RenderCube(const Shader& shader, unsigned int vao, const glm::mat4& view, const glm::mat4& perspective, const glm::vec3& position)
//{
//    glm::mat4 model = glm::mat4(1);
//    model = glm::translate(model, position);
//    glm::mat4 mvp = perspective * view * model;
//
//    int location = shader.GetUniformLocation("u_MVP");
//    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
//
//    glBindVertexArray(vao);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
//}
//
//void RenderPlane(const Shader& shader, const Texture& texture, unsigned int vao, const glm::mat4& view, const glm::mat4& perspective, const glm::vec3& position)
//{
//    shader.Bind();
//    glm::mat4 model = glm::mat4(1);
//    model = glm::translate(model, position);
//    model = glm::scale(model, glm::vec3(10.0f));
//    glm::mat4 mvp = perspective * view * model;
//
//    int location = shader.GetUniformLocation("u_MVP");
//    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
//
//    texture.Bind(0);
//    glBindVertexArray(vao);
//    glDrawArrays(GL_TRIANGLES, 24, 6);
//}
//
//void RenderWindow(const Shader& shader, const Texture& texture, unsigned int vao, const glm::mat4& view, const glm::mat4& perspective, const glm::vec3& position)
//{
//    shader.Bind();
//    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
//    glm::mat4 mvp = perspective * view * model;
//
//    int location = shader.GetUniformLocation("u_MVP");
//    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
//
//    texture.Bind(0);
//    glBindVertexArray(vao);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//}
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
//        float vertices[] = {
//            // positions          // normals           // texture coords
//            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//        };
//
//        unsigned int vao;
//        glGenVertexArrays(1, &vao);
//        glBindVertexArray(vao);
//
//        unsigned int vbo;
//        glGenBuffers(1, &vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
//
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
//
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
//        glBindVertexArray(0);
//
//
//        Shader shader{ "res/shaders/Group2/Blending.shader" };
//        Texture texture{ "res/textures/container2.png" };
//        Texture planeTex{ "res/textures/marble.png" };
//        Texture windowTex{ "res/textures/blending_transparent_window.png" };
//
//        glm::mat4 mvp;
//        glm::mat4 model;
//        glm::mat4 view;
//        glm::mat4 projection;
//
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LESS);
//
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
//            shader.Bind();
//            texture.Bind(0);
//
//            projection = camera.GetPerspectiveMat();
//            view = camera.GetViewMat();
//
//            RenderCube(shader, vao, view, projection, glm::vec3(-1.0f, 0.0f, 0.0f));
//            RenderCube(shader, vao, view, projection, glm::vec3(2.0f, 0.0f, -1.0f));
//
//            RenderPlane(shader, planeTex, vao, view, projection, glm::vec3(0.0f, 4.5f, 0.0f));
//
//            RenderWindow(shader, windowTex, vao, view, projection, glm::vec3(1.0f, 0.0f, 1.0f));
//            RenderWindow(shader, windowTex, vao, view, projection, glm::vec3(1.0f, 0.0f, 0.0f));
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
