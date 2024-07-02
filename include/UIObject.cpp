#include "UIObject.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

UIObject::UIObject(Game* _game) : GameObject(_game)
{
	mShader = new Shader("Assets/Shaders/UIShader.vert", "Assets/Shaders/UIShader.frag");
}

void UIObject::Draw()
{
	int width, height;
	mGame->GetWindowSize(width, height);
	glm::mat4 projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 1.0f);

	glm::mat4 model(1.0f);
	model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0, 0, 0)); // Top left for now
	model = glm::scale(model, glm::vec3(300.0f, 300.0f, 1)); // 300x300 for now

	mShader->uniform("u_Projection", projection);
	mShader->uniform("u_Model", model);
	mShader->uniform("u_View", glm::mat4(1.0f));

	mShader->draw(mModel, mTexture);
}