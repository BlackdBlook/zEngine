#include "DrawTexBox.h"
#include "Objects/Box/TexBox.h"

void DrawTexBox::Init()
{
    std::function<void(float)> update = [](float) {
        float radius = 10.0f;
        glm::vec3 pos(
            (float)(sin(glfwGetTime()) * radius),
            0,
            (float)(cos(glfwGetTime()) * radius)
        );
        glm::vec3 font(
            glm::normalize(pos - glm::vec3(0, 0, 0))
        );
        auto c = Camera::GetCamera();
        c->SetPos(pos);
        c->SetRot(font);
    };

    Camera::GetCamera()->Reset(update);
    objs.emplace_back(new TexBox());
    objs.emplace_back(new TexBox(glm::vec3(2,2,0)));
    objs.emplace_back(new TexBox(glm::vec3(-2,-2,0)));
    objs.emplace_back(new TexBox(glm::vec3(2,0,2)));
    objs.emplace_back(new TexBox(glm::vec3(-2,0,-2)));
}
