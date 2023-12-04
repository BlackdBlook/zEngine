#include "ImgToolKit.h"
#include "../Header.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_img.h"

Texture ImgToolKit::ReadImage(const char* path)
{
    if (!FileToolKit::FileExist(path))
    {
        LOG("Img ", path, " Can not find");
        return NULL;
    }
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false);
        
    unsigned char* Data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (Data == nullptr)
    {
        LOG("Img ", path, " Can not find");
        return NULL;
    }

    LOG(path," w:",width, "h:",height,"c:",nrChannels);
    
    return std::make_shared<m_Texture>(Data, width, height, nrChannels);
}

bool m_Texture::IsValid() const
{
    return Data != nullptr;
}

m_Texture::m_Texture(unsigned char* Data
    , int width, int height, int nrChannels)
{
    this->Data = Data;
    this->width = width;
    this->height = height;
    this->nrChannels = nrChannels;
}

m_Texture::m_Texture(const m_Texture& other)
{
    Data = other.Data;
    this->width = other.width;
    this->height = other.height;
    this->nrChannels = other.nrChannels;
}

m_Texture::~m_Texture()
{
    stbi_image_free(Data);
    Data = nullptr;
}
