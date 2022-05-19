#pragma once
#include <string>
#include <exception>
#include <vector>
class FileDoesNotExist : public std::exception
{
public:
    FileDoesNotExist(const std::string&& info);
    std::string info;
};
enum class EWriteFileMode : unsigned char
{
    CreateOrOverried = 0,
    Append
};
class FileToolKit
{
public:
    static std::string ReadFile(const char* path);
    static bool FileExist(const char* path);
    static bool WriteFile(const char* path, const char* context, EWriteFileMode mode);
    static bool DeleteFile(const char* path);
private:
    FileToolKit(){}
    static bool OverriedWrite(const char* path, const char* context);
    static bool AppendWrite(const char* path, const char* context);
};
class PathToolKit
{
public:
    static std::string GetCurrentPath();
    static std::string GetFullPath(const char* path);
    static std::string CompiePath(std::vector<const char*>&& path);
private:

};

