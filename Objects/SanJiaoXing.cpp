#include "SanJiaoXing.h"
#include "../Engine/Core/ShaderProgram.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define SHADERNAME "SanJiaoXing"


SanJiaoXing::SanJiaoXing()
{
    program = new ShaderProgram(SHADERNAME, SHADERNAME);
    program->use();
    
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    GLID vbo;
    glGenBuffers(1, &vbo);
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

void SanJiaoXing::Draw()
{
    glBindVertexArray(vao);
    program->use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void SanJiaoXing::Update(float DeltaTime)
{
    
}
