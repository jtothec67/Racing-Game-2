#pragma once

#include "GameObject.h"
#include "Game.h"
#include "OpenGLWrappedh/Mesh.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Shader.h"

#include <memory>

enum class Anchor
{
    TopLeft,
    TopRight,
    TopCenter,
    BottomLeft,
    BottomRight,
    BottomCenter,
    Center,
    LeftCenter,
    RightCenter
};

class UIObject : public GameObject
{
public:
    UIObject(Game* _game);

    ~UIObject() {}

    void Update(float _deltaTime);
    void Draw() override;

    virtual void SetTexture(std::shared_ptr<Texture> _texture) { mTexture = _texture; mTexture->GetSize(mWidth, mHeight); }
    virtual std::shared_ptr<Texture> GetTexture() { return mTexture; }

    virtual void SetShader(std::shared_ptr<Shader> _shader) { mShader = _shader; }
    virtual std::shared_ptr<Shader> GetShader() { return mShader; }

    void GetTextureSize(int& _width, int& _height) { _width = mWidth; _height = mHeight; }

    void SetAnchor(Anchor _anchor) { mAnchor = _anchor; }

protected:
    int mWidth = 0;
    int mHeight = 0;

    Anchor mAnchor = Anchor::Center;

    std::shared_ptr<Mesh> mMesh;
    std::shared_ptr<Texture> mTexture;
    std::shared_ptr<Shader> mShader;

private:
    int mScreenWidthLastFrame = 0;
    int mScreenHeightLastFrame = 0;
};