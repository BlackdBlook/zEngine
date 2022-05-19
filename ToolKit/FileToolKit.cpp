#include "FileToolKit.h"
#include <fstream>
#include <cstdio>
#include <direct.h>
#include <iostream>
using namespace std;
FileDoesNotExist::FileDoesNotExist(const string&& info)
{
    this->info = info;
}
string FileToolKit::ReadFile(const char* path)
{
    cout << path << endl;
    if (!FileExist(path))
    {
        return "";
    }
    string s;
    ifstream file(path);
    while (!file.eof())
    {
        char c[100]={0};
        file.read(c, 99);
        s += c;
    }
    file.close();
    return s;
}
bool FileToolKit::FileExist(const char* path)
{
    ifstream read;
    read.open(path);
    bool ans = read.is_open();
    read.close();
    return ans;
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

string PathToolKit::CompiePath(vector<const char*>&& path)
{
    if (path.size() <= 0)
        return string();
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
