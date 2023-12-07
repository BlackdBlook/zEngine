#pragma once
#include "Objects/DrawAdvanceBox/BoxV3.h"

class PlaneWithLight : public Object
{
public:
    Texture2D Tex;
    Texture2D specular;
    GLID vao,vbo;

    std::shared_ptr<ShaderProgram> shader;

    std::vector<std::shared_ptr<PointLightV2>> PointLight;

    void initDirectLight();
    
    void initPointLight(int index);
    void updatePointLight(int index);
    
    void initSpotLight();
    void updateSpotLight();

    
    PlaneWithLight(const char* diff, const char* spec);
    void Start() override;
    void Update(float DeltaTime) override;
    void Draw() override;
    ~PlaneWithLight() override;
    void addLight(std::shared_ptr<PointLightV2> light);
};
