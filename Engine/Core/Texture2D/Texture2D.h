#pragma once
#include "../../../Header.h"
class Texture2D
{
    GLID unit = 0;
    GLID texture = -1;
public:
    Texture2D(const char* name);
    Texture2D();
    Texture2D(const Texture2D& t);
    Texture2D(Texture2D&& t)noexcept;
    ~Texture2D();
    void operator=(Texture2D&& t)noexcept;
    GLID GetTexture()const;
    void Bind(GLID unit = 0);
};

