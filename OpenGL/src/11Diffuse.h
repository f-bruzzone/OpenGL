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
//unsigned int SetupLightCube(unsigned int vbo)
//{
//    unsigned int va;
//    glCreateVertexArrays(1, &va);
//    glBindVertexArray(va);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);
//    glBindVertexArray(0);
//    return va;
//}
//
//void RenderLight(unsigned int lightVao, Shader& shader, glm::vec3& lightLocation, glm::mat4& view, glm::mat4& perspective, float* vertices)
//{
//    shader.Bind();
//
//    glm::mat4 model = glm::mat4(1);
//    model = glm::translate(model, lightLocation);
//    model = glm::scale(model, glm::vec3(0.25f));
//    glm::mat4 mvp = perspective * view * model;
//
//    int location = shader.GetUniformLocation("u_MVP");
//    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);
//
//    glBindVertexArray(lightVao);
//    glDrawArrays(GL_TRIANGLES, 0, 36);
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
//        //std::vector<float> vertices;
//        //ObjReader reader;
//        //reader.ParseObject("res/models/Model.txt", vertices);
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
//        unsigned int lightVAO = SetupLightCube(vbo);
//
//        Shader shader{ "res/shaders/Group2/CrateShader.shader" };
//        Shader lightShader{ "res/shaders/Group2/LightShader.shader" };
//
//        Texture diffuse{ "res/textures/container2.png" };
//        Texture specular{ "res/textures/container2_specular.png" };
//
//        glm::vec3 lightLocation = glm::vec3(2.0f, 2.0f, 2.0f);
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
//            shader.Bind();
//
//            diffuse.Bind(0);
//            specular.Bind(1);
//            int diffuseTex = shader.GetUniformLocation("material.diffuse");
//            int specularTex = shader.GetUniformLocation("material.specular");
//            glUniform1i(diffuseTex, 0);
//            glUniform1i(specularTex, 1);
//
//            int mvpLocation = shader.GetUniformLocation("u_MVP");
//            int lightPosition = shader.GetUniformLocation("u_LightLocation");
//            int cameraShaderLoc = shader.GetUniformLocation("u_CameraPosition");
//
//            glm::mat4 projection = camera.GetPerspectiveMat();
//            view = camera.GetViewMat();
//            model = glm::scale(glm::mat4(1), glm::vec3(1));
//            mvp = projection * view * model;
//
//            auto cameraPosition = model * glm::vec4(camera.GetPosition(), 1.0f);
//
//            glUniform3fv(lightPosition, 1, &lightLocation[0]);
//            glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvp[0][0]);
//            glUniform3fv(cameraShaderLoc, 1, &cameraPosition[0]);
//
//            //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
//
//            glBindVertexArray(vao);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//
//            RenderLight(lightVAO, lightShader, lightLocation, view, projection, vertices);
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
