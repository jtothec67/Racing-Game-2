#include "UIObject.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

UIObject::UIObject(Game* _game) : GameObject(_game)
{
	mTag = Tag::UI;

	mShader = &(mGame->GetShaderLibrary()->uiShader);
	mMesh = &(mGame->GetModelLibrary()->quadMesh);
	mTexture = &(mGame->GetModelLibrary()->defaultTexture);

	mTexture->GetSize(mWidth, mHeight);
	
	mGame->GetWindowSize(mScreenWidthLastFrame, mScreenHeightLastFrame);
}

void UIObject::Update(float _deltaTime)
{
	int winWidth, winHeight;
	mGame->GetWindowSize(winWidth, winHeight);

	if (mScreenWidthLastFrame != winWidth || mScreenHeightLastFrame != winHeight)
	{
		switch (mAnchor)
		{
            case Anchor::TopLeft:
            {
                int widthFromLeft = transform.position.x;
                int heightFromTop = mScreenHeightLastFrame - transform.position.y;
                transform.position = glm::vec3(widthFromLeft, winHeight - heightFromTop, 0);
                break;
            }
            case Anchor::TopRight:
            {
                int widthFromRight = mScreenWidthLastFrame - transform.position.x;
                int heightFromTop = mScreenHeightLastFrame - transform.position.y;
                transform.position = glm::vec3(winWidth - widthFromRight, winHeight - heightFromTop, 0);
                break;
            }
            case Anchor::TopCentre:
            {
                int widthDistFromCentre = transform.position.x - (mScreenWidthLastFrame / 2);
                int heightDistFromTop = mScreenHeightLastFrame - transform.position.y;
                transform.position = glm::vec3((winWidth / 2) + widthDistFromCentre, winHeight - heightDistFromTop, 0);
                break;
            }
            case Anchor::BottomLeft:
            {
                int widthFromLeft = transform.position.x;
                int heightFromBottom = transform.position.y;
                transform.position = glm::vec3(widthFromLeft, heightFromBottom, 0);
                break;
            }
            case Anchor::BottomRight:
            {
                int widthFromRight = mScreenWidthLastFrame - transform.position.x;
                int heightFromBottom = transform.position.y;
                transform.position = glm::vec3(winWidth - widthFromRight, heightFromBottom, 0);
                break;
            }
            case Anchor::BottomCentre:
            {
                int widthDistFromCentre = transform.position.x - (mScreenWidthLastFrame / 2);
                int heightFromBottom = transform.position.y;
                transform.position = glm::vec3((winWidth / 2) + widthDistFromCentre, heightFromBottom, 0);
                break;
            }
            case Anchor::Centre:
            {
                int widthDistFromCentre = transform.position.x - (mScreenWidthLastFrame / 2);
                int heightDistFromCentre = transform.position.y - (mScreenHeightLastFrame / 2);
                transform.position = glm::vec3((winWidth / 2) + widthDistFromCentre, (winHeight / 2) + heightDistFromCentre, 0);
                break;
            }
            case Anchor::LeftCentre:
			{
				transform.position = glm::vec3(transform.position.x, transform.position.y, 0);
				break;
			}
            case Anchor::RightCentre:
            {
                int widthFromRight = mScreenWidthLastFrame - transform.position.x;
                transform.position = glm::vec3(winWidth - widthFromRight, transform.position.y, 0);
                break;
            }
		}

		mScreenWidthLastFrame = winWidth;
		mScreenHeightLastFrame = winHeight;
	}
}

void UIObject::Draw()
{
	glm::mat4 model(1.0f);
	model = glm::mat4(1.0f);
	float halfWidth = mWidth * 0.5f * transform.scale.x;
	float halfHeight = mHeight * 0.5f * transform.scale.y;
	model = glm::translate(model, glm::vec3(transform.position.x - halfWidth, transform.position.y - halfHeight, 0));
	model = glm::scale(model, glm::vec3(transform.scale.x * mWidth, transform.scale.y * mHeight, 1));

	mShader->uniform("u_Model", model);

	mShader->draw(mMesh, mTexture);
}