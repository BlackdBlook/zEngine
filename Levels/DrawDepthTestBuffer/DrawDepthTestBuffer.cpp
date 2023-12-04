#include "DrawDepthTestBuffer.h"

#include "Engine/zEngine.h"
#include "Engine/Component/Model/Model.h"
#include "Engine/Core/Camera/Camera.h"
#include "Engine/Core/InputSystem/InputSystem.h"
#include "Objects/PointLightV2.h"


class TurnModelScript : public Object
{
    struct POINT
    {
        double x;
        double y;
    };

public:
    TurnModelScript(std::shared_ptr<Object> Target) : Target(Target)
    {
        
    }
    void Start() override
    {
        input = InputSystem::GetInstance();
        //window = Engine::GetInstance()->GetWindow();
    }
    void Update(float DeltaTime) override
    {
        if(input)
        {
            if(input->GetMouseButtonDown(true))
            {
                if(window == nullptr)
                {
                    window = Engine::GetInstance()->GetWindow();
                    glfwGetCursorPos(window,&tempPoint.x ,&tempPoint.y);
                    return;
                }
                POINT x;
                glfwGetCursorPos(window,&x.x ,&x.y);

                Target->SetRot(Target->GetRot() + glm::vec3{0, x.x - tempPoint.x, 0});
                
                tempPoint = x;
            }else
            {
                if(window)
                {
                    window = nullptr;
                }
            }
        }
    }
    void Draw() override
    {
        
    }
    ~TurnModelScript() override = default;

private:
    POINT tempPoint = { 10,10 };
    InputSystem* input = nullptr;
    GLFWwindow* window = nullptr;
    std::shared_ptr<Object> Target;
};


void DrawDepthTestBuffer::Init()
{
    Level::Init();

    Level::Init();

    Camera::GetCamera()->Reset();
    Camera::GetCamera()->SetPos(glm::vec3(0,0,10));
    
    {
        std::string name = std::string{"nanosuit.obj"};
        std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>(
            "NanoSuit0", "DepthTest");

        auto m = std::make_shared<Model>(std::move(name), sp);
        objs.push_back(m);
        m->SetPos(glm::vec3{5,-10,0});
        m->SetRot(glm::vec3{0,0,0});

        objs.push_back(std::make_shared<TurnModelScript>(m));
    }

    {
        std::string name = std::string{"nanosuit.obj"};
        std::shared_ptr<ShaderProgram> sp = std::make_shared<ShaderProgram>(
            "NanoSuit0", "DepthTest");

        auto m = std::make_shared<Model>(std::move(name), sp);
        objs.push_back(m);
        m->SetPos(glm::vec3{-5,-10,-10});
        m->SetRot(glm::vec3{0,0,0});
        
        objs.push_back(std::make_shared<TurnModelScript>(m));
    }
    
}
