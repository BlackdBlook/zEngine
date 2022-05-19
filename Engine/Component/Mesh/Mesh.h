#pragma once
#include "../Component.h"
#include <vector>
class Mesh :public Component
{
public:
    Mesh(std::vector<float> vertices);
};

