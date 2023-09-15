#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>


class AssetSystem
{
public:

    AssetSystem();

    
    
    std::string GetFilePathByName(const std::string& s);

    
    static AssetSystem* GetInstance();



private:

    void InitFileMap();

    void InitIgnoreMap();
    
    void RefreshFileMap();

    bool IsIgnoreToFileMap(const std::string& Name);
    
    // 文件映射表
    std::unordered_map<std::string, std::string> FileMap;

    // 忽略表
    std::unordered_set<std::string> IgnoreMap;
};
