#pragma once
#include <glad/glad.h>
#include <memory>
#include <string>

//basic type
typedef short int16;
typedef unsigned short uint16;
typedef long long int64;
typedef unsigned long long uint64;
typedef float float32;
typedef double float64;
typedef char char8;
typedef unsigned char uchar8;

// stl
using string  = std::string;

//openGL type
typedef GLuint GLID;

// shared_ptr
template<typename T>
using SPtr = std::shared_ptr<T>;

template<typename T, typename ...Args>
inline SPtr<T> NewSPtr(Args&&... args)
{
    return std::make_shared<T>(args...);
}

