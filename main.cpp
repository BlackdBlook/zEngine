#include <iostream>
#include "Engine/zEngine.h"
#include "ToolKit/FileToolKit.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
int main()
{
    system("chcp 65001");

    Engine engine;
    engine.SetLevel(1);
    engine.Run();
    return 0;
}