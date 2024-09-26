#include "Button.h"

#include <glm/glm.hpp>

Button::Button(Game* _game) : UIObject(_game)
	, mText(_game)
{
	SetTexture(mGame->GetModelLibrary()->unhoveredButtonTex);
	SetHoveredTexture(mGame->GetModelLibrary()->hoveredButtonTex);

	mTag = Tag::Button;
}

void Button::Draw()
{
	if (!mVisible)
		return;

	glm::mat4 model(1.0f);
	model = glm::mat4(1.0f);

	if (!mHovered)
	{
		float halfWidth = mWidth * 0.5f * transform.scale.x;
		float halfHeight = mHeight * 0.5f * transform.scale.y;
		model = glm::translate(model, glm::vec3(transform.position.x - halfWidth, transform.position.y - halfHeight, 0));
		model = glm::scale(model, glm::vec3(transform.scale.x * mWidth, transform.scale.y * mHeight, 1));
		mShader->uniform("u_Model", model);

		mShader->draw(mMesh.get(), mTexture.get());
	}
	else
	{
		float halfWidth = mHoveredWidth * 0.5f * transform.scale.x;
		float halfHeight = mHoveredHeight * 0.5f * transform.scale.y;
		model = glm::translate(model, glm::vec3(transform.position.x - halfWidth, transform.position.y - halfHeight, 0));
		model = glm::scale(model, glm::vec3(transform.scale.x * mHoveredWidth, transform.scale.y * mHoveredHeight, 1));
		mShader->uniform("u_Model", model);

		mShader->draw(mMesh.get(), mHoveredTexture.get());
	}

	mText.Draw(transform.position.x, transform.position.y);
}