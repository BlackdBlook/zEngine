#pragma once
#include <glm/vec3.hpp>

#include "Engine/zEngine.h"
#include "Engine/Core/Camera/Camera.h"

class Camera;
class InputSystem;

class CamRot
{
    glm::vec3 rot {0};
    Camera* cam = Camera::GetCamera();
    GLFWwindow* window = nullptr;
    double tempX, tempY;
public:
    void Update(float DeltaTime);
};
