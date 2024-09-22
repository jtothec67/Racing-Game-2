#pragma once

#include "GameObject.h"
#include "Game.h"
#include "OpenGLWrappedh/Mesh.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Shader.h"

#include <memory>

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

	virtual void SetShader(std::shared_ptr<Shader> _shader) { mShader = _shader; }
	virtual std::shared_ptr<Shader> GetShader() { return mShader; }

private:
	Mesh* mMesh;
	Texture* mTexture;
	std::shared_ptr<Shader> mShader;
};