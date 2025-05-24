//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//
//#include <iostream>
//#include "vendor/glm/gtc/matrix_transform.hpp"
//#include "classes/Window.h"
//#include "classes/Time.h"
//#include "classes/Camera.h"
//#include "classes/Shader.h"
//#include "classes/ObjReader.h"
//#include "classes/Texture.h"
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
//        // calculate tangent vectors
//        std::vector<glm::vec3> tangents;
//        reader.BuildObjectTangents(vertices, 8, tangents);
//
//        unsigned int vao;
//        glCreateVertexArrays(1, &vao);
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
//        // build vertex buffer for the tangents
//        unsigned int tbo;
//        glGenBuffers(1, &tbo);
//        glBindBuffer(GL_ARRAY_BUFFER, tbo);
//        glBufferData(GL_ARRAY_BUFFER, tangents.size() * sizeof(glm::vec3), tangents.data(), GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(3);
//        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0);
//
//        glEnableVertexAttribArray(4);
//        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) * 3));
//
//        Shader shader{ "res/shaders/Group2/TextureLightShader1.shader" };
//        shader.Bind();
//
//        Texture texture{ "res/textures/marble.png" };
//        Texture normalMap{ "res/textures/marble-normals.png" };
//
//        int texLocation = shader.GetUniformLocation("u_Texture");
//        int normalLocation = shader.GetUniformLocation("u_NormalMap");
//
//        glUniform1i(texLocation, 0);
//        glUniform1i(normalLocation, 1);
//
//        texture.Bind(0);
//        normalMap.Bind(1);
//
//        int mvpLocation = shader.GetUniformLocation("u_MVP");
//        int diffuseColorLocation = shader.GetUniformLocation("u_DiffuseColor");
//        int lightPowerLocation = shader.GetUniformLocation("u_LightPower");
//        int lightPositionLocation = shader.GetUniformLocation("u_LightPosition");
//        int modelLocation = shader.GetUniformLocation("u_Model");
//        int viewLocation = shader.GetUniformLocation("u_View");
//
//        glUniform3f(diffuseColorLocation, 1.0f, 0.5f, 0.5f);
//        glUniform1f(lightPowerLocation, 20.0f);
//        glUniform3f(lightPositionLocation, -3.0f, 3.0f, -3.0f);
//
//        glm::mat4 mvp;
//        glm::mat4 model;
//        glm::mat4 view;
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
//            view = camera.GetViewMat();
//            model = glm::scale(glm::mat4(1), glm::vec3(1));
//            mvp = projection * view * model;
//
//            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
//            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//
//            glDrawArrays(GL_TRIANGLES, 0, 6);
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
