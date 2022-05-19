#pragma once
#include "../../Object/Object.h"
#include "../../../Header.h"
class Camera :public Object
{
    glm::mat4 viewmat;
    glm::vec3 pos;
    glm::vec3 font;
    std::function<void(void)> updateFun;
    bool needUpdateView = true;
    static Camera* malloc();
public:

    void* operator new(size_t s)
    {
        //static Camera* cam = malloc();
        auto malloc = []() ->Camera*
        {
            void* cam = ::malloc(sizeof(Camera));
            if (cam == 0)
                return nullptr;
            memset(cam, 0, sizeof(Camera));
            Camera* ans = static_cast<Camera*>(cam);
            ans->Camera::Camera();
            return ans;
        };
        static Camera* cam = malloc();
        cam->Reset();
        return cam;
    }
    static Camera* GetCamera();

    virtual void Update() override;

    Camera();
    Camera(std::function<void(void)> update);
    void Reset(std::function<void(void)> update = []() {});
    glm::mat4 GetCameraView();
    glm::vec3 GetPos();
    void SetPos(glm::vec3 pos);
    /*glm::vec3 GetRot();
    void SetRot(glm::vec3 rot);*/
    void SetFont(glm::vec3);
    glm::vec3 GetFont();
};

