#include "TextureCube.h"
#include "Header.h"
#include "Engine/SubSystem/AssetSystem.h"
#include "ToolKit/stb_img.h"

void TextureCube::loadCubemap(const std::vector<std::string>& faces)
{
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        std::string path = AssetSystem::GetInstance()->GetFilePathByName(faces[i]);
        
        TexturePtr t = AssetSystemIns->LoadImage(faces[i]);
        if(t->IsValid())
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, t->width, t->height,
                         0, GL_RGB, GL_UNSIGNED_BYTE, t->Data
            );
            ts.push_back(t);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            return;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void TextureCube::Bind(GLID unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}


TextureCube::TextureCube()
{
    textureID = 0;
}

TextureCube::TextureCube(const std::vector<std::string>& cube)
{
    loadCubemap(cube);
}

void TextureCube::use(int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}
