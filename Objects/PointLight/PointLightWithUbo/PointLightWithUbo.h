#pragma once
#include "Engine/Component/Component.h"
#include "Engine/Object/Object.h"
#include "Objects/Light/LightComponent.h"

class PointLightWithUbo : public LightComponent
{
public:
    [[nodiscard]] glm::vec3 get_color() const
    {
        return color;
    }

    void set_color(const glm::vec3& color)
    {
        this->color = color;
    }

    [[nodiscard]] glm::vec3 get_ambient() const
    {
        return ambient;
    }

    void set_ambient(const glm::vec3& ambient)
    {
        this->ambient = ambient;
    }

    [[nodiscard]] glm::vec3 get_diffuse() const
    {
        return diffuse;
    }

    void set_diffuse(const glm::vec3& diffuse)
    {
        this->diffuse = diffuse;
    }

    [[nodiscard]] glm::vec3 get_specular() const
    {
        return specular;
    }

    void set_specular(const glm::vec3& specular)
    {
        this->specular = specular;
    }

    [[nodiscard]] float get_constant() const
    {
        return constant;
    }

    void set_constant(float constant)
    {
        this->constant = constant;
    }

    [[nodiscard]] float get_linear() const
    {
        return linear;
    }

    void set_linear(float linear)
    {
        this->linear = linear;
    }

    [[nodiscard]] float get_quadratic() const
    {
        return quadratic;
    }

    void set_quadratic(float quadratic)
    {
        this->quadratic = quadratic;
    }

    [[nodiscard]] uint8 get_point_light_index_mask() const
    {
        return PointLightIndexMask;
    }

    void set_point_light_index_mask(uint8 point_light_index_mask)
    {
        PointLightIndexMask = point_light_index_mask;
    }

private:
    glm::vec3 color = glm::vec3{1};
    glm::vec3 ambient = glm::vec3{0.05f, 0.05f, 0.05f};
    glm::vec3 diffuse = glm::vec3{0.8f, 0.8f, 0.8f};
    glm::vec3 specular = glm::vec3{1.0f, 1.0f, 1.0f};
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    uint8 PointLightIndexMask = 0;

    static uint8 PointLightGlobalMask;
public:
    void initPointLight(int index);
    void updatePointLight(int index);
    void OnAttached() override;
    void OnDettached() override;
    
    void InitLightBuffer() override;
    void UpdateLightBuffer() override;
};
