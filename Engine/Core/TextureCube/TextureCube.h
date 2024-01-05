﻿#pragma once
#include <string>
#include <vector>

#include "Engine/Core/IBindableTexture/IBindableTexture.h"
#include "ToolKit/ImgToolKit.h"
#include "ToolKit/Typedef.h"




class TextureCube : public IBindableTexture
{
public:
    std::vector<TexturePtr> ts;

    GLID textureID;

    TextureCube();
    
    TextureCube(const std::vector<std::string>& cube);

    void use(int index = 0);

private:

    void loadCubemap(const std::vector<std::string>& faces);
    void Bind(GLID unit) override;
};
