#include "Engine/Component/Component.h"
class InputSystem;

class TurnModelScript : public Component
{
    struct POINT
    {
        double x;
        double y;
    };

public:
    
    void OnAttached() override;
    void Update(float DeltaTime) override;

    void Draw() override;
    ~TurnModelScript() override = default;

private:
    POINT tempPoint = { 10,10 };
    InputSystem* input = nullptr;
    struct GLFWwindow* window = nullptr;
};
