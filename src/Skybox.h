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

	virtual void SetMesh(std::shared_ptr<Mesh> _mesh) { mMesh = _mesh; }
	virtual std::shared_ptr<Mesh> GetMesh() { return mMesh; }

	virtual void SetTexture(std::shared_ptr<Texture> _texture) { mTexture = _texture; }
	virtual std::shared_ptr<Texture> GetTexture() { return mTexture; }

	virtual void SetShader(std::shared_ptr<Shader> _shader) { mShader = _shader; }
	virtual std::shared_ptr<Shader> GetShader() { return mShader; }

private:
	std::shared_ptr<Mesh> mMesh;
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Shader> mShader;
};