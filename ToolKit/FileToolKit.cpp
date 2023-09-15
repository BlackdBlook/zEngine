#include "FileToolKit.h"
#include <fstream>
#include <filesystem>
#include "../Header.h"
#include <direct.h>
using namespace std;
using namespace std::filesystem;
FileDoesNotExist::FileDoesNotExist(const string&& info)
{
    this->info = info;
}

string ReadFile_Internal(ifstream&& fs)
{
    string s;
    while (!fs.eof())
    {
        char c[100]={0};
        fs.read(c, 99);
        s += c;
    }
    fs.close();
    return s;
}

string FileToolKit::ReadFile(const char* path)
{
    LOG("读取文件", path);
    if (!FileExist(path))
    {
        LOG("要读取的文件不存在");
        return "";
    }

    return ReadFile_Internal(ifstream{path});
}

std::string FileToolKit::ReadFile(const std::string& path)
{
    LOG("读取文件", path);
    if (!FileExist(path))
    {
        LOG("要读取的文件不存在");
        return "";
    }

    return ReadFile_Internal(ifstream{path});
}

bool FileToolKit::FileExist(const char* Path)
{
    return FileToolKit::FileExist(path{Path});    
}

bool FileToolKit::FileExist(const std::string& Path)
{
    return FileToolKit::FileExist(path{Path});    
}

bool FileToolKit::FileExist(const std::filesystem::path& path)
{
    return exists(path);
}
bool FileToolKit::WriteFile(const char* path, const char* context, EWriteFileMode mode)
{
    if (mode == EWriteFileMode::CreateOrOverried)
    {
        if (FileExist(path))
        {
            DeleteFile(path);
        }
       return OverriedWrite(path,context);
    }
    else if (mode == EWriteFileMode::Append)
    {
        if (!FileExist(path))
        {
            return false;
        }
        return AppendWrite(path,context);
    }
    return false;
}

bool FileToolKit::DeleteFile(const char* path)
{
    if (!FileExist(path))
    {
        return false;
    }
    return remove(path) == 0;
}

std::string FileToolKit::GetFileName(const char* Path)
{
    return FileToolKit::GetFileName(path{Path});
}

std::string FileToolKit::GetFileName(const std::filesystem::path& Path)
{
    return Path.filename().generic_string();
}

bool FileToolKit::OverriedWrite(const char* path, const char* context)
{
    ofstream file(path, ios::out | ios::ate);
    if (!file.is_open())
        return false;
    file << context;
    file.close();
    return true;
}
bool FileToolKit::AppendWrite(const char* path, const char* context)
{
    ofstream file(path,ios::out | ios::app);
    if(!file.is_open())
        return false;
    file << context;
    file.close();
    return true;
}

string PathToolKit::GetCurrentPath()
{
    char* ans = nullptr;
    if ((ans = _getcwd(NULL, 0)) == nullptr)
    {
        LOG(L"ÃÂ¨ÃÂÃÂ·ÃÂ¥ÃÂÃÂÃÂ¨ÃÂ·ÃÂ¯ÃÂ¥ÃÂ¾ÃÂÃÂ¥ÃÂ¤ÃÂ±ÃÂ¨ÃÂ´ÃÂ¥");
        return "";
    }
    string s(ans);
    delete[] ans;
    return s;
}

string PathToolKit::GetFullPath(const char* path)
{
    return "";
}

bool PathToolKit::GetAllFileInDirectory(std::vector<std::string>& Out, const path& Path, bool SubPath)
{
    if(exists(Path) == false)
    {
        return false;
    }
    
    const directory_iterator it {Path};

    for(const auto& i : it)
    {
        if(SubPath && i.is_directory())
        {
            GetAllFileInDirectory(Out, i.path(), SubPath);
        }
        else
        {
            Out.push_back(i.path().string());
        }
    }
    return true;
}


string PathToolKit::CompiePath(vector<const char*>&& path)
{
    if (path.empty())
        return string{};
    string s;
    s += GetCurrentPath() + '\\';
    for (const char* c : path)
    {
        if (c[0] != '/' && s[s.size() - 1] != '/'
            && c[0] != '\\' && s[s.size() - 1] != '\\')
        {
            s += '\\';
        }
        s += c;
    }
    return s;
}
