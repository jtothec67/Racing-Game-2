#include "UIObject.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

UIObject::UIObject(Game* _game) : GameObject(_game)
{
	mShader = &(mGame->GetShaderLibrary()->uiShader);
	mMesh = &(mGame->GetModelLibrary()->quadMesh);
	mTexture = &(mGame->GetModelLibrary()->defaultTexture);

	mTexture->GetSize(mWidth, mHeight);
}

void UIObject::Draw()
{
	int windowWidth, windowHeight;
	mGame->GetWindowSize(windowWidth, windowHeight);
	glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, 0.0f, 1.0f);

	glm::mat4 model(1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(transform.position.x, transform.position.y, 0));
	model = glm::scale(model, glm::vec3(transform.scale.x * mWidth, transform.scale.y * mHeight, 1));

	mShader->uniform("u_Projection", projection);
	mShader->uniform("u_Model", model);
	mShader->uniform("u_View", glm::mat4(1.0f));

	mShader->draw(mMesh, mTexture);
}