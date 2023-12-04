#pragma once
#include "Engine/Core/Level.h"
#include "Header.h"
class DrawDepthTestBuffer : public Level
{
public:
    ~DrawDepthTestBuffer() override = default;
    void Init() override;
};
