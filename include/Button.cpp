#include "Button.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

Button::Button(Game* _game) : UIObject(_game)
	, mText(_game)
{
	mHoverTexture = &(mGame->GetModelLibrary()->defaultTexture);
	mHoverTexture->GetSize(mHoveredWidth, mHoveredHeight);

	mTag = Tag::Button;
}

void Button::Draw()
{
	glm::mat4 model(1.0f);
	model = glm::mat4(1.0f);

	if (!mHovered)
	{
		float halfWidth = mWidth * 0.5f * transform.scale.x;
		float halfHeight = mHeight * 0.5f * transform.scale.y;
		model = glm::translate(model, glm::vec3(transform.position.x - halfWidth, transform.position.y - halfHeight, 0));
		model = glm::scale(model, glm::vec3(transform.scale.x * mWidth, transform.scale.y * mHeight, 1));
		mShader->uniform("u_Model", model);

		mShader->draw(mMesh, mTexture);
	}
	else
	{
		float halfWidth = mHoveredWidth * 0.5f * transform.scale.x;
		float halfHeight = mHoveredHeight * 0.5f * transform.scale.y;
		model = glm::translate(model, glm::vec3(transform.position.x - halfWidth, transform.position.y - halfHeight, 0));
		model = glm::scale(model, glm::vec3(transform.scale.x * mHoveredWidth, transform.scale.y * mHoveredHeight, 1));
		mShader->uniform("u_Model", model);

		mShader->draw(mMesh, mHoverTexture);
	}

	if (mText.GetText() != "")
	{
		mText.Draw(transform.position.x, transform.position.y);
	}
}