#pragma once

class LightSceneDepthFrameBuffer;

struct LightSceneDepthFrameBufferCreateInfo
{
    // 透视
    bool perspective;

    // 附加深度缓冲
    bool depthBuffer;

    LightSceneDepthFrameBufferCreateInfo()
    {
        perspective = false;
        depthBuffer = false;
    }
};

class LightScenceDepthFrameBufferFactory
{
    LightScenceDepthFrameBufferFactory();

    virtual LightSceneDepthFrameBuffer* CreateImpl(const LightSceneDepthFrameBufferCreateInfo& info);

    virtual ~LightScenceDepthFrameBufferFactory();
public:

    static LightScenceDepthFrameBufferFactory* GetInstance();
    
    static LightSceneDepthFrameBuffer* Create(const LightSceneDepthFrameBufferCreateInfo& info);
};
