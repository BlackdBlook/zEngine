#include "DrawRTSJX.h"

#include "Objects/SanJiaoXing/roteSJX.h"

void DrawRTSJX::Init()
{
    objs.emplace_back(new roteSJX(true));
    objs.emplace_back(new roteSJX(false));
}
