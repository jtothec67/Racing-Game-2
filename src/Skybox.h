#pragma once

#include "GameObject.h"
#include "Game.h"
#include "OpenGLWrappedh/Mesh.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Shader.h"

class Skybox : public GameObject
{
public:
	Skybox(Game* _game);

	~Skybox() {}

	void Draw() override;

	virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }
	virtual Mesh* GetMesh() { return mMesh; }

	virtual void SetTexture(Texture* _texture) { mTexture = _texture; }
	virtual Texture* GetTexture() { return mTexture; }

	virtual void SetShader(Shader* _shader) { mShader = _shader; }
	virtual Shader* GetShader() { return mShader; }

private:
	Mesh* mMesh;
	Texture* mTexture;
	Shader* mShader;
};