#pragma once
#include <iostream>
#include <glm/vec3.hpp>

std::ostream &operator<<(std::ostream &output, const glm::vec3 &D );

class Log 
{
public:
    template<typename T>
    static void printer(T arg)
    {
        std::cout << arg << std::endl;
    }

    template<typename T, typename ... TS>
    static void printer(T arg, TS ... args)
    {
        std::cout << arg << ' ';
        printer(args...);
    }
};