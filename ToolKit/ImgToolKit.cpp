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
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data == nullptr)
    {
        LOG("Img ", path, " Can not find");
        return NULL;
    }

    LOG(path," w:",width, "h:",height,"c:",nrChannels);


    return std::make_shared<m_Texture>(data, width, height, nrChannels);
}

bool m_Texture::IsValid() const
{
    return Texture != nullptr;
}

m_Texture::m_Texture(unsigned char* texture, int width, int height, int nrChannels)
{
    Texture = texture;
    this->width = width;
    this->height = height;
    this->nrChannels = nrChannels;
}

m_Texture::~m_Texture()
{
    stbi_image_free(Texture); 
    Texture = nullptr;
}
