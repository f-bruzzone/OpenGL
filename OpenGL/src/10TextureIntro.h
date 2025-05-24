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
//#include "classes/VariableTexture.h"
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
//    float vertices[] = {
//        // positions          // normals           // texture coords
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//    };
//
//    {
//        unsigned int vao;
//        glCreateVertexArrays(1, &vao);
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
//
//
//        Shader shader{ "res/shaders/Group2/TextureShader.shader" };
//        shader.Bind();
//
//        VariableTexture texture1{ "res/textures/texture.png", TextureType::Trilinear };
//        VariableTexture texture2{ "res/textures/texture.png", TextureType::Nearest };
//        VariableTexture texture3{ "res/textures/texture.png", TextureType::Linear };
//        VariableTexture texture4{ "res/textures/texture.png", TextureType::Anisotropic };
//
//        int mvpLocation = shader.GetUniformLocation("u_MVP");
//
//        glm::mat4 mvp;
//        glm::mat4 model;
//        glm::mat4 view;
//
//        glClearColor(0.1f, 0.1f, 0.5f, 1.0f);
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
//            view = camera.GetViewMat();
//            model = glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
//            mvp = projection * view * model;
//
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//            texture2.Bind(0);
//
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//
//            // Cube two
//            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//            mvp = projection * view * model;
//
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//            texture3.Bind(0);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//            // Cube three
//            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//            mvp = projection * view * model;
//
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//            texture1.Bind(0);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//
//            // Cube four
//            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//            mvp = projection * view * model;
//
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//            texture4.Bind(0);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
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
