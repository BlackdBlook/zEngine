#include "DrawSanjiaoxing.h"
#include <memory>

#include "Objects/SanJiaoXing/SanJiaoXing.h"
using namespace std;
void DrawSanjiaoxing::Init()
{
    objs.emplace_back(new SanJiaoXing());
}
