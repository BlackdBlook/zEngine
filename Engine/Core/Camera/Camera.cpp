#include "Camera.h"

Camera* Camera::malloc()
{
    void* ans = ::malloc(sizeof(Camera));
    return static_cast<Camera*>(ans);
}

Camera* Camera::GetCamera()
{
    static Camera* camera = new Camera();
    return camera;
}

Camera::Camera()
{
    Reset();
}

Camera::Camera(std::function<void(void)> update)
{
    Reset(update);
}

void Camera::Reset(std::function<void(void)> update)
{
    pos = glm::vec3(0,0,0);

    font = glm::vec3(1,0,0);

    needUpdateView = true;

    updateFun = update;
}

void Camera::Update()
{
    updateFun();
}

glm::mat4 Camera::GetCameraView()
{
    if (needUpdateView)
    {
        needUpdateView = false;
        auto font = GetFont();
        auto right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), font));
        auto up = glm::normalize(glm::cross(font, right));
        viewmat = glm::lookAt(pos, pos - font, up);
    }
    return viewmat;
}

glm::vec3 Camera::GetPos()
{
    return pos;
}

void Camera::SetPos(glm::vec3 pos)
{
    needUpdateView = true;
    this->pos = pos;
}

//glm::vec3 Camera::GetRot()
//{
//    return rot;
//}
//
//void Camera::SetRot(glm::vec3 rot)
//{
//    this->rot = rot;
//    needUpdateView = true;
//}

void Camera::SetFont(glm::vec3 font)
{
    this->font = font;
    needUpdateView = true;
}

glm::vec3 Camera::GetFont()
{
    return font;
}