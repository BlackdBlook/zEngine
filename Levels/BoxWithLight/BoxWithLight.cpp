#include "BoxWithLight.h"
#include "../../Objects/Box.h"
void BoxWithCamera::Init()
{
    objs.emplace_back(new Box());

}
