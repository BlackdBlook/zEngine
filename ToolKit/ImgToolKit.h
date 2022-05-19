#pragma once
#include <memory>

class m_Texture
{
public:
    int width, height, nrChannels;
    unsigned char* Texture;
    bool IsValid() const;
    m_Texture(unsigned char* texture ,int width, int height, int nrChannels);
    ~m_Texture();
};

typedef std::shared_ptr<m_Texture> Texture;

class ImgToolKit
{
public:
    static Texture ReadImage(const char* path);
};