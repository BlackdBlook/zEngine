#pragma once
using GLID = unsigned int;
class IBindableTexture
{
public:
    virtual void Bind(GLID unit) = 0;
};
