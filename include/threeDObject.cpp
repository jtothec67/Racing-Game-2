#include "threeDObject.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

threeDObject::threeDObject(Game* _game) : GameObject(_game)
{
	mModel = nullptr; // Make/download cube model and put it here as default model perchance
	mTexture = &(mGame->GetModelLibrary()->defaultTexture);
	mShader = &(mGame->GetShaderLibrary()->objectShader);
}

void threeDObject::Draw()
{
	if (!mVisible)
		return;

	if (mModel == nullptr)
	{
		return;
	}

	// Translate, rotate, and scale model
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));

	mShader->uniform("u_Model", model);

	if (mUpdateSpecular)
	{
		mShader->uniform("u_IsSpecular", mIsSpecular);
		mUpdateSpecular = false;
	}

	mShader->draw(mModel, mTexture);
}