#include "DrawAdvanceLight.h"

#include <memory>

#include "Objects/DrawAdvanceBox/BoxV3.h"

void DrawAdvanceLight::Init()
{
    Level::Init();

    objs.emplace_back(std::make_shared<BoxV3>());
    
}
