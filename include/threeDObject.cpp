#include "threeDObject.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

threeDObject::threeDObject(Game* _game) : GameObject(_game)
{
	mModel = nullptr; // Make/download cube model and put it here as default model perchance
	mTexture = mGame->GetModelLibrary()->defaultTexture;
	mShader = mGame->GetShaderLibrary()->objectShader;
}

void threeDObject::Draw()
{
	if (!mVisible)
		return;

	if (mModel == nullptr)
		return;

	if (transform.position != mLastPosition || transform.rotation != mLastRotation || transform.scale != mLastScale)
	{
		mLastPosition = transform.position;
		mLastRotation = transform.rotation;
		mLastScale = transform.scale;

		// Translate, rotate, and scale model
		mModelMatrix = glm::mat4(1.f);
		mModelMatrix = glm::translate(mModelMatrix, transform.position);
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
		mModelMatrix = glm::rotate(mModelMatrix, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
		mModelMatrix = glm::scale(mModelMatrix, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z));
	}

	mShader->uniform("u_Model", mModelMatrix);

	mShader->uniform("u_IsSpecular", mIsSpecular);

	mShader->draw(mModel.get(), mTexture.get());
}