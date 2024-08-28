#pragma once

#include "GameObject.h"
#include "Game.h"
#include "OpenGLWrappedh/Mesh.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Shader.h"

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

	virtual void SetTexture(Texture* _texture) { mTexture = _texture; mTexture->GetSize(mWidth, mHeight); }
	virtual Texture* GetTexture() { return mTexture; }

	virtual void SetShader(Shader* _shader) { mShader = _shader; }
	virtual Shader* GetShader() { return mShader; }

	void GetTextureSize(int& _width, int& _height) { _width = mWidth; _height = mHeight; }

	void SetAnchor(Anchor _anchor) { mAnchor = _anchor; }

protected:
	int mWidth = 0;
	int mHeight = 0;

	Anchor mAnchor = Anchor::Center;

	Mesh* mMesh;
	Texture* mTexture;
	Shader* mShader;

private:
	int mScreenWidthLastFrame = 0;
	int mScreenHeightLastFrame = 0;
};