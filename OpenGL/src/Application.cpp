#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "vendor/glm/gtc/matrix_transform.hpp"
#include "classes/Window.h"
#include "classes/Time.h"
#include "classes/Camera.h"
#include "classes/Shader.h"
#include "classes/ObjReader.h"
#include "classes/Texture.h"

void RenderQuad(unsigned int vao, Shader& screenShader, unsigned int frameTexture)
{
    screenShader.Bind();
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, frameTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RenderCube(const Shader& shader, unsigned int vao, const glm::mat4& view, const glm::mat4& perspective, const glm::vec3& position)
{
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, position);
    glm::mat4 mvp = perspective * view * model;

    int location = shader.GetUniformLocation("u_MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void RenderPlane(const Shader& shader, const Texture& texture, unsigned int vao, const glm::mat4& view, const glm::mat4& perspective, const glm::vec3& position)
{
    shader.Bind();
    glm::mat4 model = glm::mat4(1);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(10.0f));
    glm::mat4 mvp = perspective * view * model;

    int location = shader.GetUniformLocation("u_MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

    texture.Bind(0);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 24, 6);
}

void RenderWindow(const Shader& shader, const Texture& texture, unsigned int vao, const glm::mat4& view, const glm::mat4& perspective, const glm::vec3& position)
{
    shader.Bind();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 mvp = perspective * view * model;

    int location = shader.GetUniformLocation("u_MVP");
    glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

    texture.Bind(0);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(void)
{
    std::shared_ptr<Window> window = std::make_shared<Window>();

    if (glewInit() != GLEW_OK)
        std::cout << "Error initializing glew!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    std::cout << glGetString(GL_RENDERER) << std::endl;

    glfwSwapInterval(1);

    Camera camera{ window };

    {
        float triangleVerts[] = {
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

        unsigned int screenVAO;
        glGenVertexArrays(1, &screenVAO);
        glBindVertexArray(screenVAO);

        unsigned int screenVBO;
        glGenBuffers(1, &screenVBO);
        glBindBuffer(GL_ARRAY_BUFFER, screenVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVerts), triangleVerts, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

        float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
        };

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        unsigned int vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(sizeof(float) * 6));
        glBindVertexArray(0);

        // Create framebuffer and texture object
        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        unsigned int frameColorBufferTex;
        glGenTextures(1, &frameColorBufferTex);
        glBindTexture(GL_TEXTURE_2D, frameColorBufferTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 960, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);

        // Attach the color buffer to the framebuffer
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameColorBufferTex, 0);

        // Create render buffer object for stencil and depth testing because we will only be sampling from color buffer
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 960, 720);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // Attach the render buffer to the depth and stencil attachment of the framebuffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Error: Framebuffer is not complete!";
        glBindFramebuffer(GL_FRAMEBUFFER, 0);


        Shader shader{ "res/shaders/Group2/Blending.shader" };
        Shader screenShader{ "res/shaders/Group2/ScreenShader.shader" };
        Texture texture{ "res/textures/container2.png" };
        Texture planeTex{ "res/textures/marble.png" };
        Texture windowTex{ "res/textures/blending_transparent_window.png" };

        glm::mat4 mvp;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;


        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        /* Loop until the user closes the window */
        while (!window->WindowShouldClose())
        {
            Time::UpdateTime();

            glBindFramebuffer(GL_FRAMEBUFFER, fbo);
            glEnable(GL_DEPTH_TEST);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            camera.UpdateCamera();

            shader.Bind();
            texture.Bind(0);

            projection = camera.GetPerspectiveMat();
            view = camera.GetViewMat();

            RenderCube(shader, vao, view, projection, glm::vec3(-1.0f, 0.0f, 0.0f));
            RenderCube(shader, vao, view, projection, glm::vec3(2.0f, 0.0f, -1.0f));

            RenderPlane(shader, planeTex, vao, view, projection, glm::vec3(0.0f, 4.5f, 0.0f));

            RenderWindow(shader, windowTex, vao, view, projection, glm::vec3(1.0f, 0.0f, 1.0f));
            RenderWindow(shader, windowTex, vao, view, projection, glm::vec3(1.0f, 0.0f, 0.0f));


            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glDisable(GL_DEPTH_TEST);
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            RenderQuad(screenVAO, screenShader, frameColorBufferTex);

            /* Swap front and back buffers */
            glfwSwapBuffers(window->GetWindow());

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    window->Terminate();
    return 0;
}

