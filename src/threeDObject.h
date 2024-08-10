#pragma once

#include "GameObject.h"
#include "Game.h"
#include "OpenGLWrappedh/Model.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Shader.h"

struct BoundingBox
{
	glm::vec3 offset = glm::vec3(0.f, 0.f, 0.f);

	float widthX = 0.f;
	float heightY = 0.f;
	float depthZ = 0.f;
};

class threeDObject : public GameObject
{
public:
	threeDObject(Game* _game);

	~threeDObject() {}

	void Draw() override;

	virtual void SetModel(Model* _model) { mModel = _model; }
	virtual Model* GetModel() { return mModel; }

	virtual void SetTexture(Texture* _texture) { mTexture = _texture; }
	virtual Texture* GetTexture() { return mTexture; }

	virtual void SetShader(Shader* _shader) { mShader = _shader; }
	virtual Shader* GetShader() { return mShader; }

	BoundingBox GetBoundingBox() { return mBoundingBox; }

protected:
	Model* mModel;
	Texture* mTexture;
	Shader* mShader;

	BoundingBox mBoundingBox;
};