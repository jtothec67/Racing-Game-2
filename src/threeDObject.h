#pragma once

#include "GameObject.h"
#include "Game.h"
#include "Model.h"
#include "Texture.h"
#include "Shader.h"

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

protected:
	Model* mModel;
	Texture* mTexture;
	Shader* mShader;
};