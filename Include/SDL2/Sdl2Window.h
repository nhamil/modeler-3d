#pragma once

#include <OGL/OglGraphicsDevice.h>
#include <SDL2/SDL.h>

#include "IWindow.h"
#include "Types.h"


namespace Core
{

class Sdl2Window : public IWindow
{
public:
    Sdl2Window(const std::string& title, uint width, uint height);
    virtual ~Sdl2Window();

    virtual bool IsVisible() const { return mVisible; };
    virtual void SetVisible(bool visible);

    virtual const std::string& GetTitle() const { return mTitle; };
    virtual void SetTitle(const std::string& title);

    // TODO query from SDL
    virtual uint GetWidth() const { return mWidth; };
    virtual uint GetHeight() const { return mHeight; };
    virtual void SetSize(uint width, uint height);

    virtual SDL_GLContext GetOglContext() { return mContext; }

    virtual void PollEvents();
    virtual void SwapBuffers();

    float32 GetAspectRatio()
    {
        int width, height;
        SDL_GetWindowSize(mWindow, &width, &height);
        return (float32) width / height;
    }
private:
    void InitGlew();

    static bool mGlewInit;

    std::string mTitle;
    uint mWidth;
    uint mHeight;
    bool mVisible;
    SDL_Window* mWindow;
    SDL_GLContext mContext;
};

}
