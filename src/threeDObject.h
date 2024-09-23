#pragma once

#include "GameObject.h"
#include "Game.h"
#include "OpenGLWrappedh/Model.h"
#include "OpenGLWrappedh/Texture.h"
#include "OpenGLWrappedh/Shader.h"

#include <memory>

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

	virtual void SetModel(std::shared_ptr<Model> _model) { mModel = _model; }
	virtual std::shared_ptr<Model> GetModel() { return mModel; }

	virtual void SetTexture(std::shared_ptr<Texture> _texture) { mTexture = _texture; }
	virtual std::shared_ptr<Texture> GetTexture() { return mTexture; }

	virtual void SetShader(std::shared_ptr<Shader> _shader) { mShader = _shader; }
	virtual std::shared_ptr<Shader> GetShader() { return mShader; }

	BoundingBox GetBoundingBox() { return mBoundingBox; }

	float GetWidth() { return mModel->get_width() * transform.scale.x; }
	float GetHeight() { return mModel->get_height() * transform.scale.y; }
	float GetLength() { return mModel->get_length() * transform.scale.z; }

	void SetSpecular(bool _isSpecular) { mIsSpecular = _isSpecular; }

protected:
	std::shared_ptr<Model> mModel;
	std::shared_ptr<Texture> mTexture;
	std::shared_ptr<Shader> mShader;

	BoundingBox mBoundingBox;

	bool mIsSpecular = true;

	glm::mat4 mModelMatrix{ 0 };

private:
	// For checking if we need to calculate the model matrix again
	glm::vec3 mLastPosition{ 0 };
	glm::vec3 mLastRotation{ 0 };
	glm::vec3 mLastScale{ 0 };
};