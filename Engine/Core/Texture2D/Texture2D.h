#pragma once
#include "../../../Header.h"
#include "Engine/Core/IBindableTexture/IBindableTexture.h"

class Texture2D : public IBindableTexture
{
    GLID unit = 0;
    GLID texture = -1;
    TexturePtr Image;
public:
    Texture2D(const char* name);
    Texture2D();
    Texture2D(const Texture2D& t) = delete;
    Texture2D(Texture2D&& t)noexcept;
    ~Texture2D();
    Texture2D& operator=(Texture2D&& t)noexcept;
    GLID GetTexture()const;
    void Bind(GLID unit = 0) override;
};

