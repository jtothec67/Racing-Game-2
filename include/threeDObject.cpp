#include "threeDObject.h"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

threeDObject::threeDObject(Game* _game) : GameObject(_game)
{
	mModel = nullptr; // Make/download cube model and put it here as default model
	mTexture = &(mGame->GetModelLibrary()->defaultTexture);
	mShader = &(mGame->GetShaderLibrary()->objectShader);
}

void threeDObject::Draw()
{
	if (mModel == nullptr)
	{
		return;
	}

	int width, height;
	mGame->GetWindowSize(width, height);
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.f);

	// Translate, rotate, and scale model
	glm::mat4 model(1.0f);
	model = glm::translate(model, transform.position);
	model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(2, 2, 2));

	// Use camera position and rotation to translate and rotate view matrix, then inverse it (view moves left, objects move right)
	glm::mat4 view(1.0f);
	view = glm::translate(view, mGame->GetCamera()->transform.position);
	view = glm::rotate(view, glm::radians(mGame->GetCamera()->transform.rotation.x), glm::vec3(1, 0, 0));
	view = glm::rotate(view, glm::radians(mGame->GetCamera()->transform.rotation.y), glm::vec3(0, 1, 0));
	view = glm::rotate(view, glm::radians(mGame->GetCamera()->transform.rotation.z), glm::vec3(0, 0, 1));
	view = glm::inverse(view);

	// Upload uniforms to our shader
	mShader->uniform("u_Projection", projection);
	mShader->uniform("u_Model", model);
	mShader->uniform("u_View", view);
	mShader->uniform("u_LightPos", mGame->GetLightPos());

	// Draw using our shader and out model and texture
	mShader->draw(GetModel(), GetTexture());
}