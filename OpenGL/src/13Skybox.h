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
//    {
//        std::vector<float> vertices;
//        ObjReader reader;
//        reader.ParseObject("res/models/Model.txt", vertices);
//
//        unsigned int vao;
//        glGenVertexArrays(1, &vao);
//        glBindVertexArray(vao);
//
//        unsigned int vbo;
//        glGenBuffers(1, &vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
//
//        glEnableVertexAttribArray(1);
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));
//
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 5));
//
//
//        Shader shader{ "res/shaders/Group2/CubeMap.shader" };
//        shader.Bind();
//
//        VariableTexture cubeMap{ "res/textures/skybox", TextureType::CubeMap };
//
//        int mvpLocation = shader.GetUniformLocation("u_MVP");
//
//        glm::mat4 mvp;
//        glm::mat4 view;
//        glm::mat4 projection;
//
//        glClearColor(0.1f, 0.1f, 0.5f, 1.0f);
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LESS);
//
//        /* Loop until the user closes the window */
//        while (!window->WindowShouldClose())
//        {
//            Time::UpdateTime();
//            camera.UpdateCamera();
//
//            /* Render here */
//            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
//            projection = camera.GetPerspectiveMat();
//            view = camera.GetViewMat();
//            //view = glm::mat4(glm::mat3(camera.GetViewMat())); // Disconnect from translation transformations to keep this cube in place.
//            glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
//
//            mvp = projection * view * model;
//
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//
//            cubeMap.BindCubeMap(0);
//            glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 8);
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
