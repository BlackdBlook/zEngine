#include <iostream>
#include "Engine/zshEngine.h"
#include "ToolKit/FileToolKit.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define LogVec3(s) s.x << ' ' << s.y << ' ' << s.z
using namespace std;
int main()
{
    Engine engine;
    engine.SetLevel(1);
    engine.Run();
    return 0;
}