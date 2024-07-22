#pragma once

#include "GameObject.h"
#include "Game.h"
#include "OpenGLWrappedh/Mesh.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Shader.h"

#ifndef UIOBJECT_H
#define UIOBJECT_H

class UIObject : public GameObject
{
public:
	UIObject(Game* _game);

	~UIObject() {}

	void Draw() override;

	virtual void SetTexture(Texture* _texture) { mTexture = _texture; }
	virtual Texture* GetTexture() { return mTexture; }

	virtual void SetShader(Shader* _shader) { mShader = _shader; }
	virtual Shader* GetShader() { return mShader; }

	void GetTextureSize(int& _width, int& _height) { _width = mWidth; _height = mHeight; }

protected:
	int mWidth = 0;
	int mHeight = 0;

	Mesh* mMesh;
	Texture* mTexture;
	Shader* mShader;
};

#endif // UIOBJECT_H