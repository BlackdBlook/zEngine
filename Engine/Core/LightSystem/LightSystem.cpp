#include "LightSystem.h"


void LightSystem::RegistLightComponent(SPtr<LightComponent> Light)
{
    
}

void LightSystem::UpdateLightBufferData()
{    
    
    for(auto& l : Lights)
    {
        auto lp = l.lock();

        
    }

    

}

void LightSystem::DrawShadow()
{
    
}
