#pragma once
#include <iostream>
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