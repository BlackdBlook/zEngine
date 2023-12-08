#include "Camera.h"

#include "Engine/Component/Component.h"
#include "Engine/Core/Level.h"
#include "Engine/Core/GlobalUnifromBuffer/GlobalUniformBuffer.h"
#include "ToolKit/QuaternionUtils/QuaternionUtils.h"

struct CameraUniformBuffer
{
    glm::mat4 view;
    glm::mat4 projection;
};

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

Camera::Camera(std::function<void(float)> update)
{
    Reset(update);
}

void Camera::Reset(std::function<void(float)> update)
{
    pos = VEC3_ZERO;

    rot = VEC3_ZERO;

    needUpdateView = true;

    updateFun = update;

    auto projection = GetCameraProjection();
    
    SetGlobalUniformBuffer("Matrices", projection, offsetof(CameraUniformBuffer, projection));    
}

void Camera::Update(float DeltaTime)
{
    Object::Update(DeltaTime);
    updateFun(DeltaTime);
    auto view = GetCameraView();

    SetGlobalUniformBuffer("Matrices", view, offsetof(CameraUniformBuffer, view));
}

void Camera::Attach(std::shared_ptr<Component> Target)
{
    // 相机禁止挂载组件
    assert(false);
}

void Camera::Dettach(std::shared_ptr<Component> Target)
{
    assert(false);
}

glm::mat4 Camera::GetCameraView()
{
    if (needUpdateView)
    {
        needUpdateView = false;
        // auto font = -GetFont();
        // auto right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), font));
        // auto up = glm::normalize(glm::cross(font, right));
        viewmat = glm::lookAt(pos, pos + GetFont(), GetUp());
    }
    return viewmat;
}

glm::mat4 Camera::GetCameraProjection()
{
    static const glm::mat4 projection =
        glm::perspective(glm::radians(90.0f),
        2560.0f / 1440, 0.1f, 100.0f);
    return projection;
}

void Camera::SetPos(const glm::vec3& pos)
{
    needUpdateView = true;
    
    Object::SetPos(pos);
}

void Camera::SetRot(const glm::vec3& newRot)
{
    needUpdateView = true;
    Object::SetRot(newRot);
}

void Camera::SetRot(const glm::quat& newRot)
{
    needUpdateView = true;
    Object::SetRot(newRot);
}

void Camera::AddRot(const glm::vec3& newRot)
{
    Object::AddRot(newRot);
    needUpdateView = true;
}

void Camera::SetLookAt(const glm::vec3& pos)
{
    auto f = pos -  GetPos();
    glm::vec3 forward = glm::normalize(f);

    // 将前向量转换为四元数
    glm::quat quaternion = glm::quatLookAt(forward, glm::vec3(0, 1, 0));
    
    SetRot(quaternion);
}

glm::vec3 Camera::GetFont()
{
    return QuaternionUtils::forwardVectorFromQuat(rot);
}

glm::vec3 Camera::GetRight()
{
    return glm::normalize(
        glm::cross(
            glm::vec3{0,1,0}
            ,
            GetFont()
    ));
}

glm::vec3 Camera::GetUp()
{
    return glm::normalize(
        glm::cross(
            GetFont()
            ,
            GetRight()
    ));
}
