#include "LightScenceDepthFrameBufferFactory.h"

LightScenceDepthFrameBufferFactory::LightScenceDepthFrameBufferFactory()
{
    
}

LightSceneDepthFrameBuffer* LightScenceDepthFrameBufferFactory::CreateImpl(const LightSceneDepthFrameBufferCreateInfo& info)
{
    return nullptr;
}

LightScenceDepthFrameBufferFactory::~LightScenceDepthFrameBufferFactory()
{
}

LightScenceDepthFrameBufferFactory* LightScenceDepthFrameBufferFactory::GetInstance()
{
    static LightScenceDepthFrameBufferFactory ins;
    return &ins;
}

LightSceneDepthFrameBuffer* LightScenceDepthFrameBufferFactory::Create(const LightSceneDepthFrameBufferCreateInfo& info)
{
    return GetInstance()->Create(info);
}
