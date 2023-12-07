#include "Texture2D.h"
#include "../../../ToolKit/ImgToolKit.h"
#include "Engine/SubSystem/AssetSystem.h"

Texture2D::Texture2D(const char* name)
{
    Image = AssetSystem::GetInstance()->LoadImage(name);
    
    if (Image != nullptr && Image->IsValid())
    {
        GLenum channel;

        switch (Image->nrChannels)
        {
        case 4:
            channel = GL_RGBA;
            break;
        case 3:
        default:
            channel = GL_RGB;
            break;
        }
        
        glGenTextures(1,&texture);
        glBindTexture(GL_TEXTURE_2D,texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, channel, Image->width, Image->height,
            0, channel, GL_UNSIGNED_BYTE, Image->Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

Texture2D::Texture2D()
{

}

Texture2D::Texture2D(Texture2D&& t) noexcept
{
    this->texture = t.texture;
    t.texture = 0;
    this->unit = t.unit;
    t.unit = 0;
    this->Image = std::move(t.Image);
    t.Image = nullptr;
}

Texture2D::~Texture2D()
{
     glDeleteTextures(1, &texture);
}

Texture2D& Texture2D::operator=(Texture2D&& t)noexcept
{
    this->texture = t.texture;
    t.texture = 0;
    this->unit = t.unit;
    t.unit = 0;
    this->Image = std::move(t.Image);
    t.Image = nullptr;
    return *this;
}

GLID Texture2D::GetTexture() const
{
    return texture;
}

void Texture2D::Bind(GLID unit)
{
    if(texture == 0)
    {
        LOG("Texture are already deleted");
        return;
    }
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D,texture);
}
