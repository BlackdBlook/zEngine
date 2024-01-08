#pragma once
#include "Objects/Light/LightComponent.h"

#define LightNumber 0.5f

class DirectLightWithUbo : public LightComponent
{
    glm::vec3 direction = {-0.2f, -1.0f, -0.3f};
    glm::vec3 color = {1.f, 1.f, 1.f};
    glm::vec3 ambient = {0, 0, 0};
    glm::vec3 diffuse = {LightNumber, LightNumber, LightNumber};
    glm::vec3 specular = {LightNumber, LightNumber, LightNumber};

    uint8 DirtyMask = 0;
public:

    [[nodiscard]] glm::vec3 get_direction() const
    {
        return direction;
    }

    void set_direction(const glm::vec3& direction)
    {
        DirtyMask |= 1 << 0;
        this->direction = direction;
    }

    [[nodiscard]] glm::vec3 get_color() const
    {
        return color;
    }

    void set_color(const glm::vec3& color)
    {
        DirtyMask |= 1 << 1;
        this->color = color;
    }

    [[nodiscard]] glm::vec3 get_ambient() const
    {
        return ambient;
    }

    void set_ambient(const glm::vec3& ambient)
    {
        DirtyMask |= 1 << 2;
        this->ambient = ambient;
    }

    [[nodiscard]] glm::vec3 get_diffuse() const
    {
        return diffuse;
    }

    void set_diffuse(const glm::vec3& diffuse)
    {
        DirtyMask |= 1 << 3;
        this->diffuse = diffuse;
    }

    [[nodiscard]] glm::vec3 get_specular() const
    {
        return specular;
    }

    void set_specular(const glm::vec3& specular)
    {
        DirtyMask |= 1 << 4;
        this->specular = specular;
    }

    
    void DisableLight() override;
    void InitLightBuffer() override;
    void UpdateLightBuffer() override;
};
