#pragma once
#include <assimp/types.h>

struct TextureAssimp
{
    unsigned int id;
    std::string type;
    aiString path;  // 我们储存纹理的路径用于与其它纹理进行比较
};

namespace Assimp
{
    using Texture = TextureAssimp;
}
