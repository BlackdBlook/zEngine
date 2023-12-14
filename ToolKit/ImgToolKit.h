#pragma once
#include <memory>

class m_Texture
{
public:
    unsigned char* Data;
    int width, height, nrChannels;
    bool IsValid() const;
    m_Texture(unsigned char* texture
        ,int width, int height, int nrChannels);
    m_Texture(const m_Texture& other);
    ~m_Texture();
};

typedef std::shared_ptr<m_Texture> TexturePtr;

class ImgToolKit
{
private:
    friend class AssetSystem;
    static TexturePtr ReadImage(const char* path);
};