#include "AssetSystem.h"

#include <stack>

#include "../../Header.h"
#include "../../ToolKit/FileToolKit.h"

AssetSystem::AssetSystem()
{
    InitFileMap();
}

std::string AssetSystem::GetFilePathByName(const std::string& s)
{
    auto it = FileMap.find(s);
    if(it == FileMap.end())
    {
        LOG("没有找到要查找的文件", s);
        return {};
    }

    return it->second;
}

AssetSystem* AssetSystem::GetInstance()
{
    static AssetSystem* const ins = new AssetSystem();

    return ins;
}

void AssetSystem::InitFileMap()
{
    LOG("建立文件映射");
    std::string path = PathToolKit::GetCurrentPath();

    std::vector<std::string> FilePaths;
    
    PathToolKit::GetAllFileInDirectory(FilePaths, path, true);

    while(!FilePaths.empty())
    {
        std::string p;

        FilePaths.back().swap(p);

        FilePaths.pop_back();

        std::string name = FileToolKit::GetFileName(p);

        if(IsIgnoreToFileMap(name))
        {
            continue;
        }

        auto it = FileMap.find(name);

        if(it != FileMap.end() && it->first == name)
        {
            LOG("发现重复的文件\n\t", p, "\n\t", it->second);
        }
        else
        {
            FileMap.insert({name, std::move(p)});
        }
    }
}

void AssetSystem::InitIgnoreMap()
{
    
}

void AssetSystem::RefreshFileMap()
{
    LOG("重建映射");
    FileMap.clear();
    InitFileMap();
}

bool AssetSystem::IsIgnoreToFileMap(const std::string& Name)
{
    // return IgnoreMap.find(Name) != IgnoreMap.end();
    return false;
}
