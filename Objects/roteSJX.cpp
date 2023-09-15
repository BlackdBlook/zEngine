#include "roteSJX.h"
#include "../Engine/Core/ShaderProgram.h"
#include "../Header.h"
#include <cmath>
#define SHADERNAME "rtsjx"


roteSJX::roteSJX(bool b)
{
    program = std::make_shared<ShaderProgram>(SHADERNAME, SHADERNAME);
    program->use();
    this->b = b;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    float vertices[] = {
        // ÃÂÃÂ»ÃÂÃÂ              // ÃÂÃÂÃÂÃÂ«
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ÃÂÃÂÃÂÃÂ
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ÃÂÃÂ³ÃÂÃÂ
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ÃÂ¶ÃÂ¥ÃÂ²ÃÂ¿
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void roteSJX::Draw()
{
    glBindVertexArray(vao);
    program->use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void roteSJX::Update()
{
    double lerp = (sin(glfwGetTime())) / 2.0f + 0.5;

    glm::mat4 rt(1.0f);
    rt = glm::rotate(rt, 
        glm::radians((float)(360.0f * (b? lerp: 1 - lerp))),
        glm::vec3(1.0, 1.0, 1.0));
    program->setUniform("transform",rt);
}

roteSJX::~roteSJX()
{
    glDeleteBuffers(1,&vbo);
    glDeleteVertexArrays(1, &vao);
}
