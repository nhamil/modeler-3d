#pragma once

#include "IGraphicsDevice.h"

#include "OGL/OglGeometry.h"
#include "OGL/OglShader.h"

namespace Core { class Sdl2Window; }

namespace Video
{

class OglGraphicsDevice : public IGraphicsDevice
{
public:
    OglGraphicsDevice(Core::Sdl2Window* window);
    ~OglGraphicsDevice();

    void Init();

    virtual float32 GetWidth() const;
    virtual float32 GetHeight() const ;
    virtual float32 GetAspectRatio() const;

    IVertexBuffer* CreateVertexBuffer(VertexFormat format, uint count, BufferHint hint = BufferHint::Dynamic);
    IIndexBuffer* CreateIndexBuffer(uint count, BufferHint hint = BufferHint::Dynamic);
    IShader* CreateShader(const std::string& vertex, const std::string& fragment);
    IGeometry* CreateGeometry();

    void SetClearColor(float32 r, float32 g, float32 b, float32 a = 1.0);
    void Clear(bool color = true, bool depth = true);

    const IGeometry* GetGeometry() const { return mGeometry; }
    IGeometry* GetGeometry() { return mGeometry; }
    const IShader* GetShader() const { return mShader; }
    IShader* GetShader() { return mShader; }

    void SetGeometry(IGeometry* geom);
    void SetShader(IShader* shader);

    void Draw(Primitive prim, uint start, uint primCount);
    void DrawIndices(Primitive prim, uint start, uint primCount);

    float32 Ratio = 1.3333;
private:
    Core::Sdl2Window* mWindow = nullptr;
    OglGeometry* mGeometry = nullptr;
    OglShader* mShader = nullptr;
};

}
