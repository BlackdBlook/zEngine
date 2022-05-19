#include "DrawSanjiaoxing.h"
#include "../../Objects/SanJiaoXing.h"
#include <memory>
using namespace std;
void DrawSanjiaoxing::Init()
{
    objs.emplace_back(new SanJiaoXing());
}
