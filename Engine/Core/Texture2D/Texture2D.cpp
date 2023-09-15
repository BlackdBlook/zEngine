#include "Texture2D.h"
#include "../../../ToolKit/ImgToolKit.h"
Texture2D::Texture2D(const char* name)
{
    Texture t = ImgToolKit::ReadImage(name);
    if (t->IsValid())
    {
        GLenum channel;

        switch (t->nrChannels)
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t->width, t->height,
            0, channel, GL_UNSIGNED_BYTE, t->Texture);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
}

Texture2D::Texture2D()
{

}

Texture2D::Texture2D(const Texture2D& t)
{
    this->texture = t.texture;
    this->unit = t.unit;
}

Texture2D::Texture2D(Texture2D&& t) noexcept
{
    this->texture = t.texture;
    this->unit = t.unit;
}

Texture2D::~Texture2D()
{
    
}

void Texture2D::operator=(Texture2D&& t)noexcept
{
    this->texture = t.texture;
    this->unit = t.unit;
}

GLID Texture2D::GetTexture() const
{
    return texture;
}

void Texture2D::Bind(GLID unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D,texture);
}
